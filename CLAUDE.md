# CLAUDE.md — Pokémon Fettuccine Version

## What this project is

A Pokémon Emerald ROM hack called **Pokémon Fettuccine Version** (working title), built on a fork of **pokeemerald-expansion**. Every town is renamed after pasta, the rival Brian hates Italian food, and several characters are replaced by members of the Retrotopia podcast.

The full design lives in **`docs/DESIGN.md`**. Read it before starting any task. Treat it as the source of truth: items marked **Decided** are final, and items marked **Open** need Joe's decision. If a task touches an Open item, ask instead of guessing.

## About the owner

Joe is a graphic designer and web developer, new to ROM hacking and C. Explain what you changed in plain language, and point out anything he should playtest. He works on an **Intel Mac** and tests in mGBA. He uses **MacPorts, not Homebrew** (Homebrew no longer fully supports Intel Macs). When instructions say `brew install`, translate them to the MacPorts equivalent (`sudo port install`).

## Ground rules

- **One feature per session.** Only change what the current task asks for. Don't refactor or "clean up" unrelated code.
- **Build after every change.** Run `make` and fix any errors before calling a task done.
- **Commit each working step** with a clear message, so broken changes are easy to roll back. Never commit a build that doesn't compile.
- **Prefer config over code.** Many features are options in `include/config/`. Check there first, and report what exists before writing custom code.
- **Verify, don't assume.** Option names and file layouts change between expansion versions. Read the actual files in this repo instead of relying on memory.
- **Text limits matter.** Location names, NPC dialogue boxes, and trainer names have character limits. Check that new text fits.
- **Graphics rules.** Sprites are indexed PNGs with 16 colors (index 0 is transparent). Keep new or recolored art within its palette, and check whether a palette is shared before changing it.
- **Keep the design doc current.** When a feature is finished or a detail changes, tell Joe so he can update the doc (or update the feature tracker in `docs/DESIGN.md` if he asks).

## Useful places in the repo

- `include/config/` — feature toggles (battle, items, Pokémon, overworld)
- `data/maps/` — map scripts, events, and NPC dialogue
- `src/data/trainers.party` (or similar) — trainer teams
- `graphics/` — sprites, tiles, and palettes

Paths can differ between versions; search the repo to confirm.

## Tools

- **mGBA** to playtest the built `.gba` file
- **Porymap** for map editing (Joe uses it for anything visual on maps)
- **Aseprite** for sprite work (done by Joe, not Claude Code)
