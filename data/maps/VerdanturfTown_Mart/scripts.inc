VerdanturfTown_Mart_MapScripts::
	.byte 0

VerdanturfTown_Mart_EventScript_Clerk::
	lock
	faceplayer
	message VerdanturfTown_Mart_Text_JasonGreeting
	waitmessage
	pokemart VerdanturfTown_Mart_Pokemart
	msgbox gText_RetroSalvageGames_ThanksForShopping, MSGBOX_DEFAULT
	release
	end

	.align 2
VerdanturfTown_Mart_Pokemart:
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_REPEL
	.2byte ITEM_X_SP_ATK
	.2byte ITEM_FLUFFY_TAIL
	.2byte ITEM_TM_SEED_BOMB
	.2byte ITEM_TM_HEX
	.2byte ITEM_TM_SWORDS_DANCE
	pokemartlistend

VerdanturfTown_Mart_EventScript_Boy::
	msgbox VerdanturfTown_Mart_Text_XSpecialIsCrucial, MSGBOX_NPC
	end

VerdanturfTown_Mart_EventScript_ExpertF::
	msgbox VerdanturfTown_Mart_Text_NoStrategyGuidesForBattleTent, MSGBOX_NPC
	end

VerdanturfTown_Mart_EventScript_Lass::
	msgbox VerdanturfTown_Mart_Text_NestBallOnWeakenedPokemon, MSGBOX_NPC
	end

VerdanturfTown_Mart_Text_XSpecialIsCrucial:
	.string "X SP. ATK powers up special\n"
	.string "moves for one battle. Crucial!\p"
	.string "Lucky for me, JASON keeps it in stock.$"

VerdanturfTown_Mart_Text_NoStrategyGuidesForBattleTent:
	.string "JASON has old strategy guides for\n"
	.string "every game… except the BATTLE TENT.\p"
	.string "Guess I'll have to use my own wits!$"

VerdanturfTown_Mart_Text_NestBallOnWeakenedPokemon:
	.string "The NEST BALL works better\n"
	.string "on low-level POKéMON.\p"
	.string "This is the only\n"
	.string "RETRO SALVAGE GAMES that sells it!$"

VerdanturfTown_Mart_Text_JasonGreeting:
	.string "JASON: The air in CAVATAPURF\n"
	.string "is so clean, it keeps the\l"
	.string "dust off my circuit boards!\p"
	.string "What can I get you?$"
