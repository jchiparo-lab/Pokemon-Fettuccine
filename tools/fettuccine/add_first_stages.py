#!/usr/bin/env python3
"""
One-time follow-up to place_wild_pokemon.py: some Pokémon lines were only
placed in the wild already evolved (e.g. Torracat, never Litten), so their
first stage couldn't be caught or shown on the Pokédex Area screen. This puts
each of those first stages in one early area that suits its type, in all four
time-of-day tables.

Run from the project root:
    python3 tools/fettuccine/add_first_stages.py --dry-run   # report only
    python3 tools/fettuccine/add_first_stages.py             # rewrite the JSON

Only "spare" slots are used: a slot whose Pokémon also fills another slot in
the same table, so nothing disappears from any area. The script is
deterministic.
"""

import argparse
import json
import os
import sys
from collections import Counter, defaultdict

sys.path.insert(0, os.path.dirname(__file__))
import place_wild_pokemon as P  # noqa: E402

ROOTS = ['SPECIES_' + n for n in (
    'LITTEN', 'POPPLIO', 'SPRIGATITO', 'CHIMCHAR', 'PIKIPEK', 'FLETCHLING', 'ROOKIDEE',
    'STARLY', 'BIDOOF', 'BUNNELBY', 'BLIPBUG', 'DEWPIDER', 'KRICKETOT', 'NACLI', 'NYMBLE',
    'ROGGENROLA', 'ROLYCOLY', 'SMOLIV', 'TYMPOLE', 'WIGLETT', 'WOOPER_PALDEA')]

KINDS = ('land_mons', 'fishing_mons', 'water_mons')  # earliest-reachable first
KIND_PENALTY = {'land_mons': 0, 'fishing_mons': 15, 'water_mons': 40}
FISHING_GROUPS = [(0, 2), (2, 5), (5, 10)]
TARGET_RATE = 10  # preferred slot chance (%) for ordinary Pokémon

# Areas reachable before about the 4th badge (no Surf, Dive or Mirage Island).
EARLY_AREAS = ('gRoute101', 'gRoute102', 'gRoute103', 'gRoute104', 'gRoute110', 'gRoute111',
               'gRoute112', 'gRoute113', 'gRoute114', 'gRoute116', 'gRoute117',
               'gPetalburgWoods', 'gRusturfTunnel', 'gGraniteCave', 'gFieryPath',
               'gJaggedPass', 'gMeteorFalls_1F_1R', 'gNewMauville', 'gPetalburgCity',
               'gDewfordTown', 'gSlateportCity', 'gRustboroCity', 'gLittlerootTown',
               'gOldaleTown', 'gMauvilleCity')


def free_slots(mons, kind):
    """Indexes whose Pokémon also appears in another slot of the same rod group."""
    ranges = FISHING_GROUPS if kind == 'fishing_mons' else [(0, len(mons))]
    out = []
    for lo, hi in ranges:
        counts = Counter(m['species'] for m in mons[lo:hi])
        out += [i for i in range(lo, hi) if counts[mons[i]['species']] > 1]
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--dry-run', action='store_true')
    args = ap.parse_args()

    wild = json.load(open(P.WILD_JSON, encoding='utf-8'))
    group = wild['wild_encounter_groups'][0]
    rates = {f['type']: f['encounter_rates'] for f in group['fields']}
    aliases = P.load_aliases()
    species, _ = P.load_species(aliases)

    # area base label -> {time: table}
    areas = defaultdict(dict)
    for t in group['encounters']:
        for time in P.TIMES:
            if t['base_label'].endswith('_' + time):
                base = t['base_label'][:-len(time) - 1]
                if base not in P.SKIP_TABLES:
                    areas[base][time] = t

    wild_species = {m['species'] for t in group['encounters'] for k in KINDS + ('rock_smash_mons',)
                    for m in t.get(k, {}).get('mons', [])}
    per_area = Counter()
    report = []

    for root in ROOTS:
        if root in wild_species:
            report.append((root, None, 'already wild'))
            continue
        types = set(species[root]['types'])
        best = None
        for base in sorted(areas):
            tables = areas[base]
            if len(tables) != len(P.TIMES) or not base.startswith(EARLY_AREAS):
                continue
            if base in ('gGraniteCave_StevensRoom',):
                continue
            for kind in KINDS:
                picks = {}
                for time in P.TIMES:
                    mons = tables[time].get(kind, {}).get('mons')
                    if not mons:
                        break
                    existing = {aliases.get(m['species'], m['species']) for m in mons}
                    ex_types = set()
                    for sp in existing:
                        ex_types |= set(species.get(sp, {}).get('types', [])[:1])
                    habitat = P.area_types(base, ex_types, kind)
                    choices = []
                    for i in free_slots(mons, kind):
                        slot = {'kind': kind, 'rate': rates[kind][i], 'level': mons[i]['min_level'],
                                'habitat': habitat, 'time': time}
                        pts, stage = P.score(species, root, slot, True)
                        if pts is None or stage != root:
                            continue
                        rate_pts = -abs(slot['rate'] - TARGET_RATE)
                        choices.append((rate_pts, -i, i, slot['level']))
                    if not choices:
                        break
                    picks[time] = max(choices)
                if len(picks) != len(P.TIMES):
                    continue
                level = max(p[3] for p in picks.values())
                match = 2 if species[root]['types'][0] in habitat else 1
                pts = match * 30 - level * 3 - KIND_PENALTY[kind] - 25 * per_area[base]
                key = (pts, base, kind)
                if best is None or key > best[0]:
                    best = (key, base, kind, picks)
        if best is None:
            report.append((root, None, 'no suitable early slot'))
            continue
        _, base, kind, picks = best
        for time, (_, _, i, _) in picks.items():
            areas[base][time][kind]['mons'][i]['species'] = root
        per_area[base] += 1
        slot_rates = sorted({rates[kind][p[2]] for p in picks.values()})
        levels = sorted({areas[base][t][kind]['mons'][p[2]]['min_level'] for t, p in picks.items()})
        report.append((root, base, '%s, %s%%, Lv %s' % (P.KIND_NAMES[kind], '/'.join(map(str, slot_rates)),
                                                        '/'.join(map(str, levels)))))

    for root, base, info in report:
        print('%-14s %-28s %s' % (P.pretty(root), (base or '-')[1:], info))

    if not args.dry_run:
        with open(P.WILD_JSON, 'w', encoding='utf-8') as f:
            json.dump(wild, f, indent=2, ensure_ascii=False)
            f.write('\n')
        print('Wrote', P.WILD_JSON)


if __name__ == '__main__':
    main()
