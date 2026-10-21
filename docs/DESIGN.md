# Pokémon Fettuccine Version — Design Doc

Working title. A Pokémon Emerald ROM hack built on **pokeemerald-expansion**. This file is the source of truth for what the game should be. Items marked **Decided** are final; items marked **Open** still need a decision from Joe before implementation.

## Overview

Most features below already exist in pokeemerald-expansion as built-in systems or config toggles. The main custom work is the story and character changes, the randomizer, the PC item, and possibly the party-menu move relearner.

Workflow rule: build and test after every change, and `git commit` each working step so any broken edit can be rolled back.

## Region

The game takes place in one region, **Pastalia** (Hoenn renamed; pasta + Italia). Johto and Kanto were considered and cut to keep the scope manageable.

- **Decided and done:** the region is called **PASTALIA** in all dialogue, the Pokédex ("PASTALIA DEX"), the PokéNav, the Town Map title, and the diploma.
- **Still to do (art):** two PokéNav graphics have "HOENN MAP" drawn into the pixels: `graphics/pokenav/options/hoenn_map.png` and `graphics/pokenav/left_headers/hoenn_map.png`. They need "PASTALIA MAP" (or similar) redrawn in Aseprite.

## Town names

Every town gets a pasta-themed name that echoes the original. Update the location name, signs, NPC dialogue, the Town Map, and Fly destinations.

**Done.** Names appear in all dialogue, signs, popups, the Town Map, Fly map, PokéNav, and save screen. Long names automatically switch to a narrower font on the Town Map, Fly map, PokéNav map, and save screen. Town sign slogans are unchanged. Internal map names (what Porymap shows, e.g. `LittlerootTown`) keep their original names.

- **Known issue:** the map-name popup is too narrow for FETTUCCINE GRANDE CITY, so it is cut off there. Fixing it needs wider popup frame art (a later sprite task).

| Original | New name | Pasta reference |
| --- | --- | --- |
| Littleroot Town | Lil Ragu Town | Ragù sauce |
| Oldale Town | Orzodale Town | Orzo |
| Petalburg City | Pestoburg City | Pesto |
| Rustboro City | Rotiniboro City | Rotini |
| Dewford Town | Doughford Town | Pasta dough |
| Slateport City | Spaghettiport City | Spaghetti |
| Mauville City | Macaroville City | Macaroni |
| Verdanturf Town | Vermiturf Town | Vermicelli |
| Fallarbor Town | Farfallarbor Town | Farfalle |
| Lavaridge Town | Lasagnaridge Town | Lasagna |
| Fortree City | Fortellini City | Tortellini |
| Lilycove City | Linguicove City | Linguine |
| Mossdeep City | Mostaccideep City | Mostaccioli |
| Sootopolis City | Sugopolis City | Sugo (sauce) |
| Pacifidlog Town | Paccheridlog Town | Paccheri |
| Ever Grande City | Fettuccine Grande City | Fettuccine (the title) |
| Battle Frontier | Bucatini Frontier | Bucatini |
| Petalburg Woods | Pestoburg Woods | Pesto (matches Pestoburg) |
| New Mauville | New Macaroville | Macaroni (matches Macaroville) |
| Rusturf Tunnel | Rotiturf Tunnel | Rotini + Vermiturf |

## Landmark names

**Done.** Key landmarks also get pasta names, in location names, the PokéNav, and dialogue.

| Original | New name | Pasta reference |
| --- | --- | --- |
| Mt. Chimney | Mt. Calzone | Calzone (oozing like lava) |
| Mt. Pyre | Mt. Penne | Penne |
| Meteor Falls | Meatball Falls | Meatballs |
| Cave of Origin | Cave of Oregano | Oregano |
| Sky Pillar | Sky Breadstick | Breadstick |
| Terra Cave (Groudon) | Terramisu Cave | Tiramisu |
| Marine Cave (Kyogre) | Marinara Cave | Marinara |

## Starters

The player picks one of three starters from different generations. They replace Treecko, Torchic, and Mudkip.

| Starter | Type | Final evolution | Play style |
| --- | --- | --- | --- |
| Rowlet (Gen 7) | Grass/Flying | Decidueye (Grass/Ghost) | Steady physical attacker |
| Scorbunny (Gen 8) | Fire | Cinderace | Fast physical attacker |
| Froakie (Gen 6) | Water | Greninja (Water/Dark) | Fast special attacker |

Balance notes:

- All three final evolutions have a base stat total of 530 and evolve at similar levels.
- None of them can Mega Evolve, because the new Megas from Legends Z-A are excluded for now.
- Roxanne's Rock types are tough for Rowlet and Scorbunny; consider slightly lower levels for her team or an easy early catch with a type advantage.
- Scorbunny has the easiest time against Brian and Rowlet the hardest; tweak Brian's moves or levels based on the player's starter (Emerald already varies the rival's team by starter).

**Done.** Birch's bag offers Rowlet (left), Scorbunny (middle), and Froakie (right). The woman in the Pestoburg Pokémon Center who explains your starter's type is updated too.

- **Until the Brian feature is done,** the rival's teams still use Treecko, Torchic, and Mudkip.

## Shops and Pokémon Centers

### Retro Salvage Games (replaces every Poké Mart)

- **Decided:** Every Poké Mart becomes a **Retro Salvage Games** shop.
- **Decided:** **Jason** runs every shop, with different dialogue in each town. That's about 11 shops, plus he replaces one of the shopkeepers in the Lilycove Department Store and is the shopkeeper at the Pokémon League.
- **Decided:** Every customer NPC in the shops talks about how awesome Retro Salvage Games is.
- **Decided:** Jason's sprite is a recolor of an existing NPC sprite (palette edit only, no new drawing).
- **Decided:** Shop roofs are orange instead of blue. This is a palette change; check that no other buildings share that palette, or they'll turn orange too.
- The "MART" sign on the roof is part of the building's tile graphics and needs a new tile.
- Replace any in-game text that says "Poké Mart."

### Nurse Joy and the Jammie Dodger

- **Decided:** Talking to Nurse Joy skips the usual "Would you like me to heal your Pokémon?" exchange.
- Sequence: she says **"Here, have a Jammie Dodger!"**, the **"item obtained" fanfare** plays, the party is healed, and she says **"Seems like your Pokémon loved it!"**
- **Decided:** The healing machine animation is skipped.
- This is one shared script, so the change applies to every Pokémon Center at once.
- **Decided:** after the player blacks out and wakes up in a Pokémon Center, Nurse Joy says **"QUICK! TAKE THIS COOKIE!"**, the "item obtained" fanfare plays, the party is healed (no healing machine), and she says **"Looks like they ate it all, that was a close one..."** This replaces the usual "restore your Pokémon" and Potion-tip lines.
- Blacking out before reaching the first Pokémon Center (Mom heals you at home) is unchanged.
- **Done** (both the normal and blackout versions).

## Characters and sprites

- **Decided:** The player keeps the boy/girl choice.
- **Decided:** Player sprites use community Gen 3-style sprites of **Ethan** (boy) and **Kris from Crystal** (girl), from PokéCommunity or The Spriters Resource, with credit to the artists. Pick packs with full sheets: walking, running, biking, surfing, fishing, field moves, and a battle back sprite with the throw animation. Rearrange frames to match Emerald's layout if needed.
- **Decided:** No recolor; use the Ethan and Kris sprites as they are.
- **Decided:** The rival is always **Brian**, regardless of the player's gender choice. Replace the Brendan/May rival logic, name, dialogue, front battle sprite, and overworld sprite.
- Sprites are indexed PNGs with 16 colors each (one transparent).

## Brian's story

Brian is a proud Canadian who hates all Italian food. He wants to become Champion so he can rid the world of it, and he won't let the player get in his way. In a region where every town is named after pasta, he's surrounded by everything he hates.

**Decided:** Brian stays a pasta hater forever, even after he loses.

**Decided:** Brian fills three roles from Emerald: **the rival, Wally, and the Champion** (replacing Wallace). His appearances:

1. **Route 103 (first battle).** Introduces his hatred of Italian food and his goal of becoming Champion.
2. **Petalburg City and Route 102 (replaces Wally's catch scene).** Instead of meeting Wally, the player finds Brian demanding that Norman help him catch his second Pokémon. The scene plays out as normal, with the player helping Brian catch **Snover** (his future Mega Abomasnow). This is a scene, not a battle.
3. **Rotiniboro City.** Complains about the town's name and vows to rename it once he wins.
4. **Macaroville City (replaces Wally's battle in Mauville).** Brian just lost to the Mauville Gym and takes his anger out on the player. (It doesn't help that the city is named after macaroni.)
5. **Route 110.** Starts to see the player as a real obstacle to his plan.
6. **Route 119 / Linguicove City.** His frustration peaks; the player is the only thing standing between him and a pasta-free world.
7. **Victory Road (replaces Wally's final battle).** After losing, Brian is furious and runs ahead to the Elite Four.
8. **Champion battle.** Brian beats the Elite Four before the player arrives and becomes the new Champion. The player has to beat him one last time to become Champion.

### Wallace at the Pokémon League

- Wallace is no longer the Champion. After Victory Road, he's standing outside the Elite Four entrance in Fettuccine Grande.
- Talking to him gets a line along the lines of: "That angry fellow who hates pasta just stormed through here... and he's the new Champion!" (draft wording)
- **Decided:** In the post-game, after the player becomes Champion, Wallace stays in the same spot. Talking to him starts a challenge to see whether the new Champion is the real deal, using his original Emerald Champion team.

### Notes on merging the roles

- Brian battles the player seven times; his team has to grow consistently across all of them, with his full team at its highest levels for the Champion battle.
- Wally's scenes need new reasons for Brian to be there. Mauville is decided (he lost to the gym). **Decided:** Verdanturf is dropped; Brian doesn't appear there, and Wally's relatives' house becomes an ordinary NPC house.
- Confirm that the rival and Wally never appear in the same scene by searching the scripts.
- The Champion's trainer data, room, and dialogue all switch to Brian.

### Brian's team (Champion battle)

**Decided:** Canadian-themed, with Swanna as his ace and a Mega Abomasnow, as balanced as possible while keeping the theme: seven different types, and no single attacking type hits more than three of his Pokémon super-effectively. Brian has no starter.

| Pokémon | Type | Canadian link |
| --- | --- | --- |
| Bibarel | Normal/Water | Beaver, Canada's national animal |
| Abomasnow (Mega) | Grass/Ice | Sasquatch of the snowy forests |
| Swanna | Water/Flying | Stand-in for the Canada goose; his ace |
| Wyrdeer | Normal/Psychic | The closest thing to a moose |
| Sawsbuck (Autumn form) | Normal/Grass | Maple-leaf colors, a nod to maple syrup |
| Alolan Ninetales | Ice/Fairy | Arctic fox; its Aurora Veil move is the northern lights |

- **Swanna is his ace,** saved for last, and its shiny Canada goose colors are the big reveal. Give it an ace build (highest level, perfect IVs, a good item and strong moveset); its stats are modest for an ace, so consider buffing its base stats.
- **Swanna is also his day-one partner.** Players never see the rival pick a starter, so Ducklett is his first Pokémon and the one he uses in the Route 103 battle. Bidoof joins later.
- **Abomasnow Mega Evolves** in later battles, so Brian needs a Key Stone in the story.
- **Lock Sawsbuck to its Autumn form** in his trainer data.
- **Decided: Brian's Swanna is recolored as a Canada goose:** black head and neck, a white chinstrap patch, a gray-brown body, a pale chest, and a black beak and tail. Same approach as Sam's Metagross: Brian's Swanna is shiny in his trainer data, and Swanna's shiny palette gets the goose colors, so any shiny Swanna the player finds is a Canada goose too. Because the white chinstrap and black neck may share a color with the rest of the body, the sprite probably needs a few pixel edits in Aseprite as well as the palette change. Brian's Ducklett stays normal-colored in earlier battles, so the goose colors are a surprise when it evolves.
- **Watch out for Fire.** Abomasnow, Sawsbuck, and Ninetales are all weak to it. Bibarel and Swanna can switch in against Fire types; give the others coverage moves.
- Earlier battles use pre-evolved forms (Ducklett, Snover, Bidoof, Stantler, Deerling, Alolan Vulpix) as the team grows.

## Retrotopia cast

| Person | Replaces | Role in the game |
| --- | --- | --- |
| Alan | Professor Birch | Gives the player their starter and introduces the world |
| Sam | Steven Stone | Kind mentor, gives the player the Key Stone, secret post-game boss |
| Joe | Game designer (Cove Lily Motel, Linguicove) | Awards the diploma for completing the Pokédex |
| Brian | The rival, Wally, and Wallace (Champion) | See Brian's story |
| Jason | Every shopkeeper | Runs every Retro Salvage Games shop |

**Decided:** Alan, Sam, and Joe all get custom sprites (overworld; Sam also needs a battle sprite; Alan also needs the large Birch portrait from the opening scene).

### Alan as Birch

- The lovable British gentleman of Retrotopia, and the first character players meet.
- Loves Italian food, which makes him a natural foil for Brian.
- **Decided:** His love of whiskey is a running joke in his dialogue.
- The Jammie Dodgers at the Pokémon Centers can come from Alan's own stash.

### Sam as Steven

- The heart of Retrotopia: kind and always looking out for the player.
- Instead of rare stones, Sam collects rare Wisconsin cheeses.
- **Decided:** Sam gives the player the **Key Stone in Granite Cave** when they first meet him. Spread Mega Stones across the rest of the game so players can't Mega Evolve something powerful too early.
- Steven's post-game battle at Meteor Falls becomes Sam's.

#### Sam's team (post-game battle)

Every Pokémon is from Gens 1–3 and has a cheese connection.

| Pokémon | Gen | Type | Cheese link |
| --- | --- | --- | --- |
| Metagross (shiny, Mega, ace) | 3 | Steel/Psychic | The Big Cheese, recolored cheddar yellow |
| Miltank | 2 | Normal | Dairy cow, for Wisconsin, "America's Dairyland" |
| Tauros | 1 | Normal | Dairy bull, Miltank's partner on the farm |
| Raichu | 1 | Electric | A mouse, and mice love cheese |
| Ampharos | 2 | Electric | A yellow sheep, for sheep's-milk cheeses like feta |
| Lunatone | 3 | Rock/Psychic | Yellow crescent moon shaped like a cheese wedge; the moon is made of cheese |

- **Decided: shiny cheddar Metagross.** Sam's Metagross is shiny in his trainer data, and Metagross's shiny palette is recolored cheddar yellow (Mega Metagross's shiny palette too). Any shiny Metagross the player finds will also be yellow.
- **Balance:** Ground is the biggest weakness, hitting Metagross, Raichu, and Ampharos (Lunatone is immune thanks to Levitate). Give the team coverage moves for Ground types, such as Grass Knot on Raichu, Ice Punch on Metagross, and Earthquake on Tauros.
- As a post-game boss, the whole team should have high levels, good items, and strong movesets.

### Joe as the game designer

- Replaces the Game Freak developer cameo in the Cove Lily Motel.
- Awards the diploma for completing the Pokédex.

## Pokémon, moves, items and abilities

All built into pokeemerald-expansion; the work is deciding where things appear.

- **All Pokémon through Gen IX.** **Decided:** every Gen 3 Pokémon stays where it is in Emerald. Where the other generations appear, and the regional Dex order, will be planned later.
- **Every item, ability, and move effect through Gen IX.** Still to plan: where items are found or sold, and which TMs exist.
- **Physical/special split.** Built in and on by default.

## Battle mechanics

- **Mega Evolution.** Built in. Key Stone from Sam in Granite Cave. Mega Stone locations will be decided by Joe later; don't place them without asking. **Decided:** the new Megas from Legends Z-A are excluded for now.
- **Primal Reversion (Kyogre and Groudon).** Built in; triggers when they hold the Blue Orb or Red Orb. **Decided:** the orbs come from the elderly couple at the Mt. Pyre summit, as in Omega Ruby/Alpha Sapphire (Emerald never gives them to the player).
- **Double wild battles.** Config option with an adjustable encounter chance. **Done:** 15% chance; always a single battle when the player has only one usable Pokémon.
- **1v2 / 2v1 battles.** Supported by the engine; set up per trainer encounter in event scripts.

## Battle UI and speed

Mostly quality-of-life config options. Feature names change between expansion versions, so read `include/config/` and report what this copy offers before editing.

**Done** except faster AI. Most were already on by default; Run shortcut and skipping the intro slide were turned on. Simultaneous HP reduction is built in (confirmed in playtest). Faster AI has no speed setting: it means choosing simpler AI flags for ordinary trainers, measured with `DEBUG_AI_DELAY_TIMER`.

- **Poké Ball quick menu** ("last used ball" shortcut). R throws the last ball; hold R and press the D-Pad to switch.
- **Move description menu** in the fight menu. Press L while choosing a move.
- **Shortcut to Run** in wild battles. B jumps the cursor to Run.
- **Faster battle intro.**
- **Faster HP drain.**
- **Simultaneous HP reduction** for spread moves in doubles.
- **Faster AI calculations** (AI config flags plus possible code tuning).

## Overworld and menus

- **HMs are not permanent.** HM moves can be forgotten like normal moves. **Decided:** field moves only need the badge plus the HM in the bag; no Pokémon has to know the move. Forgetting HMs is **done** (config). Using field moves without knowing them is still custom work.
- **Move relearner in the party menu.** A "Relearn" option on each Pokémon. This version already has a relearner on the summary screen's moves page. **Decided:** add it as a party-menu option anyway (custom).
- **PC access anywhere via a bag item.** A key item that opens the storage system. Likely custom.
- **"Move" as the default PC option.** Storage opens straight into Move mode. Small code change. "Move Pokémon" is already the first PC menu option, with the cursor on it; skipping the menu entirely would be a further small change.

## Randomizer option at game start

A yes/no choice at New Game that randomizes Pokémon for that save file. It must run inside the ROM at runtime (save-file flag plus a seed), not as a separate patching tool. **Build this last.**

**Decided:**

- Randomizes **wild Pokémon, starters, and trainer teams**.
- **Full random** (no matching by strength).
- **No exclusions;** legendaries can appear anywhere.
- **Simple on/off.** The New Game prompt must tell the player exactly what gets randomized: wild Pokémon, starters, and trainer teams.

## Feature tracker

| Feature | Type of work | Status |
| --- | --- | --- |
| Pasta town names | Text, signs, Town Map | Done |
| Pasta landmark names | Text, Town Map | Done |
| Pasta region name: Pastalia (replaces Hoenn) | Text, plus 2 PokéNav graphics | Text done; PokéNav "HOENN MAP" art still to redraw |
| Starters: Rowlet, Scorbunny, Froakie | Script and data change | Done |
| Nurse Joy Jammie Dodger heal (plus blackout cookie) | One shared script change | Done |
| Retro Salvage Games shops (Jason, orange roofs) | Sprite recolor, palette, tiles, dialogue | Not started |
| Main character sprites (Ethan and Kris) | Community sprites, no recolor | Not started |
| Brian as rival (sprites, name, logic, anti-pasta story) | Art plus code and dialogue | Not started (rival teams still use old Hoenn starters) |
| Brian replaces Wally (Petalburg catch, Mauville, Victory Road) | Scripts and dialogue | Not started |
| Brian as Champion, Wallace outside the Elite Four | Scripts, trainer data, dialogue | Not started |
| Retrotopia cast: Alan (Birch), Sam (Steven), Joe (designer) | Custom sprites, scripts, dialogue | Not started |
| All Pokémon through Gen IX | Built in; plan placement | Not started |
| Items, abilities, move effects through Gen IX | Built in; plan placement | Not started |
| Physical/special split | Built in | Done (built in) |
| Mega Evolution (Key Stone from Sam in Granite Cave) | Built in; place Key Stone and Mega Stones | Not started |
| Primal Reversion | Built in; place Blue/Red Orbs | Not started |
| Double wild battles | Config toggle | Done (config, 15%) |
| 1v2 / 2v1 battles | Event scripting | Not started |
| Poké Ball quick menu | Config toggle | Done (built in) |
| Move description menu | Verify in config | Done (built in) |
| Shortcut to Run | Verify in config | Done (config) |
| Faster battle intro | Config toggle | Done (config) |
| Faster HP drain | Config toggle | Done (built in) |
| Simultaneous HP reduction | Verify in config | Done (built in) |
| Faster AI calculations | Config plus tuning | Not started |
| Non-permanent HMs | Config toggle | Partly done: HMs forgettable (config); field moves without knowing the move still custom |
| Move relearner in party menu | Custom (party-menu option) | Not started (summary-screen relearner already exists) |
| PC access via bag item, "Move" default in storage | Custom (small) | Not started |
| Randomizer at New Game | Custom (large) | Not started |

## Suggested build order

Work from easiest to hardest so there's always a playable build.

1. ~~Build pokeemerald-expansion unchanged and confirm it runs in mGBA. (Intel Mac with MacPorts, not Homebrew.)~~ **Done.** devkitARM 16.1.0; the hack lives on the `fettuccine` git branch, based on upstream commit `90c30f02ae`.
2. ~~Audit `include/config/` and report which "Verify" features exist in this version.~~ **Done.**
3. ~~Turn on the config toggles (battle speed, double wilds, HMs) and playtest.~~ **Done.** Legends Z-A Megas turned off.
4. ~~Small visible changes: town names, Nurse Joy, starters.~~ **Done**, plus landmark names.
5. Script the Key Stone (Sam in Granite Cave), Mega Stones, and Orbs into the story.
6. Story and character changes: Brian (rival, Wally, Champion), the Retrotopia cast, Retro Salvage Games.
7. Small custom features: PC item and Move-default storage; party-menu relearner if needed.
8. Sprites (as art becomes available).
9. Randomizer, last.
