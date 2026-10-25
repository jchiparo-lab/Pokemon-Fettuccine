#!/usr/bin/env python3
"""
One-time script: place every Pokémon that can't be obtained yet into the wild.

Run from the project root:
    python3 tools/fettuccine/place_wild_pokemon.py --dry-run   # report only
    python3 tools/fettuccine/place_wild_pokemon.py             # rewrite the JSON

What it does:
  1. Reads every species from src/data/pokemon/species_info/ (types, base stats,
     evolutions, legendary flags).
  2. Works out what the player can already get: Emerald's wild tables, gifts,
     eggs, fossils, in-game trades and static encounters, plus anything those
     evolve into or breed down to.
  3. Splits each Emerald encounter table into Morning / Day / Evening / Night
     copies (time-of-day encounters).
  4. Every Emerald species keeps one slot (its best one) in every copy, so it
     stays where it was. The other "duplicate" slots are free, and missing
     Pokémon are placed into them, matched by type to the area and by level.
  5. Writes the new src/data/wild_encounters.json and a readable report,
     docs/wild_pokemon_placements.md.

Not placed here: legendaries, mythicals, Ultra Beasts and Paradox Pokémon
(they're one-off encounters), cosmetic forms, Megas and other battle forms.
The script is deterministic: the same input always gives the same output.
"""

import argparse
import glob
import json
import re
import sys
from collections import defaultdict

WILD_JSON = 'src/data/wild_encounters.json'
REPORT = 'docs/wild_pokemon_placements.md'
TIMES = ['Morning', 'Day', 'Evening', 'Night']

# Encounter tables that never get new Pokémon (unused or event-only maps)
SKIP_TABLES = {
    'gCaveOfOrigin_UnusedRubySapphireMap1', 'gCaveOfOrigin_UnusedRubySapphireMap2',
    'gCaveOfOrigin_UnusedRubySapphireMap3',
    'gAlteringCave2', 'gAlteringCave3', 'gAlteringCave4', 'gAlteringCave5',
    'gAlteringCave6', 'gAlteringCave7', 'gAlteringCave8', 'gAlteringCave9',
}

# Extra types that suit each area, on top of the types already living there.
# Matched against the start of the table label.
AREA_TYPES = [
    ('gPetalburgWoods', {'BUG', 'GRASS', 'POISON', 'FAIRY', 'NORMAL'}),
    ('gRusturfTunnel', {'NORMAL', 'ROCK', 'GROUND', 'FIGHTING'}),
    ('gGraniteCave', {'ROCK', 'GROUND', 'STEEL', 'FIGHTING', 'DARK', 'GHOST'}),
    ('gFieryPath', {'FIRE', 'ROCK', 'GROUND', 'POISON'}),
    ('gJaggedPass', {'FIRE', 'ROCK', 'GROUND', 'FIGHTING'}),
    ('gMagmaHideout', {'FIRE', 'ROCK', 'GROUND', 'POISON', 'STEEL'}),
    ('gMtPyre_Exterior', {'GHOST', 'PSYCHIC', 'FAIRY', 'GRASS'}),
    ('gMtPyre_Summit', {'GHOST', 'PSYCHIC', 'FAIRY', 'FLYING'}),
    ('gMtPyre', {'GHOST', 'PSYCHIC', 'DARK'}),
    ('gMeteorFalls', {'DRAGON', 'PSYCHIC', 'ROCK', 'WATER'}),
    ('gVictoryRoad', {'FIGHTING', 'ROCK', 'STEEL', 'DRAGON', 'GROUND', 'DARK'}),
    ('gShoalCave', {'ICE', 'WATER', 'ROCK'}),
    ('gSeafloorCavern', {'WATER', 'DARK', 'ROCK'}),
    ('gCaveOfOrigin', {'GHOST', 'DARK', 'PSYCHIC', 'GROUND', 'DRAGON'}),
    ('gNewMauville', {'ELECTRIC', 'STEEL'}),
    ('gAbandonedShip', {'GHOST', 'WATER', 'STEEL'}),
    ('gSkyPillar', {'DRAGON', 'FLYING', 'PSYCHIC', 'GHOST', 'ROCK', 'ICE'}),
    ('gMirageTower', {'GROUND', 'ROCK', 'GHOST', 'BUG'}),
    ('gDesertUnderpass', {'GROUND', 'POISON', 'NORMAL', 'GHOST', 'ROCK'}),
    ('gArtisanCave', {'NORMAL', 'FAIRY', 'PSYCHIC', 'STEEL', 'ROCK'}),
    ('gAlteringCave', {'POISON', 'DARK', 'GHOST', 'ROCK', 'DRAGON', 'STEEL', 'ICE', 'FIGHTING'}),
    ('gSafariZone', {'NORMAL', 'GRASS', 'BUG', 'GROUND', 'PSYCHIC', 'FAIRY', 'ELECTRIC', 'FIRE', 'POISON', 'FLYING', 'ICE', 'FIGHTING'}),
    ('gRoute111', {'GROUND', 'ROCK', 'FIRE', 'NORMAL', 'BUG'}),
    ('gRoute112', {'FIRE', 'ROCK', 'NORMAL', 'GRASS'}),
    ('gRoute113', {'STEEL', 'GROUND', 'FIRE', 'NORMAL', 'ROCK'}),
    ('gRoute114', {'GRASS', 'POISON', 'NORMAL', 'GROUND', 'DRAGON'}),
    ('gRoute117', {'FAIRY', 'BUG', 'NORMAL', 'GRASS', 'ELECTRIC'}),
    ('gRoute119', {'GRASS', 'BUG', 'WATER', 'ELECTRIC', 'NORMAL', 'FLYING', 'DRAGON'}),
    ('gRoute120', {'GRASS', 'BUG', 'ELECTRIC', 'NORMAL', 'FLYING', 'DARK', 'ICE'}),
    ('gRoute121', {'GHOST', 'GRASS', 'NORMAL', 'POISON', 'PSYCHIC', 'DARK'}),
    ('gRoute123', {'GHOST', 'GRASS', 'NORMAL', 'POISON', 'PSYCHIC', 'FIGHTING'}),
]
ROUTE_TYPES = {'NORMAL', 'GRASS', 'BUG', 'FLYING', 'ELECTRIC', 'FAIRY', 'POISON', 'PSYCHIC', 'FIGHTING'}

# Starters and pseudo-legendary lines only go in rare slots (5% or less)
RARE = {'SPECIES_' + n for n in (
    'BULBASAUR CHARMANDER SQUIRTLE CHIKORITA CYNDAQUIL TOTODILE TREECKO TORCHIC MUDKIP '
    'TURTWIG CHIMCHAR PIPLUP SNIVY TEPIG OSHAWOTT CHESPIN FENNEKIN FROAKIE ROWLET LITTEN '
    'POPPLIO GROOKEY SCORBUNNY SOBBLE SPRIGATITO FUECOCO QUAXLY '
    'DRATINI LARVITAR BAGON BELDUM GIBLE DEINO GOOMY JANGMO_O DREEPY FRIGIBAX').split()}
RARE_MAX_RATE = 5

# Most new Pokémon per area, time of day and encounter type (per rod for fishing),
# so Emerald's own Pokémon stay common
MAX_NEW = {'land_mons': 3, 'water_mons': 1, 'fishing_mons': 1, 'rock_smash_mons': 1}
MAX_NEW_EARLY = 2  # land tables at level 8 or lower
SPREAD_PENALTY = 6  # per new Pokémon already in the same area and time

# Families whose species data is built from shared templates the parser can't read,
# plus White-Striped Basculin (the only way to get Basculegion). Placed by hand.
def lv(n, target):
    return {'method': 'EVO_LEVEL', 'param': str(n), 'target': target, 'region_only': False, 'conditional': False}


MANUAL_SPECIES = {
    'SPECIES_UNOWN': (['PSYCHIC'], 336, []),
    'SPECIES_SCATTERBUG': (['BUG'], 200, [lv(9, 'SPECIES_SPEWPA')]),
    'SPECIES_SPEWPA': (['BUG'], 213, [lv(12, 'SPECIES_VIVILLON')]),
    'SPECIES_VIVILLON': (['BUG', 'FLYING'], 411, []),
    'SPECIES_FLABEBE': (['FAIRY'], 303, [lv(19, 'SPECIES_FLOETTE')]),
    'SPECIES_FLOETTE': (['FAIRY'], 371, []),
    'SPECIES_FURFROU': (['NORMAL'], 472, []),
    'SPECIES_MINIOR': (['ROCK', 'FLYING'], 440, []),
}
MANUAL_ROOTS = ['SPECIES_UNOWN', 'SPECIES_SCATTERBUG', 'SPECIES_FLABEBE', 'SPECIES_FURFROU',
                'SPECIES_MINIOR', 'SPECIES_BASCULIN_WHITE_STRIPED']

NIGHT_TYPES = {'GHOST', 'DARK'}
DAY_TYPES = {'GRASS', 'BUG', 'FIRE'}
EVENING_TYPES = {'PSYCHIC', 'FAIRY'}

EXCLUDE_FLAGS = ('isRestrictedLegendary', 'isSubLegendary', 'isMythical', 'isUltraBeast', 'isParadox')
BATTLE_FORM_FLAGS = ('isMegaEvolution', 'isGigantamax', 'isPrimalReversion', 'isTotem', 'isUltraBurst', 'isTeraForm')
REGIONAL_FLAGS = ('isAlolanForm', 'isGalarianForm', 'isHisuianForm', 'isPaldeanForm')


def power_cap(level):
    """Highest base stat total a wild Pokémon should have at this level."""
    return 300 + 6 * level


def load_aliases():
    aliases = {}
    for line in open('include/constants/species.h', encoding='utf-8'):
        m = re.match(r'\s+(SPECIES_\w+) = (SPECIES_\w+),', line)
        if m:
            aliases[m.group(1)] = m.group(2)
    return aliases


def load_species(aliases):
    species = {}
    order = []
    for path in sorted(glob.glob('src/data/pokemon/species_info/gen_*_families.h'),
                       key=lambda p: int(re.search(r'gen_(\d+)', p).group(1))):
        text = open(path, encoding='utf-8').read()
        # Some families share a types macro, e.g. CLEFAIRY_FAMILY_TYPES (first, newest definition wins)
        type_macros = {}
        for d in re.finditer(r'#define (\w+_TYPES)\s*\{([^}]*)\}', text):
            type_macros.setdefault(d.group(1), d.group(2))
        for m in re.finditer(r'\[(SPECIES_\w+)\]\s*=\s*\n\s*\{', text):
            name = m.group(1)
            depth, i = 0, m.end() - 1
            while True:
                c = text[i]
                if c == '{':
                    depth += 1
                elif c == '}':
                    depth -= 1
                    if depth == 0:
                        break
                i += 1
            body = text[m.end():i]
            if name in species:
                continue
            stats = {}
            for stat in ('baseHP', 'baseAttack', 'baseDefense', 'baseSpeed', 'baseSpAttack', 'baseSpDefense'):
                s = re.search(r'\.%s\s*=\s*(\d+)' % stat, body)
                stats[stat] = int(s.group(1)) if s else 0
            t = re.search(r'\.types = MON_TYPES\(([^)]*)\)', body)
            if t:
                types = [x.strip().replace('TYPE_', '') for x in t.group(1).split(',')]
            else:
                t = re.search(r'\.types = (\w+_TYPES)', body)
                types = [x.strip().replace('TYPE_', '') for x in type_macros.get(t.group(1), '').split(',')] if t else []
                types = list(dict.fromkeys(x for x in types if x))
            if not types:
                types = ['NORMAL']  # forms built from shared macros (Vivillon patterns etc.)
            dex = re.search(r'\.natDexNum = (NATIONAL_DEX_\w+)', body)
            evos = []
            start = body.find('.evolutions = EVOLUTION(')
            if start >= 0:
                j = start + len('.evolutions = EVOLUTION(')
                depth = 1
                while depth:
                    depth += {'(': 1, ')': -1}.get(body[j], 0)
                    j += 1
                evo_text = body[start:j]
                found = list(re.finditer(r'\{(EVO_\w+),\s*([^,]+),\s*(SPECIES_\w+)', evo_text))
                for n, ev in enumerate(found):
                    end = found[n + 1].start() if n + 1 < len(found) else len(evo_text)
                    rest = evo_text[ev.end():end]
                    target = aliases.get(ev.group(3), ev.group(3))
                    evos.append({'method': ev.group(1), 'param': ev.group(2).strip(),
                                 'target': target, 'region_only': 'IF_REGION,' in rest,
                                 'conditional': 'CONDITIONS' in rest})
            species[name] = {
                'name': name, 'types': types, 'bst': sum(stats.values()),
                'dex': dex.group(1) if dex else None, 'evos': evos,
                'flags': {f for f in EXCLUDE_FLAGS + BATTLE_FORM_FLAGS + REGIONAL_FLAGS
                          if re.search(r'\.%s = TRUE' % f, body)},
            }
            order.append(name)
    for name, (types, bst, evos) in MANUAL_SPECIES.items():
        species[name] = {'name': name, 'types': types, 'bst': bst, 'dex': None, 'evos': evos, 'flags': set()}
        order.append(name)
    return species, order


def emerald_tables(wild):
    group = [g for g in wild['wild_encounter_groups'] if g.get('for_maps')][0]
    return group, [t for t in group['encounters']
                   if not re.search(r'_(FireRed|LeafGreen)$', t['base_label'])]


def obtainable_start(tables, aliases):
    got = set()
    for t in tables:
        for kind in ('land_mons', 'water_mons', 'rock_smash_mons', 'fishing_mons'):
            for mon in t.get(kind, {}).get('mons', []):
                got.add(aliases.get(mon['species'], mon['species']))
    for path in glob.glob('data/maps/*/scripts.inc'):
        if '_Frlg' in path:
            continue
        for m in re.finditer(r'(?:givemon|giveegg|setwildbattle|seteventmon)\s+(SPECIES_\w+)', open(path, encoding='utf-8').read()):
            got.add(aliases.get(m.group(1), m.group(1)))
    # Starters, plus the four Emerald in-game trades
    starter = open('src/starter_choose.c', encoding='utf-8').read()
    got |= set(re.findall(r':\s*(SPECIES_(?:ROWLET|SCORBUNNY|FROAKIE))', starter))
    got |= {'SPECIES_SEEDOT', 'SPECIES_PLUSLE', 'SPECIES_HORSEA', 'SPECIES_MEOWTH'}
    # Feebas lives on special Route 119 fishing tiles handled in code, not in the tables
    got.add('SPECIES_FEEBAS')
    return got


def spread(species, got):
    """Add everything reachable by evolving or breeding."""
    pre = defaultdict(list)
    for s in species.values():
        for e in s['evos']:
            if not e['region_only']:
                pre[e['target']].append(s['name'])
    changed = True
    while changed:
        changed = False
        for name in list(got):
            s = species.get(name)
            if not s:
                continue
            nxt = [e['target'] for e in s['evos'] if not e['region_only']] + pre.get(name, [])
            for n in nxt:
                if n not in got:
                    got.add(n)
                    changed = True
    return got, pre


def candidates(species, order, got, pre):
    """Species to place: base forms and regional forms nobody can get yet."""
    first_of_dex = {}
    for name in order:
        d = species[name]['dex']
        if d and d not in first_of_dex:
            first_of_dex[d] = name
    out, gaps = [], []
    for name in order:
        s = species[name]
        if s['flags'] & set(EXCLUDE_FLAGS + BATTLE_FORM_FLAGS) or not s['dex']:
            continue
        is_base = first_of_dex[s['dex']] == name
        # Regional forms only, not their battle forms (e.g. Zen Mode Galarian Darmanitan)
        is_regional = bool(s['flags'] & set(REGIONAL_FLAGS)) and bool(
            re.search(r'_(ALOLA|GALAR|HISUI|PALDEA)(_(COMBAT|BLAZE|AQUA|STANDARD))?$', name))
        if not (is_base or is_regional) or name in got:
            continue
        parents = pre.get(name, [])
        region_parents = [p for p in species if any(e['target'] == name and e['region_only'] for e in species[p]['evos'])]
        if parents:
            continue  # its pre-evolution is placed instead
        if region_parents:
            gaps.append(name)  # e.g. Alolan Raichu: only evolves "in Alola"
            continue
        out.append(name)
    out += [n for n in MANUAL_ROOTS if n not in got and n not in out]
    return out, gaps


def stage_for_level(species, root, level):
    """Evolve a placed Pokémon by plain level-up while the slot's level allows it."""
    cur = root
    while True:
        nxt = [e for e in species[cur]['evos']
               if e['method'] == 'EVO_LEVEL' and e['param'].isdigit() and not e['conditional']
               and int(e['param']) > 0 and int(e['param']) + 3 <= level and e['target'] in species]
        if not nxt:
            return cur
        cur = nxt[0]['target']


def area_types(label, existing_types, kind):
    if kind in ('water_mons', 'fishing_mons'):
        return {'WATER'} | existing_types
    if kind == 'rock_smash_mons':
        return {'ROCK', 'GROUND', 'STEEL'} | existing_types
    for prefix, extra in AREA_TYPES:
        if label.startswith(prefix):
            return extra  # themed areas use only their own list
    if re.match(r'g(Route|.*City|.*Town)', label):
        return ROUTE_TYPES | existing_types
    return existing_types


def build_slots(tables, species, aliases):
    """Every free slot: (label, time, kind, index, rate, level)."""
    rates = {}
    group_ranges = {'fishing_mons': [(0, 2), (2, 5), (5, 10)]}
    slots = []
    for t in tables:
        label = t['base_label']
        for kind in ('land_mons', 'water_mons', 'rock_smash_mons', 'fishing_mons'):
            mons = t.get(kind, {}).get('mons')
            if not mons:
                continue
            rate_list = FIELD_RATES[kind]
            existing = {aliases.get(m['species'], m['species']) for m in mons}
            ex_types = set()
            for sp in existing:
                ex_types |= set(species.get(sp, {}).get('types', [])[:1])  # main type only
            habitat = area_types(label, ex_types, kind)
            ranges = group_ranges.get(kind, [(0, len(mons))])
            free = []
            for lo, hi in ranges:
                best = {}
                for i in range(lo, hi):
                    sp = mons[i]['species']
                    if sp not in best or rate_list[i] > rate_list[best[sp]]:
                        best[sp] = i
                free += [i for i in range(lo, hi) if best[mons[i]['species']] != i]
            if label in SKIP_TABLES:
                free = []
            for time in TIMES:
                for i in free:
                    group = next(n for n, (lo, hi) in enumerate(ranges) if lo <= i < hi)
                    slots.append({'label': label, 'time': time, 'kind': kind, 'index': i,
                                  'rate': rate_list[i], 'level': mons[i]['min_level'],
                                  'habitat': habitat, 'taken': None,
                                  'bucket': (label, time, kind, group),
                                  'cap': MAX_NEW_EARLY if kind == 'land_mons' and mons[i]['max_level'] <= 8 else MAX_NEW[kind]})
    return slots


def score(species, root, slot, strict):
    stage = stage_for_level(species, root, slot['level'])
    s = species[stage]
    types = set(s['types'])
    if s['bst'] > power_cap(slot['level']):
        return None, stage
    if root in RARE and slot['rate'] > RARE_MAX_RATE:
        return None, stage
    if slot['kind'] in ('water_mons', 'fishing_mons') and 'WATER' not in types:
        return None, stage
    if slot['kind'] == 'rock_smash_mons' and not types & {'ROCK', 'GROUND', 'STEEL'}:
        return None, stage
    main = s['types'][0]
    match = 2 if main in slot['habitat'] else (1 if types & slot['habitat'] else 0)
    if slot['kind'] == 'land_mons' and types == {'WATER'} and 'WATER' not in slot['habitat']:
        return None, stage
    if strict and match == 0:
        return None, stage
    pts = match * 15 + slot['rate']
    if types & NIGHT_TYPES:
        pts += 15 if slot['time'] == 'Night' else -10
    elif types & DAY_TYPES:
        pts += 8 if slot['time'] == 'Day' else 0
    elif types & EVENING_TYPES:
        pts += 8 if slot['time'] == 'Evening' else 0
    if slot['kind'] in ('water_mons', 'fishing_mons') and 'WATER' in types:
        pts += 10
    return pts, stage


def place(species, roots, slots):
    placements = defaultdict(list)
    used = defaultdict(set)  # (label, time) -> species placed there
    filled = defaultdict(int)  # bucket -> new Pokémon placed in it

    def options(root, strict, avoid_labels):
        opts = []
        for idx, slot in enumerate(slots):
            if slot['taken'] or slot['label'] in avoid_labels or filled[slot['bucket']] >= slot['cap']:
                continue
            pts, stage = score(species, root, slot, strict)
            if pts is None or stage in used[(slot['label'], slot['time'])]:
                continue
            pts -= SPREAD_PENALTY * len(used[(slot['label'], slot['time'])])
            opts.append((pts, -idx, idx, stage))
        return sorted(opts, reverse=True)

    for round_no in range(2):  # every Pokémon gets up to two homes
        for strict in (True, False):
            pending = [r for r in roots if len(placements[r]) == round_no]
            counted = sorted(pending, key=lambda r: (len(options(r, strict, set())), r))
            for root in counted:
                if len(placements[root]) > round_no:
                    continue
                avoid = {p['label'] for p in placements[root]}
                opts = options(root, strict, avoid)
                if not opts:
                    continue
                _, _, idx, stage = opts[0]
                slot = slots[idx]
                slot['taken'] = stage
                used[(slot['label'], slot['time'])].add(stage)
                filled[slot['bucket']] += 1
                placements[root].append(slot)
    return placements


def write_json(wild, group, tables, slots):
    by_label = defaultdict(list)
    for s in slots:
        if s['taken']:
            by_label[(s['label'], s['time'])].append(s)
    new_list = []
    for t in group['encounters']:
        if t not in tables:
            new_list.append(t)
            continue
        for time in TIMES:
            copy = json.loads(json.dumps(t))
            copy['base_label'] = t['base_label'] + '_' + time
            for s in by_label[(t['base_label'], time)]:
                copy[s['kind']]['mons'][s['index']]['species'] = s['taken']
            new_list.append(copy)
    group['encounters'] = new_list
    with open(WILD_JSON, 'w', encoding='utf-8') as f:
        json.dump(wild, f, indent=2, ensure_ascii=False)
        f.write('\n')


def pretty(name):
    return name.replace('SPECIES_', '').replace('_', ' ').title()


KIND_NAMES = {'land_mons': 'grass/cave', 'water_mons': 'surfing', 'fishing_mons': 'fishing', 'rock_smash_mons': 'Rock Smash'}


def write_report(species, roots, placements, gaps, slots):
    lines = ['# Wild Pokémon placements', '',
             'Generated by `tools/fettuccine/place_wild_pokemon.py`. Every area now has Morning, Day, Evening and',
             'Night encounter tables. Emerald\'s own Pokémon keep their best slot in every table; the Pokémon below',
             'fill the duplicate slots. "Rate" is the slot\'s chance within that encounter type and time of day.', '']
    unplaced = [r for r in roots if not placements[r]]
    lines += ['## Summary', '',
              '- Pokémon lines placed: %d' % sum(1 for r in roots if placements[r]),
              '- Placed in two areas: %d' % sum(1 for r in roots if len(placements[r]) >= 2),
              '- Not placed (no room): %d' % len(unplaced),
              '- Free slots left over: %d' % sum(1 for s in slots if not s['taken']), '']
    if unplaced:
        lines += ['### Not placed', ''] + ['- ' + pretty(r) for r in unplaced] + ['']
    if gaps:
        lines += ['### Regional evolutions that need another method',
                  '', 'These only evolve "in" their home region, so they can\'t be reached yet:', '']
        lines += ['- ' + pretty(g) for g in gaps] + ['']
    lines += ['## By area', '']
    by_area = defaultdict(list)
    for s in slots:
        if s['taken']:
            by_area[s['label']].append(s)
    for label in sorted(by_area):
        lines += ['### ' + label[1:], '', '| Pokémon | Time | Where | Rate | Level |', '| --- | --- | --- | --- | --- |']
        for s in sorted(by_area[label], key=lambda s: (TIMES.index(s['time']), s['kind'], s['index'])):
            lines.append('| %s | %s | %s | %d%% | %d |' % (pretty(s['taken']), s['time'], KIND_NAMES[s['kind']], s['rate'], s['level']))
        lines.append('')
    with open(REPORT, 'w', encoding='utf-8') as f:
        f.write('\n'.join(lines))


FIELD_RATES = {}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--dry-run', action='store_true')
    args = ap.parse_args()

    wild = json.load(open(WILD_JSON, encoding='utf-8'))
    group, tables = emerald_tables(wild)
    if any(t['base_label'].endswith('_' + TIMES[0]) for t in tables):
        sys.exit('wild_encounters.json already has time-of-day tables; this script only runs once.')
    for field in group['fields']:
        FIELD_RATES[field['type']] = field['encounter_rates']

    aliases = load_aliases()
    species, order = load_species(aliases)
    got, pre = spread(species, obtainable_start(tables, aliases))
    roots, gaps = candidates(species, order, got, pre)
    slots = build_slots(tables, species, aliases)
    placements = place(species, roots, slots)

    placed = sum(1 for r in roots if placements[r])
    print('Species data: %d entries; already obtainable: %d' % (len(species), len(got)))
    print('Lines to place: %d; placed: %d; in two areas: %d' % (len(roots), placed, sum(1 for r in roots if len(placements[r]) >= 2)))
    print('Free slots: %d; used: %d' % (len(slots), sum(1 for s in slots if s['taken'])))
    print('Unplaced:', ', '.join(pretty(r) for r in roots if not placements[r]) or 'none')
    print('Regional gaps:', ', '.join(pretty(g) for g in gaps) or 'none')
    if args.dry_run:
        return
    write_json(wild, group, tables, slots)
    write_report(species, roots, placements, gaps, slots)
    print('Wrote', WILD_JSON, 'and', REPORT)


if __name__ == '__main__':
    main()
