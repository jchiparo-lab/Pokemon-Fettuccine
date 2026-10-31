PetalburgCity_Mart_MapScripts::
	.byte 0

PetalburgCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message PetalburgCity_Mart_Text_JasonGreeting
	waitmessage
	goto_if_set FLAG_PETALBURG_MART_EXPANDED_ITEMS, PetalburgCity_Mart_EventScript_ExpandedItems
	pokemart PetalburgCity_Mart_Pokemart_Basic
	msgbox gText_RetroSalvageGames_ThanksForShopping, MSGBOX_DEFAULT
	release
	end

	.align 2
PetalburgCity_Mart_Pokemart_Basic:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_LEVEL_BALL
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_ORANGE_MAIL
	.2byte ITEM_TM_CRUNCH
	.2byte ITEM_TM_DRAIN_PUNCH
	.2byte ITEM_TM_KNOCK_OFF
	.2byte ITEM_TM_SUBSTITUTE
	.2byte ITEM_LUCKY_EGG
	.2byte ITEM_POWER_WEIGHT
	.2byte ITEM_POWER_BRACER
	.2byte ITEM_POWER_BELT
	.2byte ITEM_POWER_LENS
	.2byte ITEM_POWER_BAND
	.2byte ITEM_POWER_ANKLET
	.2byte ITEM_PUNCHING_GLOVE
	.2byte ITEM_EXP_CHARM
	pokemartlistend

PetalburgCity_Mart_EventScript_ExpandedItems::
	pokemart PetalburgCity_Mart_Pokemart_Expanded
	msgbox gText_RetroSalvageGames_ThanksForShopping, MSGBOX_DEFAULT
	release
	end

	.align 2
PetalburgCity_Mart_Pokemart_Expanded:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LEVEL_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_ORANGE_MAIL
	.2byte ITEM_TM_CRUNCH
	.2byte ITEM_TM_DRAIN_PUNCH
	.2byte ITEM_TM_KNOCK_OFF
	.2byte ITEM_TM_SUBSTITUTE
	.2byte ITEM_LUCKY_EGG
	.2byte ITEM_POWER_WEIGHT
	.2byte ITEM_POWER_BRACER
	.2byte ITEM_POWER_BELT
	.2byte ITEM_POWER_LENS
	.2byte ITEM_POWER_BAND
	.2byte ITEM_POWER_ANKLET
	.2byte ITEM_PUNCHING_GLOVE
	.2byte ITEM_EXP_CHARM
	pokemartlistend

PetalburgCity_Mart_EventScript_Woman::
	msgbox PetalburgCity_Mart_Text_WeakWillGrowStronger, MSGBOX_NPC
	end

PetalburgCity_Mart_EventScript_Boy::
	msgbox PetalburgCity_Mart_Text_RepelIsUseful, MSGBOX_NPC
	end

PetalburgCity_Mart_EventScript_Man::
	msgbox PetalburgCity_Mart_Text_TakeSomeAntidotesWithYou, MSGBOX_NPC
	end

PetalburgCity_Mart_Text_WeakWillGrowStronger:
	.string "Even a weak POKéMON\n"
	.string "grows strong with love.\p"
	.string "Like a beat-up cartridge here:\n"
	.string "JASON brings them back to life!$"

PetalburgCity_Mart_Text_RepelIsUseful:
	.string "Do you use REPEL? It keeps weak\n"
	.string "POKéMON away when you're in a hurry.\p"
	.string "JASON's prices can't be beat!$"

PetalburgCity_Mart_Text_TakeSomeAntidotesWithYou:
	.string "Got ANTIDOTES? A poisoned\n"
	.string "POKéMON loses HP as you walk.\p"
	.string "I never leave RETRO SALVAGE GAMES\n"
	.string "without a few!$"

PetalburgCity_Mart_Text_JasonGreeting:
	.string "JASON: Hey there!\p"
	.string "PESTOBURG has a tough GYM, but this\n"
	.string "shop has the toughest deals in town.\p"
	.string "What'll it be?$"
