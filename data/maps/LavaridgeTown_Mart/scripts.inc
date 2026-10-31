LavaridgeTown_Mart_MapScripts::
	.byte 0

LavaridgeTown_Mart_EventScript_Clerk::
	lock
	faceplayer
	message LavaridgeTown_Mart_Text_JasonGreeting
	waitmessage
	pokemart LavaridgeTown_Mart_Pokemart
	msgbox gText_RetroSalvageGames_ThanksForShopping, MSGBOX_DEFAULT
	release
	end

	.align 2
LavaridgeTown_Mart_Pokemart:
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_X_SPEED
	pokemartlistend

LavaridgeTown_Mart_EventScript_ExpertM::
	msgbox LavaridgeTown_Mart_Text_XSpeedFirstStrike, MSGBOX_NPC
	end

LavaridgeTown_Mart_EventScript_OldWoman::
	msgbox LavaridgeTown_Mart_Text_LocalSpecialtyOnMtChimney, MSGBOX_NPC
	end

LavaridgeTown_Mart_Text_XSpeedFirstStrike:
	.string "X SPEED raises a POKéMON's SPEED\n"
	.string "in battle so it strikes first.\p"
	.string "RETRO SALVAGE GAMES always has some!$"

LavaridgeTown_Mart_Text_LocalSpecialtyOnMtChimney:
	.string "MT. CALZONE's peak sells a treat\n"
	.string "you can't buy anywhere else.\p"
	.string "Not even here, and this\n"
	.string "place has EVERYTHING!$"

LavaridgeTown_Mart_Text_JasonGreeting:
	.string "JASON: Hot springs\n"
	.string "outside, hot deals inside!\p"
	.string "Just don't take any\n"
	.string "cartridges into the water.\p"
	.string "What can I get you?$"
