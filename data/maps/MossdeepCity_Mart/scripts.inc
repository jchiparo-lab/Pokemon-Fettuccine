MossdeepCity_Mart_MapScripts::
	.byte 0

MossdeepCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message MossdeepCity_Mart_Text_JasonGreeting
	waitmessage
	pokemart MossdeepCity_Mart_Pokemart
	msgbox gText_RetroSalvageGames_ThanksForShopping, MSGBOX_DEFAULT
	release
	end

	.align 2
MossdeepCity_Mart_Pokemart:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_DIVE_BALL
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_TM_VOLT_SWITCH
	.2byte ITEM_TM_FOCUS_BLAST
	.2byte ITEM_TM_STONE_EDGE
	.2byte ITEM_SCOPE_LENS
	.2byte ITEM_ZOOM_LENS
	.2byte ITEM_ODD_INCENSE
	.2byte ITEM_ICY_ROCK
	pokemartlistend

MossdeepCity_Mart_EventScript_Woman::
	msgbox MossdeepCity_Mart_Text_ReviveIsFantastic, MSGBOX_NPC
	end

MossdeepCity_Mart_EventScript_Boy::
	msgbox MossdeepCity_Mart_Text_MaxRepelLastsLongest, MSGBOX_NPC
	end

MossdeepCity_Mart_EventScript_Sailor::
	msgbox MossdeepCity_Mart_Text_NetAndDiveBallsRare, MSGBOX_NPC
	end

MossdeepCity_Mart_Text_ReviveIsFantastic:
	.string "REVIVE is fantastic!\p"
	.string "It wakes up a fainted POKéMON,\n"
	.string "but it doesn't restore PP.\p"
	.string "RETRO SALVAGE GAMES\n"
	.string "saves the day again!$"

MossdeepCity_Mart_Text_MaxRepelLastsLongest:
	.string "MAX REPEL keeps weak POKéMON\n"
	.string "away the longest of any REPEL.\p"
	.string "JASON recommended\n"
	.string "it. He's never wrong!$"

MossdeepCity_Mart_Text_NetAndDiveBallsRare:
	.string "NET and DIVE BALLS are\n"
	.string "only made in MOSTACCIDEEP.\p"
	.string "NET BALLS work on BUG and WATER\n"
	.string "types, DIVE BALLS under the sea.\p"
	.string "Only at RETRO SALVAGE GAMES!$"

MossdeepCity_Mart_Text_JasonGreeting:
	.string "JASON: They launch rockets\n"
	.string "at the SPACE CENTER.\p"
	.string "Me? I launch DEALS!\p"
	.string "What'll it be?$"
