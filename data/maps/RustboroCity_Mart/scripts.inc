RustboroCity_Mart_MapScripts::
	.byte 0

RustboroCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message RustboroCity_Mart_Text_JasonGreeting
	waitmessage
	goto_if_unset FLAG_MET_DEVON_EMPLOYEE, RustboroCity_Mart_EventScript_PokemartBasic
	goto_if_set FLAG_MET_DEVON_EMPLOYEE, RustboroCity_Mart_EventScript_PokemartExpanded
	end

RustboroCity_Mart_EventScript_PokemartBasic::
	pokemart RustboroCity_Mart_Pokemart_Basic
	msgbox gText_RetroSalvageGames_ThanksForShopping, MSGBOX_DEFAULT
	release
	end

	.align 2
RustboroCity_Mart_Pokemart_Basic:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_TM_BULLDOZE
	.2byte ITEM_TM_THUNDER_WAVE
	.2byte ITEM_ROCK_INCENSE
	.2byte ITEM_LURE
	pokemartlistend

RustboroCity_Mart_EventScript_PokemartExpanded::
	pokemart RustboroCity_Mart_Pokemart_Expanded
	msgbox gText_RetroSalvageGames_ThanksForShopping, MSGBOX_DEFAULT
	release
	end

	.align 2
RustboroCity_Mart_Pokemart_Expanded:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_TM_BULLDOZE
	.2byte ITEM_TM_THUNDER_WAVE
	.2byte ITEM_ROCK_INCENSE
	.2byte ITEM_LURE
	pokemartlistend

RustboroCity_Mart_EventScript_PokefanF::
	msgbox RustboroCity_Mart_Text_BuyingHealsInCaseOfShroomish, MSGBOX_NPC
	end

RustboroCity_Mart_EventScript_Boy::
	msgbox RustboroCity_Mart_Text_ShouldBuySuperPotionsInstead, MSGBOX_NPC
	end

RustboroCity_Mart_EventScript_BugCatcher::
	msgbox RustboroCity_Mart_Text_GettingEscapeRopeJustInCase, MSGBOX_NPC
	end

RustboroCity_Mart_Text_BuyingHealsInCaseOfShroomish:
	.string "I'm stocking up on PARLYZ HEALS\n"
	.string "and ANTIDOTES in case SHROOMISH\l"
	.string "get me in PESTOBURG WOODS.\p"
	.string "This place has everything!$"

RustboroCity_Mart_Text_ShouldBuySuperPotionsInstead:
	.string "My POKéMON evolved, so it has way\n"
	.string "more HP. Time for SUPER POTIONS!\p"
	.string "JASON always knows what I need.$"

RustboroCity_Mart_Text_GettingEscapeRopeJustInCase:
	.string "I'm getting an ESCAPE ROPE\n"
	.string "in case I get lost in a cave.\p"
	.string "RETRO SALVAGE GAMES is\n"
	.string "the only shop I trust!$"

RustboroCity_Mart_Text_JasonGreeting:
	.string "JASON: GARLIC CORP. makes\n"
	.string "all the fancy new gadgets.\p"
	.string "But nothing beats blowing\n"
	.string "on an old cartridge!\p"
	.string "What can I get you?$"
