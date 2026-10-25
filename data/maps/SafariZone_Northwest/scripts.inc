SafariZone_Northwest_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SafariZone_Northwest_OnTransition
	.byte 0

SafariZone_Northwest_OnTransition:
	call SafariZone_Northwest_EventScript_SetupLegendXerneas
	end

SafariZone_Northwest_EventScript_Man::
	msgbox SafariZone_Northwest_Text_Man, MSGBOX_NPC
	end

@ Fettuccine: post-game Xerneas. Appears after the Hall of Fame, until it's caught.
SafariZone_Northwest_EventScript_SetupLegendXerneas::
	setflag FLAG_HIDE_LEGEND_XERNEAS
	goto_if_unset FLAG_SYS_GAME_CLEAR, SafariZone_Northwest_EventScript_SetupLegendXerneasDone
	getcaughtmon SPECIES_XERNEAS
	goto_if_eq VAR_RESULT, TRUE, SafariZone_Northwest_EventScript_SetupLegendXerneasDone
	clearflag FLAG_HIDE_LEGEND_XERNEAS
SafariZone_Northwest_EventScript_SetupLegendXerneasDone::
	return

SafariZone_Northwest_EventScript_LegendXerneas::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_XERNEAS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_XERNEAS, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, SafariZone_Northwest_EventScript_CaughtLegendXerneas
	release
	end

SafariZone_Northwest_EventScript_CaughtLegendXerneas::
	setflag FLAG_HIDE_LEGEND_XERNEAS
	goto Common_EventScript_RemoveStaticPokemon
	end
