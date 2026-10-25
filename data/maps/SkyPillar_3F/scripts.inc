SkyPillar_3F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SkyPillar_3F_OnTransition
	.byte 0

SkyPillar_3F_OnTransition:
	call SkyPillar_3F_EventScript_SetupLegendDialga
	call_if_lt VAR_SKY_PILLAR_STATE, 2, SkyPillar_3F_EventScript_CleanFloor
	end

SkyPillar_3F_EventScript_CleanFloor::
	setmaplayoutindex LAYOUT_SKY_PILLAR_3F_CLEAN
	return

@ Fettuccine: post-game Dialga. Appears after the Hall of Fame and once Rayquaza are caught, until it's caught.
SkyPillar_3F_EventScript_SetupLegendDialga::
	setflag FLAG_HIDE_LEGEND_DIALGA
	goto_if_unset FLAG_SYS_GAME_CLEAR, SkyPillar_3F_EventScript_SetupLegendDialgaDone
	getcaughtmon SPECIES_DIALGA
	goto_if_eq VAR_RESULT, TRUE, SkyPillar_3F_EventScript_SetupLegendDialgaDone
	getcaughtmon SPECIES_RAYQUAZA
	goto_if_eq VAR_RESULT, FALSE, SkyPillar_3F_EventScript_SetupLegendDialgaDone
	clearflag FLAG_HIDE_LEGEND_DIALGA
SkyPillar_3F_EventScript_SetupLegendDialgaDone::
	return

SkyPillar_3F_EventScript_LegendDialga::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DIALGA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_DIALGA, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, SkyPillar_3F_EventScript_CaughtLegendDialga
	release
	end

SkyPillar_3F_EventScript_CaughtLegendDialga::
	setflag FLAG_HIDE_LEGEND_DIALGA
	goto Common_EventScript_RemoveStaticPokemon
	end
