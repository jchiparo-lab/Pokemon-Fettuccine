AlteringCave_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AlteringCave_OnTransition
	.byte 0

AlteringCave_OnTransition:
	call AlteringCave_EventScript_SetupLegendLunala
	setflag FLAG_LANDMARK_ALTERING_CAVE
	end

@ Fettuccine: post-game Lunala. Appears after the Hall of Fame, until it's caught.
AlteringCave_EventScript_SetupLegendLunala::
	setflag FLAG_HIDE_LEGEND_LUNALA
	goto_if_unset FLAG_SYS_GAME_CLEAR, AlteringCave_EventScript_SetupLegendLunalaDone
	getcaughtmon SPECIES_LUNALA
	goto_if_eq VAR_RESULT, TRUE, AlteringCave_EventScript_SetupLegendLunalaDone
	clearflag FLAG_HIDE_LEGEND_LUNALA
AlteringCave_EventScript_SetupLegendLunalaDone::
	return

AlteringCave_EventScript_LegendLunala::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_LUNALA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_LUNALA, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, AlteringCave_EventScript_CaughtLegendLunala
	release
	end

AlteringCave_EventScript_CaughtLegendLunala::
	setflag FLAG_HIDE_LEGEND_LUNALA
	goto Common_EventScript_RemoveStaticPokemon
	end
