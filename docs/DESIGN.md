# Pokémon Fettuccine Version — Design Doc

Working title. A Pokémon Emerald ROM hack built on **pokeemerald-expansion**. This file is the source of truth for what the game should be. Items marked **Decided** are final; items marked **Open** still need a decision from Joe before implementation.

## Overview

Most features below already exist in pokeemerald-expansion as built-in systems or config toggles. The main custom work is the story and character changes, the randomizer, the PC item, and possibly the party-menu move relearner.

Workflow rule: build and test after every change, and `git commit` each working step so any broken edit can be rolled back.

## Region

The game takes place in one region, **Pastalia** (Hoenn renamed; pasta + Italia). Johto and Kanto were considered and cut to keep the scope manageable.

- **Decided and done:** the region is called **PASTALIA** in all dialogue, the Pokédex ("PASTALIA DEX"), the PokéNav, the Town Map title, and the diploma.
- **Still to do (art):** two PokéNav graphics have "HOENN MAP" drawn into the pixels: `graphics/pokenav/options/hoenn_map.png` and `graphics/pokenav/left_headers/hoenn_map.png`. They need "PASTALIA MAP" (or similar) redrawn in Aseprite.
- **Still to do (art):** the Pokédex list screen draws "HOENN" from `graphics/pokedex/interface.png` (the label just above "NATIONAL", about two-thirds of the way down the sheet). It needs "PASTALIA" redrawn in the same space; it's 8 letters instead of 5, so it may need a narrower font.

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
| Dewford Town | Ditalinford Town | Ditalini |
| Slateport City | Spaghettiport City | Spaghetti |
| Mauville City | Macaroville City | Macaroni |
| Verdanturf Town | Cavatapurf Town | Cavatappi |
| Fallarbor Town | Farfallarbor Town | Farfalle |
| Lavaridge Town | Lasagnaridge Town | Lasagna |
| Fortree City | Fortellini City | Tortellini |
| Lilycove City | Linguicove City | Linguine |
| Mossdeep City | Mostaccideep City | Mostaccioli |
| Sootopolis City | Sugopolis City | Sugo (sauce) |
| Pacifidlog Town | Raviolog Town | Ravioli |
| Ever Grande City | Fettuccine Grande City | Fettuccine (the title) |
| Battle Frontier | Bucatini Frontier | Bucatini |
| Petalburg Woods | Pestoburg Woods | Pesto (matches Pestoburg) |
| New Mauville | New Macaroville | Macaroni (matches Macaroville) |
| Rusturf Tunnel | Rotipurf Tunnel | Rotini + Cavatapurf |

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
| Marine Cave (Kyogre) | Marsala Cave | Marsala sauce (renamed from Marinara Cave to avoid clashing with Team Marinara) |

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

### Mike at the Pokémon League (replaces Wallace)

- **Decided:** **Mike** (Joe's cousin) takes Wallace's place. Wallace is no longer the Champion; after Victory Road, Mike is standing outside the Elite Four entrance in Fettuccine Grande.
- Talking to him gets a line along the lines of: "That angry fellow who hates pasta just stormed through here... and he's the new Champion!" (draft wording)
- **Decided:** In the post-game, after the player becomes Champion, Mike stays in the same spot. Talking to him starts a challenge to see whether the new Champion is the real deal.
- **Decided:** Mike replaces Wallace **everywhere** (Sugopolis and HM Waterfall, Cave of Origin, Sky Pillar, Mostaccideep, the Champion's Room until Brian takes it over, and every line that mentions him). **Done:** all dialogue and his trainer name say MIKE. Wallace's sprites are his placeholder.
- **Decided:** Mike's ace is an **overpowered Spearow**, a unique Spearow form only he has (`SPECIES_SPEAROW_MIKE`). Wild Spearow are unaffected. Both Mike and his Spearow get custom sprite work by Joe. **Done:** the form exists with boosted stats (80 HP / 145 Atk / 90 Def / 55 SpA / 90 SpD / 140 Spe, 600 total, vs. 262 for Spearow), using Spearow's sprites as a placeholder. Moves: Brave Bird, Double-Edge, Drill Run, U-turn, with a Life Orb.
- **Decided: Mike's team is hyper-Italian,** with a Mega (Gallade). (The earlier three-Gen-1 rule was dropped when Falinks replaced Snorlax.) **Done** (levels 57–60, Spearow last):

| Pokémon | Gen | Type | Italian theme |
| --- | --- | --- | --- |
| Smeargle | 2 | Normal | Renaissance painter (leads with Spore and Sticky Web) |
| Chandelure | 5 | Ghost/Fire | Murano glass chandelier |
| Lapras | 1 | Water/Ice | Venetian gondola (knows Sing, like a gondolier) |
| Falinks | 8 | Fighting | A Roman legion marching in shield formation |
| Gallade (Mega) | 4 | Psychic/Fighting | Roman gladiator; holds a Galladite and Mega Evolves |
| Spearow (Mike's form, ace) | 1 | Normal/Flying | Mike's overpowered ace |

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
- **Abomasnow Mega Evolves** in later battles, so Brian needs a Mega Ring in the story (story flavor only: trainers Mega Evolve without one).
- **Lock Sawsbuck to its Autumn form** in his trainer data.
- **Decided: Brian's Swanna is recolored as a Canada goose:** black head and neck, a white chinstrap patch, a gray-brown body, a pale chest, and a black beak and tail. Same approach as Sam's Metagross: Brian's Swanna is shiny in his trainer data, and Swanna's shiny palette gets the goose colors, so any shiny Swanna the player finds is a Canada goose too. Because the white chinstrap and black neck may share a color with the rest of the body, the sprite probably needs a few pixel edits in Aseprite as well as the palette change. Brian's Ducklett stays normal-colored in earlier battles, so the goose colors are a surprise when it evolves.
- **Watch out for Fire.** Abomasnow, Sawsbuck, and Ninetales are all weak to it. Bibarel and Swanna can switch in against Fire types; give the others coverage moves.
- Earlier battles use pre-evolved forms (Ducklett, Snover, Bidoof, Stantler, Deerling, Alolan Vulpix) as the team grows.

## Villain teams: White Sauce vs. Red Sauce

Decided: Team Aqua and Team Magma become two rival sauce fanatics, each convinced theirs is the one true sauce. (This replaced the earlier "sauce vs. boil" theme, Team Marinara vs. Team Al Dente.)

**Team Alfredo** (replaces Team Aqua). Obsessed with white sauce: Alfredo and sauces like it. Wants to wake Kyogre and flood the world with their ideal sauce.
**Team Marinara** (replaces Team Magma). Passionate about red sauce: marinara and sauces like it. Wants to wake Groudon so the world's volcanoes spray red sauce everywhere.

What this touches:

Team names in all dialogue, signs, and trainer classes (for example, "Team Alfredo Grunt").
Recolored grunt and admin sprites to match each team.
Story dialogue for both leaders and their admins.

Status:

- **Done:** team names in all dialogue and signs; trainer classes TEAM ALFREDO, ALFREDO ADMIN, ALFREDO LEADER, TEAM MARINARA, MARINARA ADMIN, MARINARA LEADER; hideouts renamed ALFREDO HIDEOUT and MARINARA HIDEOUT; the Magma Emblem key item is now the Marinara Emblem. Admin names (Shelly, Matt, Tabitha, Courtney) are unchanged.
- **Done:** leaders renamed. Archie is now **PARMIGIANO** (Parmesan, the cheese in Alfredo) and Maxie is now **MARZANO** (San Marzano, the marinara tomato). These replace the earlier names Marzano (Archie) and Bollito (Maxie).
- **Done:** white-vs-red dialogue for every villain scene: the Oceanic Museum, Meatball Falls, Mt. Calzone (including the Route 112 cable car guards), the Weather Institute (including the Route 119 bridge lookouts), the Mt. Penne summit (orb theft and the old couple's legends), and both hideouts (including the Team Alfredo lines around Linguicove), the Mostaccideep Space Center, the Seafloor Cavern (and the Route 128 scene right after), plus the grunts' jokes there. Kyogre's downpour is a downpour of Alfredo sauce. The Pokédex entries for Groudon, Kyogre, their Primal forms, and Rayquaza also tell the sauce legend. Sugopolis is done too: the townspeople describe the clash as a sauce legend, and one calls Kyogre "the white one" (this relies on the cream Kyogre recolor). The leaders' lines in Sugopolis, Wallace's lines, and the orb return at Mt. Penne didn't need changes. All villain story scenes are now on the white-vs-red plot; Joe may revise any of these lines later.
- **Not started:** recolored sprites (art). Team Marinara can keep Team Magma's red outfits. Team Alfredo's grunt, admin, and leader sprites need a white or cream recolor instead of blue.
- **Not started: Kyogre recolored cream instead of blue** (art). Covers its battle sprites and overworld sprites (the asleep, front, and side views used in the Seafloor Cavern and Sugopolis scenes). Check which palettes are shared before changing them.
- **Decided:** dialogue tone is mostly serious for leaders and admins (sincere villains whose worldview is built on sauce), with the jokes and puns going to the grunts.
- **Decided: keep Team Alfredo's dialogue free of innuendo.** White sauce is easy to read as a sexual joke, so lean on butter, cheese, Parmesan, and "Alfredo sauce" rather than "cream". Avoid pairing white sauce or cream with words like squirt, spray, shoot, load, slurp, swallow, thick, sticky, or "all over", and with bodies or faces. Team Marinara's red sauce can erupt and spray; Team Alfredo's sauce floods and covers.
- **Decided:** rewrite key scenes first, starting with the leader introductions, then the other scenes one at a time.

**Decided:** Brian does not show up during the teams' schemes. (Considered: both teams want more pasta while Brian wants it gone, so he could have appeared furious, on the player's side. Dropped.)

## Retrotopia cast

| Person | Replaces | Role in the game |
| --- | --- | --- |
| Alan | Professor Birch | Gives the player their starter and introduces the world |
| Sam | Steven Stone | Kind mentor, gives the player the Mega Ring, secret post-game boss |
| Joe Fettuccine | Game designer (Cove Lily Motel, Linguicove) | Awards the diploma for completing the Pokédex |
| Brian | The rival, Wally, and Wallace (Champion) | See Brian's story |
| Jason | Every shopkeeper | Runs every Retro Salvage Games shop |

**Decided:** Alan, Sam, and Joe Fettuccine all get custom sprites (overworld; Sam also needs a battle sprite; Alan also needs the large Birch portrait from the opening scene).

### Alan as Birch

- The lovable British gentleman of Retrotopia, and the first character players meet.
- Loves Italian food, which makes him a natural foil for Brian.
- **Decided:** His love of whiskey is a running joke in his dialogue.
- The Jammie Dodgers at the Pokémon Centers can come from Alan's own stash.

### Sam as Steven

- The heart of Retrotopia: kind and always looking out for the player.
- Instead of rare stones, Sam collects rare Wisconsin cheeses.
- **Decided:** Sam gives the player the **Mega Ring in Granite Cave** when they first meet him. Spread Mega Stones across the rest of the game so players can't Mega Evolve something powerful too early.
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

### Joe Fettuccine as the game designer

- Replaces the Game Freak developer cameo in the Cove Lily Motel.
- Awards the diploma for completing the Pokédex.

## Joe's cousins

| Person | Replaces | Role in the game |
| --- | --- | --- |
| Mike | Wallace | Waits outside the Elite Four; post-game challenge with an overpowered Spearow ace (see "Mike at the Pokémon League") |
| Joe Q | Scott | Scott's role, with dialogue changes |

- **Decided:** Joe Q is a different person from Joe Fettuccine (the game designer).
- **Decided:** Mike and his Spearow get custom sprites (placeholder for now). Joe Q keeps Scott's sprite.

## Trainer and Gym Leader teams

- **Decided:** every trainer and Gym Leader gets a different team from base Emerald, drawn from Pokémon of Gens 1–9. Each keeps their current theme (for example, a Bug Catcher still uses Bug types and a Gym Leader keeps their gym's type).
- **Decided:** this is a fixed set of new teams that every player gets. It is separate from the optional randomizer at New Game.
- **Decided:** from the 3rd gym on, each Gym Leader has a Mega-Evolving Pokémon.
- **Decided:** trainers' names are replaced with names from the Retrotopia community. Joe will supply the list; build this near the end.

## Pokémon, moves, items and abilities

All built into pokeemerald-expansion; the work is deciding where things appear.

- **All Pokémon through Gen IX.** **Decided:** every Gen 3 Pokémon stays where it is in Emerald. Where the other generations appear, and the regional Dex order, will be planned later.
- **Every item, ability, and move effect through Gen IX.** Still to plan: where items are found or sold, and which TMs exist.
  - **Done: evolution counter.** A third clerk on the Linguicove Department Store's 3rd floor sells all 51 items any Pokémon uses to evolve: every evolution stone, the Linking Cord, every held trade item (Metal Coat, King's Rock, Dragon Scale, Up-Grade…), and the newer items (apples, teacups, sweets, Galarica items, armors, Black Augurite, Peat Block, Metal Alloy, both Scrolls). The Scrolls had no price, so they now cost ¥3,000.
- **Physical/special split.** Built in and on by default.

## Battle mechanics

- **Mega Evolution.** Built in. **Done:** Steven (Sam) gives the **Mega Ring** in Granite Cave, right after TM Steel Wing, and hints that a Mega Stone is hidden in the same cave (the Aggronite). **Decided:** the item keeps the engine's name, Mega Ring (Joe briefly tried "Key Stone" and switched back). **Decided:** the new Megas from Legends Z-A are excluded for now.
  - **Decided: no Mega Stone is locked behind the post-game.** Every stone is obtainable before the final battle with Brian. Stones are found as item balls, and each appears around when its Pokémon can reach its final form.
  - **Done: every Mega-capable Pokémon is now obtainable before Brian** (see "Pokémon added for Mega Evolution" below), so all 46 non-Z-A Mega Stones are in the game.
  - **Decided: Marzano Mega Evolves Camerupt** (Space Center double battle) and **Parmigiano Mega Evolves Sharpedo** (Seafloor Cavern).
  - **Done: all Mega Stones placed.** 39 are item balls (Joe may move any of them in Porymap), and Prof. Birch (Alan) gives the 7 starter stones.

| Stone | Where | Unlocked by |
| --- | --- | --- |
| Aggronite | Granite Cave B2F | Early (Aggron is level 42) |
| Manectite | New Macaroville | Basement Key, after Gym 3 |
| Gardevoirite, Galladite | Pestoburg City, north pond | Surf, after Gym 5 |
| Dawn Stone (for Gallade) | Pestoburg City, southwest | Early |
| Banettite | Mt. Penne 5F | Mid-game |
| Cameruptite | Marinara Hideout 4F | Marinara Hideout |
| Sharpedonite | Alfredo Hideout B2F | Alfredo Hideout |
| Pinsirite, Heracronite | Safari Zone (Northwest, North) | Linguicove |
| Ampharosite, Houndoominite | Safari Zone expansion (Southeast, Northeast) | Linguicove |
| Altarianite | Fortellini City, by the Gym | Fortellini |
| Absolite | Route 120 | After Fortellini |
| Glalitite | Shoal Cave, ice room | Mostaccideep area |
| Alakazite | Mostaccideep City | Gym 7 area |
| Metagrossite | Sam's house, Mostaccideep | Mostaccideep (Beldum is a gift there after the Space Center) |
| Gyaradosite | Sugopolis City, by the Pokémon Center | Dive |
| Sablenite | Cave of Oregano 1F | Sugopolis |
| Latiasite, Latiosite | Routes 132 and 133, near Raviolog | Late game |
| Salamencite | Meatball Falls B1F (back room) | Waterfall |
| Mawilite | Victory Road B1F | Victory Road |
| Beedrillite | Route 110 | After Gym 3 |
| Lopunnite, Audinite | Cavatapurf Town, by the Pokémon Center | Mid-game |
| Gengarite | Mt. Penne 6F | Mid-game |
| Medichamite | Route 118 | After Gym 5 |
| Aerodactylite | Route 111 desert | Go-Goggles |
| Pidgeotite | Fortellini City, by the Gym | Fortellini |
| Scizorite | Route 120 | After Fortellini |
| Lucarionite | Route 121 | After Gym 6 |
| Slowbronite | Linguicove City | Linguicove |
| Kangaskhanite | Safari Zone South | Linguicove |
| Abomasite | Shoal Cave, ice room | Mostaccideep area |
| Diancite | Meatball Falls B1F (back room), next to Diancie | Waterfall |
| Steelixite, Garchompite, Tyranitarite | Victory Road | Victory Road |
| Mewtwonite X and Y | Victory Road, near Mewtwo | Victory Road |
| Sceptilite, Blazikenite, Swampertite, Venusaurite, Charizardite X and Y, Blastoisinite | Gift from Prof. Birch (Alan) at his lab | He calls right after Scott's call, once you have 6 badges |

  - **Done: Safari Zone expansion open from the start** (Mareep and Houndour live there; in Emerald it opened after the Hall of Fame).
  - **Done: the Latias/Latios roamer starts after the Sugopolis crisis,** when Wallace gives HM Waterfall and mentions reports of a rare red or blue Pokémon (picked at random). In Emerald it started after the Hall of Fame.
  - **Done: Beldum is offered by Steven (Sam) with HM Dive** after the Space Center, instead of after the Hall of Fame.
  - **Done: trade evolutions without trading.** Two Linking Cords (Routes 110 and 123) evolve Kadabra, Haunter and other trade Pokémon. `I_USE_EVO_HELD_ITEMS_FROM_BAG` is on, so held-item trade evolutions (Metal Coat, Dragon Scale, Electirizer…) work by using the item from the bag. Two Metal Coats are placed (New Macaroville, Route 121) for Steelix and Scizor.

### Pokémon added for Mega Evolution

**Decided:** these Pokémon were added so every Mega Stone is usable before the final battle with Brian. New wild Pokémon take over a slot of a species that already appears two or more times in that area, so every Gen 3 Pokémon stays where it was in Emerald.

| Pokémon | Where |
| --- | --- |
| Weedle | Pestoburg Woods |
| Pidgey | Routes 102, 103, 104 |
| Bulbasaur, Buneary, Audino | Route 117 (rare) |
| Slowpoke | Route 117 (surfing), Shoal Cave (surfing) |
| Onix | Granite Cave 1F, Rotipurf Tunnel |
| Snover | Shoal Cave, ice room |
| Gastly | Mt. Penne 1F–6F |
| Meditite | Mt. Penne outside and summit |
| Larvitar, Gible | Route 111 desert (rare) |
| Scyther, Treecko | Route 119 (rare) |
| Torchic | Fiery Path (rare) |
| Charmander | Route 112 (rare) |
| Squirtle | Route 118 (surfing) |
| Mudkip | Route 120 (rare) |
| Kangaskhan | Safari Zone South |
| Riolu | Egg from a Black Belt next to the Ditalinford Gym |
| Aerodactyl | Old Amber from the Fossil Maniac (Route 114), revived at Devon in Rotiniboro |
| Diancie | One-time encounter, Lv 50, Meatball Falls B1F back room |
| Mewtwo | One-time encounter, Lv 70, Victory Road B2F |

Diancie and Mewtwo stay put if the player knocks them out or runs, so they can be retried.
- **Primal Reversion (Kyogre and Groudon).** Built in; triggers when they hold the Blue Orb or Red Orb. **Decided:** the orbs come from the elderly couple at the Mt. Pyre summit, as in Omega Ruby/Alpha Sapphire (Emerald never gives them to the player). **Done:** after Marzano and Parmigiano return the orbs (after Sugopolis, before the Elite Four), the old woman gives the player both orbs. If the bag is full, she offers them again later. **Done:** Terramisu Cave (Groudon) and Marsala Cave (Kyogre) open at the same point instead of after the Hall of Fame: the Weather Institute scientist (2F) reports the abnormal weather once the orbs are returned, and the old woman points the player there.
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
- **Decided: battle speed option.** A setting in the Options menu that doubles battle speed without speeding up the overworld.

## Overworld and menus

- **Done: the player starts with the Running Shoes.** Mom's scene in Lil Ragu Town after getting the starter is now just a goodbye.
- **Done: the player starts with the Shiny Charm** in the bag (it only works from the bag, not the PC).
- **Decided: faster berry picking**, quick or near instant.

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
| Villain teams: Alfredo and Marinara (names) | Text, trainer classes | Done |
| Villain teams: recolored sprites | Palette edits | Not started |
| Kyogre recolored cream | Palette edits, possibly pixel edits | Not started |
| Villain teams: white vs. red sauce story dialogue | Dialogue | Done |
| Villain leaders renamed: Parmigiano and Marzano | Text, trainer data | Done |
| Pasta region name: Pastalia (replaces Hoenn) | Text, plus 2 PokéNav graphics and 1 Pokédex graphic | Text done; PokéNav "HOENN MAP" and Pokédex "HOENN" art still to redraw |
| Starters: Rowlet, Scorbunny, Froakie | Script and data change | Done |
| Nurse Joy Jammie Dodger heal (plus blackout cookie) | One shared script change | Done |
| Retro Salvage Games shops (Jason, orange roofs) | Sprite recolor, palette, tiles, dialogue | Not started |
| Main character sprites (Ethan and Kris) | Community sprites, no recolor | Not started |
| Brian as rival (sprites, name, logic, anti-pasta story) | Art plus code and dialogue | Not started (rival teams still use old Hoenn starters) |
| Brian replaces Wally (Petalburg catch, Mauville, Victory Road) | Scripts and dialogue | Not started |
| Brian as Champion, Mike (replaces Wallace) outside the Elite Four | Scripts, trainer data, dialogue, custom sprites | Not started |
| Joe Q replaces Scott | Dialogue, names | Not started |
| New themed teams for all trainers and Gym Leaders (Gens 1–9, Megas from gym 3) | Trainer data | Not started |
| Trainer names from the Retrotopia community | Text (waiting on Joe's list) | Not started |
| Retrotopia cast: Alan (Birch), Sam (Steven), Joe Fettuccine (designer) | Custom sprites, scripts, dialogue | Not started |
| All Pokémon through Gen IX | Built in; plan placement | Not started |
| Items, abilities, move effects through Gen IX | Built in; plan placement | Not started |
| Physical/special split | Built in | Done (built in) |
| Mega Evolution (Mega Ring from Sam in Granite Cave) | Built in; place Mega Ring and Mega Stones | Done |
| Primal Reversion | Built in; place Blue/Red Orbs | Done (orbs given at Mt. Penne) |
| Double wild battles | Config toggle | Done (config, 15%) |
| 1v2 / 2v1 battles | Event scripting | Not started |
| Poké Ball quick menu | Config toggle | Done (built in) |
| Move description menu | Verify in config | Done (built in) |
| Shortcut to Run | Verify in config | Done (config) |
| Faster battle intro | Config toggle | Done (config) |
| Faster HP drain | Config toggle | Done (built in) |
| Simultaneous HP reduction | Verify in config | Done (built in) |
| Faster AI calculations | Config plus tuning | Not started |
| Battle speed option (battles only) | Custom (Options menu) | Not started |
| Non-permanent HMs | Config toggle | Partly done: HMs forgettable (config); field moves without knowing the move still custom |
| Move relearner in party menu | Custom (party-menu option) | Not started (summary-screen relearner already exists) |
| PC access via bag item, "Move" default in storage | Custom (small) | Not started |
| Start with Running Shoes | New-game setup, Mom's script | Done |
| Start with Shiny Charm | New-game setup | Done |
| Faster berry picking | Config or small code change | Not started |
| Randomizer at New Game | Custom (large) | Not started |

## Suggested build order

Work from easiest to hardest so there's always a playable build.

1. ~~Build pokeemerald-expansion unchanged and confirm it runs in mGBA. (Intel Mac with MacPorts, not Homebrew.)~~ **Done.** devkitARM 16.1.0; the hack lives on the `fettuccine` git branch, based on upstream commit `90c30f02ae`.
2. ~~Audit `include/config/` and report which "Verify" features exist in this version.~~ **Done.**
3. ~~Turn on the config toggles (battle speed, double wilds, HMs) and playtest.~~ **Done.** Legends Z-A Megas turned off.
4. ~~Small visible changes: town names, Nurse Joy, starters.~~ **Done**, plus landmark names.
5. Script the Mega Ring (Sam in Granite Cave), Mega Stones, and Orbs into the story.
6. Story and character changes: Brian (rival, Wally, Champion), the Retrotopia cast, Retro Salvage Games.
7. Small custom features: PC item and Move-default storage; party-menu relearner if needed.
8. Sprites (as art becomes available).
9. Randomizer, last.
