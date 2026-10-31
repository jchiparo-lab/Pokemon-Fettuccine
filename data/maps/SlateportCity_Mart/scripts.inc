SlateportCity_Mart_MapScripts::
	.byte 0

SlateportCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message SlateportCity_Mart_Text_JasonGreeting
	waitmessage
	pokemart SlateportCity_Mart_Pokemart
	msgbox gText_RetroSalvageGames_ThanksForShopping, MSGBOX_DEFAULT
	release
	end

	.align 2
SlateportCity_Mart_Pokemart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_HARBOR_MAIL
	.2byte ITEM_TM_ICY_WIND
	.2byte ITEM_TM_ACROBATICS
	.2byte ITEM_TM_DRAINING_KISS
	pokemartlistend

SlateportCity_Mart_EventScript_BlackBelt::
	msgbox SlateportCity_Mart_Text_SomeItemsOnlyAtMart, MSGBOX_NPC
	end

SlateportCity_Mart_EventScript_Man::
	msgbox SlateportCity_Mart_Text_GreatBallIsBetter, MSGBOX_NPC
	end

SlateportCity_Mart_Text_SomeItemsOnlyAtMart:
	.string "The MARKET has some neat stuff.\p"
	.string "But RETRO SALVAGE GAMES has things\n"
	.string "you can't find anywhere else!$"

SlateportCity_Mart_Text_GreatBallIsBetter:
	.string "A GREAT BALL catches\n"
	.string "better than a POKé BALL.\p"
	.string "That elusive POKéMON\n"
	.string "is mine! Thanks, JASON!$"

SlateportCity_Mart_Text_JasonGreeting:
	.string "JASON: Welcome!\p"
	.string "Ships bring new stuff into\n"
	.string "SPAGHETTIPORT every day. I'm\l"
	.string "the guy who wants the OLD stuff!\p"
	.string "What'll it be?$"
