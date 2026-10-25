SkyPillar_5F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SkyPillar_5F_OnTransition
	.byte 0

SkyPillar_5F_OnTransition:
	call SkyPillar_5F_EventScript_SetupLegendPalkia
	call_if_lt VAR_SKY_PILLAR_STATE, 2, SkyPillar_5F_EventScript_CleanFloor
	return

SkyPillar_5F_EventScript_CleanFloor::
	setmaplayoutindex LAYOUT_SKY_PILLAR_5F_CLEAN
	return

@ Fettuccine: post-game Palkia. Appears after the Hall of Fame and once Rayquaza are caught, until it's caught.
SkyPillar_5F_EventScript_SetupLegendPalkia::
	setflag FLAG_HIDE_LEGEND_PALKIA
	goto_if_unset FLAG_SYS_GAME_CLEAR, SkyPillar_5F_EventScript_SetupLegendPalkiaDone
	getcaughtmon SPECIES_PALKIA
	goto_if_eq VAR_RESULT, TRUE, SkyPillar_5F_EventScript_SetupLegendPalkiaDone
	getcaughtmon SPECIES_RAYQUAZA
	goto_if_eq VAR_RESULT, FALSE, SkyPillar_5F_EventScript_SetupLegendPalkiaDone
	clearflag FLAG_HIDE_LEGEND_PALKIA
SkyPillar_5F_EventScript_SetupLegendPalkiaDone::
	return

SkyPillar_5F_EventScript_LegendPalkia::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PALKIA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_PALKIA, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, SkyPillar_5F_EventScript_CaughtLegendPalkia
	release
	end

SkyPillar_5F_EventScript_CaughtLegendPalkia::
	setflag FLAG_HIDE_LEGEND_PALKIA
	goto Common_EventScript_RemoveStaticPokemon
	end
