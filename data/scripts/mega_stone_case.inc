@ Fettuccine: using the Mega Stone Case (from the bag or SELECT).
@ Pick a stone from the full list, then pick a Pokémon to hold it.
@ The case never runs out (see src/mega_stone_case.c).
EventScript_UseMegaStoneCase::
	lockall
	message MegaStoneCase_Text_WhichStone
	waitmessage
	special MegaStoneCase_PushChoices
	dynmultistack 0, 0, FALSE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, EventScript_CloseMegaStoneCase
	special MegaStoneCase_SetChosenStone
	goto_if_eq VAR_ITEM_ID, ITEM_NONE, EventScript_CloseMegaStoneCase
	closemessage
	fadescreen FADE_TO_BLACK
	special ChooseMonToGiveMegaStone
	waitstate
	releaseall
	end

EventScript_CloseMegaStoneCase::
	closemessage
	releaseall
	end

MegaStoneCase_Text_WhichStone:
	.string "Which MEGA STONE?$"
