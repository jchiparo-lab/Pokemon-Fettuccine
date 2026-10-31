OldaleTown_Mart_MapScripts::
	.byte 0

OldaleTown_Mart_EventScript_Clerk::
	lock
	faceplayer
	message OldaleTown_Mart_Text_JasonGreeting
	waitmessage
	goto_if_set FLAG_ADVENTURE_STARTED, OldaleTown_Mart_ExpandedItems
	pokemart OldaleTown_Mart_Pokemart_Basic
	msgbox gText_RetroSalvageGames_ThanksForShopping, MSGBOX_DEFAULT
	release
	end

	.align 2
OldaleTown_Mart_Pokemart_Basic:
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	pokemartlistend

OldaleTown_Mart_ExpandedItems::
	pokemart OldaleTown_Mart_Pokemart_Expanded
	msgbox gText_RetroSalvageGames_ThanksForShopping, MSGBOX_DEFAULT
	release
	end

	.align 2
OldaleTown_Mart_Pokemart_Expanded:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	pokemartlistend

OldaleTown_Mart_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_ADVENTURE_STARTED, OldaleTown_Mart_EventScript_PokeBallsInStock
	msgbox OldaleTown_Mart_Text_PokeBallsAreSoldOut, MSGBOX_DEFAULT
	release
	end

OldaleTown_Mart_EventScript_PokeBallsInStock::
	msgbox OldaleTown_Mart_Text_ImGoingToBuyPokeBalls, MSGBOX_DEFAULT
	release
	end

OldaleTown_Mart_EventScript_Boy::
	msgbox OldaleTown_Mart_Text_RestoreHPWithPotion, MSGBOX_NPC
	end

OldaleTown_Mart_Text_PokeBallsAreSoldOut:
	.string "JASON says the\n"
	.string "POKé BALLS are sold out.\p"
	.string "Everyone in town shops\n"
	.string "at RETRO SALVAGE GAMES!$"

OldaleTown_Mart_Text_ImGoingToBuyPokeBalls:
	.string "I'm buying a bunch of POKé BALLS!\p"
	.string "JASON always has the good stuff.$"

OldaleTown_Mart_Text_RestoreHPWithPotion:
	.string "If a POKéMON runs out of HP,\n"
	.string "it faints and can't battle.\p"
	.string "Heal it with a POTION!\n"
	.string "RETRO SALVAGE GAMES has plenty.$"

OldaleTown_Mart_Text_JasonGreeting:
	.string "JASON: Welcome to\n"
	.string "RETRO SALVAGE GAMES!\p"
	.string "I'm JASON. Every game on these shelves\n"
	.string "got rescued from somebody's attic.\p"
	.string "What can I get you?$"
