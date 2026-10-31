SootopolisCity_Mart_MapScripts::
	.byte 0

SootopolisCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message SootopolisCity_Mart_Text_JasonGreeting
	waitmessage
	pokemart SootopolisCity_Mart_Pokemart
	msgbox gText_RetroSalvageGames_ThanksForShopping, MSGBOX_DEFAULT
	release
	end

	.align 2
SootopolisCity_Mart_Pokemart:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_POTION
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_SHADOW_MAIL
	.2byte ITEM_TM_HYDRO_PUMP
	.2byte ITEM_TM_OUTRAGE
	.2byte ITEM_TM_DRAGON_DANCE
	pokemartlistend

SootopolisCity_Mart_EventScript_FatMan::
	lock
	faceplayer
	goto_if_ge VAR_SKY_PILLAR_STATE, 2, SootopolisCity_Mart_EventScript_FatManNoLegendaries
	goto_if_unset FLAG_KYOGRE_ESCAPED_SEAFLOOR_CAVERN, SootopolisCity_Mart_EventScript_FatManNoLegendaries
	msgbox SootopolisCity_Mart_Text_TooScaryOutside, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Mart_EventScript_FatManNoLegendaries::
	msgbox SootopolisCity_Mart_Text_PPUpIsGreat, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Mart_EventScript_Gentleman::
	lock
	faceplayer
	goto_if_ge VAR_SKY_PILLAR_STATE, 2, SootopolisCity_Mart_EventScript_GentlemanNoLegendaries
	goto_if_unset FLAG_KYOGRE_ESCAPED_SEAFLOOR_CAVERN, SootopolisCity_Mart_EventScript_GentlemanNoLegendaries
	msgbox SootopolisCity_Mart_Text_DidSomethingAwaken, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Mart_EventScript_GentlemanNoLegendaries::
	msgbox SootopolisCity_Mart_Text_FullRestoreItemOfDreams, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Mart_Text_PPUpIsGreat:
	.string "PP UP is great!\p"
	.string "It raises a move's POWER POINTS.\p"
	.string "Thank goodness for\n"
	.string "RETRO SALVAGE GAMES!$"

SootopolisCity_Mart_Text_TooScaryOutside:
	.string "What… What is happening?\p"
	.string "It's too scary to go outside. I'm\n"
	.string "staying in RETRO SALVAGE GAMES\l"
	.string "until it's over!$"

SootopolisCity_Mart_Text_FullRestoreItemOfDreams:
	.string "FULL RESTORE heals all HP\n"
	.string "and every status problem!\p"
	.string "A dream item, and JASON stocks it!$"

SootopolisCity_Mart_Text_DidSomethingAwaken:
	.string "This weather… Did something awaken?\p"
	.string "At least JASON's still open.$"

SootopolisCity_Mart_Text_JasonGreeting:
	.string "JASON: You know how hard it is to stock\n"
	.string "a shop you have to DIVE to reach?\p"
	.string "Worth it! What can I get you?$"
