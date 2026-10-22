MeteorFalls_B1F_2R_MapScripts::
	.byte 0

@ Fettuccine: Diancie one-time encounter. If it isn't caught, it stays so the player can try again.
MeteorFalls_B1F_2R_EventScript_Diancie::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DIANCIE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_DIANCIE, 50
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, MeteorFalls_B1F_2R_EventScript_CaughtDiancie
	release
	end

MeteorFalls_B1F_2R_EventScript_CaughtDiancie::
	setflag FLAG_HIDE_METEOR_FALLS_DIANCIE
	goto Common_EventScript_RemoveStaticPokemon
	end
