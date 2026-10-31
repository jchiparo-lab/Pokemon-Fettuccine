MauvilleCity_Mart_MapScripts::
	.byte 0

MauvilleCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message MauvilleCity_Mart_Text_JasonGreeting
	waitmessage
	pokemart MauvilleCity_Mart_Pokemart
	msgbox gText_RetroSalvageGames_ThanksForShopping, MSGBOX_DEFAULT
	release
	end

	.align 2
MauvilleCity_Mart_Pokemart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_GUARD_SPEC
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_X_ACCURACY
	.2byte ITEM_TM_THUNDER_PUNCH
	.2byte ITEM_TM_FIRE_PUNCH
	.2byte ITEM_TM_ICE_PUNCH
	.2byte ITEM_TM_WILD_CHARGE
	pokemartlistend

MauvilleCity_Mart_EventScript_ExpertM::
	msgbox MauvilleCity_Mart_Text_ItemsToTemporarilyElevateStats, MSGBOX_NPC
	end

MauvilleCity_Mart_EventScript_Man::
	msgbox MauvilleCity_Mart_Text_DecisionsDetermineBattle, MSGBOX_NPC
	end

MauvilleCity_Mart_Text_ItemsToTemporarilyElevateStats:
	.string "Some items raise a POKéMON's stats\n"
	.string "in battle, like X ATTACK and X DEFEND.\p"
	.string "RETRO SALVAGE GAMES stocks them all!$"

MauvilleCity_Mart_Text_DecisionsDetermineBattle:
	.string "Use a move, or use an item…\p"
	.string "A TRAINER's choices decide the battle.\p"
	.string "My best choice? Shopping here!$"

MauvilleCity_Mart_Text_JasonGreeting:
	.string "JASON: Welcome!\p"
	.string "MACAROVILLE runs on\n"
	.string "electricity, and so does every\l"
	.string "console in here. Mind the cables!\p"
	.string "What do you need?$"
