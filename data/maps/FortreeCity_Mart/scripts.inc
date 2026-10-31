FortreeCity_Mart_MapScripts::
	.byte 0

FortreeCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message FortreeCity_Mart_Text_JasonGreeting
	waitmessage
	pokemart FortreeCity_Mart_Pokemart
	msgbox gText_RetroSalvageGames_ThanksForShopping, MSGBOX_DEFAULT
	release
	end

	.align 2
FortreeCity_Mart_Pokemart:
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_REVIVE
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_WOOD_MAIL
	.2byte ITEM_TM_U_TURN
	.2byte ITEM_TM_AIR_SLASH
	.2byte ITEM_TM_BRAVE_BIRD
	.2byte ITEM_TM_ROOST
	pokemartlistend

FortreeCity_Mart_EventScript_Woman::
	msgbox FortreeCity_Mart_Text_SuperRepelBetter, MSGBOX_NPC
	end

FortreeCity_Mart_EventScript_Girl::
	msgbox FortreeCity_Mart_Text_StockUpOnItems, MSGBOX_NPC
	end

FortreeCity_Mart_EventScript_Boy::
	msgbox FortreeCity_Mart_Text_RareCandyMakesMonGrow, MSGBOX_NPC
	end

FortreeCity_Mart_Text_SuperRepelBetter:
	.string "SUPER REPEL lasts much\n"
	.string "longer than a regular REPEL.\p"
	.string "RETRO SALVAGE GAMES never runs out!$"

FortreeCity_Mart_Text_StockUpOnItems:
	.string "I always buy more items than I need.\n"
	.string "You never know what might happen!\p"
	.string "That's why I'm here every day.$"

FortreeCity_Mart_Text_RareCandyMakesMonGrow:
	.string "A RARE CANDY makes a POKéMON\n"
	.string "grow one level right away.\p"
	.string "Almost as sweet as JASON's deals!$"

FortreeCity_Mart_Text_JasonGreeting:
	.string "JASON: Welcome to the treetop shop!\p"
	.string "Careful on those ladders\n"
	.string "with a stack of games.\p"
	.string "What can I get you?$"
