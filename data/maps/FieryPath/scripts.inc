FieryPath_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FieryPath_OnTransition
	.byte 0

FieryPath_OnTransition:
	call FieryPath_EventScript_SetupLegendMoltres
	call_if_unset FLAG_LANDMARK_FIERY_PATH, FieryPath_EventScript_MoveScottToFallarbor
	setflag FLAG_LANDMARK_FIERY_PATH
	end

FieryPath_EventScript_MoveScottToFallarbor::
	setflag FLAG_HIDE_VERDANTURF_TOWN_SCOTT
	clearflag FLAG_HIDE_FALLARBOR_TOWN_BATTLE_TENT_SCOTT
	return

@ Fettuccine: post-game Moltres. Appears after the Hall of Fame, until it's caught.
FieryPath_EventScript_SetupLegendMoltres::
	setflag FLAG_HIDE_LEGEND_MOLTRES
	goto_if_unset FLAG_SYS_GAME_CLEAR, FieryPath_EventScript_SetupLegendMoltresDone
	getcaughtmon SPECIES_MOLTRES
	goto_if_eq VAR_RESULT, TRUE, FieryPath_EventScript_SetupLegendMoltresDone
	clearflag FLAG_HIDE_LEGEND_MOLTRES
FieryPath_EventScript_SetupLegendMoltresDone::
	return

FieryPath_EventScript_LegendMoltres::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MOLTRES, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_MOLTRES, 60
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, FieryPath_EventScript_CaughtLegendMoltres
	release
	end

FieryPath_EventScript_CaughtLegendMoltres::
	setflag FLAG_HIDE_LEGEND_MOLTRES
	goto Common_EventScript_RemoveStaticPokemon
	end
