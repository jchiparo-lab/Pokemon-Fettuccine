@ Fettuccine: "Story beats" debug page.
@ Each script puts the story flags and vars back to the moment just before a
@ villain scene, then warps the player next to it. For playtesting only: it
@ rewinds or skips story progress, so use it on a throwaway save.

@ Gives all badges, so high-level Pokémon obey, and a strong Pokémon if the
@ party is empty, so every scene's battles work. Aura Sphere covers the Dark
@ types that Psystrike can't hit.
Debug_StoryBeat_EnsureParty:
	setflag FLAG_BADGE01_GET
	setflag FLAG_BADGE02_GET
	setflag FLAG_BADGE03_GET
	setflag FLAG_BADGE04_GET
	setflag FLAG_BADGE05_GET
	setflag FLAG_BADGE06_GET
	setflag FLAG_BADGE07_GET
	setflag FLAG_BADGE08_GET
	getpartysize
	goto_if_ne VAR_RESULT, 0, Debug_StoryBeat_EnsureParty_Done
	givemon SPECIES_MEWTWO, 70, ITEM_NONE, move1 = MOVE_PSYSTRIKE, move2 = MOVE_AURA_SPHERE, move3 = MOVE_ICE_BEAM, move4 = MOVE_FLAMETHROWER
	setflag FLAG_SYS_POKEMON_GET
Debug_StoryBeat_EnsureParty_Done:
	return

@ Spaghettiport Oceanic Museum: talk to Capt. Stern to start the scene.
Debug_StoryBeat_OceanicMuseum::
	call Debug_StoryBeat_EnsureParty
	clearflag FLAG_DELIVERED_DEVON_GOODS
	clearflag FLAG_HIDE_SLATEPORT_CITY_OCEANIC_MUSEUM_2F_CAPTAIN_STERN
	clearflag FLAG_HIDE_SLATEPORT_CITY_OCEANIC_MUSEUM_AQUA_GRUNTS
	setflag FLAG_HIDE_SLATEPORT_CITY_OCEANIC_MUSEUM_2F_ARCHIE
	setflag FLAG_HIDE_SLATEPORT_CITY_OCEANIC_MUSEUM_2F_AQUA_GRUNT_1
	setflag FLAG_HIDE_SLATEPORT_CITY_OCEANIC_MUSEUM_2F_AQUA_GRUNT_2
	setvar VAR_SLATEPORT_MUSEUM_1F_STATE, 1
	cleartrainerflag TRAINER_GRUNT_MUSEUM_1
	cleartrainerflag TRAINER_GRUNT_MUSEUM_2
	checkitem ITEM_DEVON_PARTS
	call_if_eq VAR_RESULT, FALSE, Debug_StoryBeat_GiveDevonParts
	warp MAP_SLATEPORT_CITY_OCEANIC_MUSEUM_2F, 12, 6
	waitstate
	end

Debug_StoryBeat_GiveDevonParts:
	additem ITEM_DEVON_PARTS
	return

@ Meatball Falls: walk left from the arrival spot to trigger the scene.
Debug_StoryBeat_MeteorFalls::
	call Debug_StoryBeat_EnsureParty
	setvar VAR_METEOR_FALLS_STATE, 0
	clearflag FLAG_HIDE_METEOR_FALLS_TEAM_MAGMA
	setflag FLAG_HIDE_METEOR_FALLS_TEAM_AQUA
	clearflag FLAG_HIDE_METEOR_FALLS_1F_1R_COZMO
	clearflag FLAG_MET_ARCHIE_METEOR_FALLS
	warp MAP_METEOR_FALLS_1F_1R, 16, 18
	waitstate
	end

@ Mt. Calzone: arrive at the cable car station at the top of the mountain.
Debug_StoryBeat_MtChimney::
	call Debug_StoryBeat_EnsureParty
	clearflag FLAG_HIDE_MT_CHIMNEY_TEAM_MAGMA
	clearflag FLAG_HIDE_MT_CHIMNEY_TEAM_AQUA
	setflag FLAG_HIDE_MT_CHIMNEY_LAVA_COOKIE_LADY
	clearflag FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY
	clearflag FLAG_EVIL_LEADER_PLEASE_STOP
	cleartrainerflag TRAINER_MAXIE_MT_CHIMNEY
	cleartrainerflag TRAINER_TABITHA_MT_CHIMNEY
	cleartrainerflag TRAINER_GRUNT_MT_CHIMNEY_1
	cleartrainerflag TRAINER_GRUNT_MT_CHIMNEY_2
	warp MAP_MT_CHIMNEY, 0
	waitstate
	end

@ Weather Institute: arrive at the front door.
Debug_StoryBeat_WeatherInstitute::
	call Debug_StoryBeat_EnsureParty
	setvar VAR_WEATHER_INSTITUTE_STATE, 0
	clearflag FLAG_HIDE_ROUTE_119_TEAM_AQUA
	setflag FLAG_HIDE_WEATHER_INSTITUTE_1F_WORKERS
	setflag FLAG_HIDE_WEATHER_INSTITUTE_2F_AQUA_GRUNT_M
	cleartrainerflag TRAINER_GRUNT_WEATHER_INST_1
	cleartrainerflag TRAINER_GRUNT_WEATHER_INST_2
	cleartrainerflag TRAINER_GRUNT_WEATHER_INST_3
	cleartrainerflag TRAINER_GRUNT_WEATHER_INST_4
	cleartrainerflag TRAINER_GRUNT_WEATHER_INST_5
	cleartrainerflag TRAINER_SHELLY_WEATHER_INSTITUTE
	warp MAP_ROUTE119_WEATHER_INSTITUTE_1F, 0
	waitstate
	end

@ Mt. Penne summit (orbs stolen): walk up toward the old couple.
Debug_StoryBeat_MtPyreOrbs::
	call Debug_StoryBeat_EnsureParty
	setvar VAR_MT_PYRE_STATE, 0
	clearflag FLAG_HIDE_MT_PYRE_SUMMIT_ARCHIE
	clearflag FLAG_HIDE_MT_PYRE_SUMMIT_TEAM_AQUA
	setflag FLAG_HIDE_MT_PYRE_SUMMIT_MAXIE
	clearflag FLAG_RECEIVED_RED_OR_BLUE_ORB
	removeitem ITEM_MAGMA_EMBLEM
	cleartrainerflag TRAINER_GRUNT_MT_PYRE_1
	cleartrainerflag TRAINER_GRUNT_MT_PYRE_2
	cleartrainerflag TRAINER_GRUNT_MT_PYRE_3
	cleartrainerflag TRAINER_GRUNT_MT_PYRE_4
	warp MAP_MT_PYRE_SUMMIT, 1
	waitstate
	end

@ Al Dente Hideout: arrive on the floor with Groudon; talk to the leader.
Debug_StoryBeat_MagmaHideout::
	call Debug_StoryBeat_EnsureParty
	clearflag FLAG_GROUDON_AWAKENED_MAGMA_HIDEOUT
	clearflag FLAG_HIDE_MAGMA_HIDEOUT_GRUNTS
	setflag FLAG_HIDE_MAGMA_HIDEOUT_4F_GROUDON
	clearflag FLAG_HIDE_MAGMA_HIDEOUT_4F_GROUDON_ASLEEP
	cleartrainerflag TRAINER_MAXIE_MAGMA_HIDEOUT
	cleartrainerflag TRAINER_TABITHA_MAGMA_HIDEOUT
	cleartrainerflag TRAINER_GRUNT_MAGMA_HIDEOUT_11
	cleartrainerflag TRAINER_GRUNT_MAGMA_HIDEOUT_12
	cleartrainerflag TRAINER_GRUNT_MAGMA_HIDEOUT_13
	warp MAP_MAGMA_HIDEOUT_4F, 1
	waitstate
	end

@ Marinara Hideout: walk left toward Matt and the submarine.
Debug_StoryBeat_AquaHideout::
	call Debug_StoryBeat_EnsureParty
	clearflag FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE
	clearflag FLAG_HIDE_AQUA_HIDEOUT_GRUNTS
	clearflag FLAG_HIDE_AQUA_HIDEOUT_B2F_SUBMARINE_SHADOW
	cleartrainerflag TRAINER_MATT
	warp MAP_AQUA_HIDEOUT_B2F, 8
	waitstate
	end

@ Mostaccideep: walk right toward the Al Dente group outside the Space Center.
Debug_StoryBeat_SpaceCenter::
	call Debug_StoryBeat_EnsureParty
	setvar VAR_MOSSDEEP_CITY_STATE, 1
	setvar VAR_MOSSDEEP_SPACE_CENTER_STATE, 1
	setvar VAR_MOSSDEEP_SPACE_CENTER_STAIR_GUARD_STATE, 0
	clearflag FLAG_HIDE_MOSSDEEP_CITY_TEAM_MAGMA
	clearflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_1F_TEAM_MAGMA
	clearflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_2F_TEAM_MAGMA
	clearflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_2F_STEVEN
	setflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_1F_STEVEN
	clearflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_MAGMA_NOTE
	clearflag FLAG_DEFEATED_GRUNT_SPACE_CENTER_1F
	clearflag FLAG_INTERACTED_WITH_STEVEN_SPACE_CENTER
	clearflag FLAG_DEFEATED_MAGMA_SPACE_CENTER
	cleartrainerflag TRAINER_GRUNT_SPACE_CENTER_1
	cleartrainerflag TRAINER_GRUNT_SPACE_CENTER_2
	cleartrainerflag TRAINER_GRUNT_SPACE_CENTER_3
	cleartrainerflag TRAINER_GRUNT_SPACE_CENTER_4
	cleartrainerflag TRAINER_GRUNT_SPACE_CENTER_5
	cleartrainerflag TRAINER_GRUNT_SPACE_CENTER_6
	cleartrainerflag TRAINER_GRUNT_SPACE_CENTER_7
	cleartrainerflag TRAINER_MAXIE_MOSSDEEP
	cleartrainerflag TRAINER_TABITHA_MOSSDEEP
	warp MAP_MOSSDEEP_CITY, 40, 24
	waitstate
	end

@ Seafloor Cavern: walk up toward the sleeping Kyogre.
Debug_StoryBeat_SeafloorCavern::
	call Debug_StoryBeat_EnsureParty
	setvar VAR_SEAFLOOR_CAVERN_STATE, 0
	clearflag FLAG_KYOGRE_ESCAPED_SEAFLOOR_CAVERN
	setflag FLAG_HIDE_SEAFLOOR_CAVERN_ROOM_9_ARCHIE
	setflag FLAG_HIDE_SEAFLOOR_CAVERN_ROOM_9_MAXIE
	setflag FLAG_HIDE_SEAFLOOR_CAVERN_ROOM_9_MAGMA_GRUNTS
	setflag FLAG_HIDE_SEAFLOOR_CAVERN_ROOM_9_KYOGRE
	clearflag FLAG_HIDE_SEAFLOOR_CAVERN_ROOM_9_KYOGRE_ASLEEP
	cleartrainerflag TRAINER_ARCHIE
	warp MAP_SEAFLOOR_CAVERN_ROOM9, 17, 44
	waitstate
	end

@ The world state right after the Seafloor Cavern scene, used by both
@ Sugopolis beats.
Debug_StoryBeat_SetLegendariesAwake:
	setvar VAR_SEAFLOOR_CAVERN_STATE, 1
	setflag FLAG_KYOGRE_ESCAPED_SEAFLOOR_CAVERN
	setflag FLAG_LEGENDARIES_IN_SOOTOPOLIS
	setflag FLAG_SYS_WEATHER_CTRL
	clearflag FLAG_SOOTOPOLIS_ARCHIE_MAXIE_LEAVE
	clearflag FLAG_MET_ARCHIE_SOOTOPOLIS
	clearflag FLAG_MET_MAXIE_SOOTOPOLIS
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_STEVEN
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_ARCHIE
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_MAXIE
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_RESIDENTS
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_GROUDON
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_KYOGRE
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_RAYQUAZA
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_MAN_1
	setflag FLAG_HIDE_MAP_NAME_POPUP
	return

@ Sugopolis: Groudon and Kyogre clash. The scene plays as soon as you arrive.
Debug_StoryBeat_SootopolisClash::
	call Debug_StoryBeat_EnsureParty
	call Debug_StoryBeat_SetLegendariesAwake
	setvar VAR_SOOTOPOLIS_CITY_STATE, 1
	setvar VAR_SKY_PILLAR_STATE, 0
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_WALLACE
	warp MAP_SOOTOPOLIS_CITY, 43, 32
	waitstate
	end

@ Sugopolis: Rayquaza calms the clash, then talk to both leaders.
@ The scene plays as soon as you arrive.
Debug_StoryBeat_SootopolisRayquaza::
	call Debug_StoryBeat_EnsureParty
	call Debug_StoryBeat_SetLegendariesAwake
	setvar VAR_SOOTOPOLIS_CITY_STATE, 5
	setvar VAR_SKY_PILLAR_STATE, 1
	setvar VAR_SOOTOPOLIS_WALLACE_STATE, 0
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_WALLACE
	warp MAP_SOOTOPOLIS_CITY, 43, 32
	waitstate
	end

@ Mt. Penne summit (orbs returned): walk up toward the two leaders.
Debug_StoryBeat_MtPyreReturn::
	call Debug_StoryBeat_EnsureParty
	setvar VAR_MT_PYRE_STATE, 2
	clearflag FLAG_HIDE_MT_PYRE_SUMMIT_ARCHIE
	clearflag FLAG_HIDE_MT_PYRE_SUMMIT_MAXIE
	setflag FLAG_HIDE_MT_PYRE_SUMMIT_TEAM_AQUA
	clearflag FLAG_RETURNED_RED_OR_BLUE_ORB
	warp MAP_MT_PYRE_SUMMIT, 1
	waitstate
	end
