DesertUnderpass_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DesertUnderpass_OnTransition
	.byte 0

DesertUnderpass_OnTransition:
	call DesertUnderpass_EventScript_SetupLegendZygarde
	setflag FLAG_LANDMARK_DESERT_UNDERPASS
	end

DesertUnderpass_EventScript_Fossil::
	lock
	faceplayer
	goto_if_set FLAG_CHOSE_ROOT_FOSSIL, DesertUnderpass_EventScript_GiveClawFossil
	goto_if_set FLAG_CHOSE_CLAW_FOSSIL, DesertUnderpass_EventScript_GiveRootFossil
	release
	end

DesertUnderpass_EventScript_GiveClawFossil::
	giveitem ITEM_CLAW_FOSSIL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	removeobject LOCALID_UNDERPASS_FOSSIL
	release
	end

DesertUnderpass_EventScript_GiveRootFossil::
	giveitem ITEM_ROOT_FOSSIL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	removeobject LOCALID_UNDERPASS_FOSSIL
	release
	end

@ Unused
DesertUnderpass_Text_FoundRootFossil::
	.string "{PLAYER} found the ROOT FOSSIL.$"

@ Unused
DesertUnderpass_Text_FoundClawFossil::
	.string "{PLAYER} found the CLAW FOSSIL.$"

@ Fettuccine: post-game Zygarde. Appears after the Hall of Fame, until it's caught.
DesertUnderpass_EventScript_SetupLegendZygarde::
	setflag FLAG_HIDE_LEGEND_ZYGARDE
	goto_if_unset FLAG_SYS_GAME_CLEAR, DesertUnderpass_EventScript_SetupLegendZygardeDone
	getcaughtmon SPECIES_ZYGARDE
	goto_if_eq VAR_RESULT, TRUE, DesertUnderpass_EventScript_SetupLegendZygardeDone
	clearflag FLAG_HIDE_LEGEND_ZYGARDE
DesertUnderpass_EventScript_SetupLegendZygardeDone::
	return

DesertUnderpass_EventScript_LegendZygarde::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZYGARDE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_ZYGARDE, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, DesertUnderpass_EventScript_CaughtLegendZygarde
	release
	end

DesertUnderpass_EventScript_CaughtLegendZygarde::
	setflag FLAG_HIDE_LEGEND_ZYGARDE
	goto Common_EventScript_RemoveStaticPokemon
	end
