BattleFrontier_Mart_MapScripts::
	.byte 0

BattleFrontier_Mart_EventScript_Clerk::
	lock
	faceplayer
	message BattleFrontier_Mart_Text_JasonGreeting
	waitmessage
	pokemart BattleFrontier_Mart_Pokemart
	msgbox gText_RetroSalvageGames_ThanksForShopping, MSGBOX_DEFAULT
	release
	end

	.align 2
BattleFrontier_Mart_Pokemart:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_POTION
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_PROTEIN
	.2byte ITEM_CALCIUM
	.2byte ITEM_IRON
	.2byte ITEM_ZINC
	.2byte ITEM_CARBOS
	.2byte ITEM_HP_UP
	pokemartlistend

BattleFrontier_Mart_EventScript_OldMan::
	msgbox BattleFrontier_Mart_Text_ChaperonGrandson, MSGBOX_NPC
	end

BattleFrontier_Mart_EventScript_OldWoman::
	lock
	applymovement LOCALID_FRONTIER_MART_OLD_WOMAN, Common_Movement_FaceDown
	waitmovement 0
	msgbox BattleFrontier_Mart_Text_ProteinMakeNiceGift, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Mart_EventScript_Boy::
	msgbox BattleFrontier_Mart_Text_FacilitiesDontAllowItems, MSGBOX_NPC
	end

BattleFrontier_Mart_Text_ChaperonGrandson:
	.string "We came to watch our grandson battle.\p"
	.string "While we're here, we're picking up\n"
	.string "souvenirs. What a lovely shop!$"

BattleFrontier_Mart_Text_ProteinMakeNiceGift:
	.string "Dear, wouldn't this make a nice gift?\p"
	.string "It's… PRO… TE… IN?\p"
	.string "It sounds delicious.\n"
	.string "Everything here does!$"

BattleFrontier_Mart_Text_FacilitiesDontAllowItems:
	.string "Most BUCATINI FRONTIER facilities\n"
	.string "don't allow items in battle.\p"
	.string "I still stock up at\n"
	.string "RETRO SALVAGE GAMES. Old habits!$"

BattleFrontier_Mart_Text_JasonGreeting:
	.string "JASON: Battling all day?\n"
	.string "Even champions need a\l"
	.string "break with a good old game.\p"
	.string "What can I get you?$"
