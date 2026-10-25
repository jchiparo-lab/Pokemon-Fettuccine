MtPyre_Exterior_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtPyre_Exterior_OnTransition
	.byte 0

MtPyre_Exterior_OnTransition:
	call MtPyre_Exterior_EventScript_SetupLegendCresselia
	call MtPyre_Exterior_EventScript_CheckEnterFromSummit
	end

MtPyre_Exterior_EventScript_CheckEnterFromSummit::
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	goto_if_lt VAR_TEMP_1, 12, MtPyre_Exterior_EventScript_EnterFromSummit
	return

MtPyre_Exterior_EventScript_EnterFromSummit::
	setweather WEATHER_FOG_HORIZONTAL
	return

MtPyre_Exterior_EventScript_FogTrigger::
	setweather WEATHER_FOG_HORIZONTAL
	doweather
	end

MtPyre_Exterior_EventScript_SunTrigger::
	setweather WEATHER_SUNNY
	doweather
	end

@ Fettuccine: post-game Cresselia. Appears after the Hall of Fame, until it's caught.
MtPyre_Exterior_EventScript_SetupLegendCresselia::
	setflag FLAG_HIDE_LEGEND_CRESSELIA
	goto_if_unset FLAG_SYS_GAME_CLEAR, MtPyre_Exterior_EventScript_SetupLegendCresseliaDone
	getcaughtmon SPECIES_CRESSELIA
	goto_if_eq VAR_RESULT, TRUE, MtPyre_Exterior_EventScript_SetupLegendCresseliaDone
	clearflag FLAG_HIDE_LEGEND_CRESSELIA
MtPyre_Exterior_EventScript_SetupLegendCresseliaDone::
	return

MtPyre_Exterior_EventScript_LegendCresselia::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CRESSELIA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_CRESSELIA, 60
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, MtPyre_Exterior_EventScript_CaughtLegendCresselia
	release
	end

MtPyre_Exterior_EventScript_CaughtLegendCresselia::
	setflag FLAG_HIDE_LEGEND_CRESSELIA
	goto Common_EventScript_RemoveStaticPokemon
	end
