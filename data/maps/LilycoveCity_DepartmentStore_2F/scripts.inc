LilycoveCity_DepartmentStore_2F_MapScripts::
	.byte 0

LilycoveCity_DepartmentStore_2F_EventScript_Cook::
	msgbox LilycoveCity_DepartmentStore_2F_Text_LearnToUseItemsProperly, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_2F_EventScript_PokefanF::
	msgbox LilycoveCity_DepartmentStore_2F_Text_GoodGiftForHusband, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_2F_EventScript_Sailor::
	msgbox LilycoveCity_DepartmentStore_2F_Text_StockUpOnItems, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_2F_EventScript_ClerkLeft::
	lock
	faceplayer
	message LilycoveCity_DepartmentStore_2F_Text_JasonGreeting
	waitmessage
	pokemart LilycoveCity_DepartmentStore_2F_Pokemart1
	msgbox gText_RetroSalvageGames_ThanksForShopping, MSGBOX_DEFAULT
	release
	end

	.align 2
LilycoveCity_DepartmentStore_2F_Pokemart1:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_FLUFFY_TAIL
	.2byte ITEM_TM_X_SCISSOR
	.2byte ITEM_TM_BUG_BUZZ
	.2byte ITEM_TM_DARK_PULSE
	.2byte ITEM_TM_NASTY_PLOT
	.2byte ITEM_TM_DRAGON_PULSE
	.2byte ITEM_TM_PLAY_ROUGH
	.2byte ITEM_TM_DAZZLING_GLEAM
	.2byte ITEM_TM_ENERGY_BALL
	.2byte ITEM_LOVE_BALL
	.2byte ITEM_TM_EARTH_POWER
	.2byte ITEM_TM_PSYSHOCK
	.2byte ITEM_TM_TRICK_ROOM
	.2byte ITEM_TM_STEALTH_ROCK
	.2byte ITEM_TM_IRON_HEAD
	.2byte ITEM_TM_FLASH_CANNON
	.2byte ITEM_TM_SCALD
	.2byte ITEM_TM_LIQUIDATION
	.2byte ITEM_CATCHING_CHARM
	.2byte ITEM_RETRO_MAIL
	pokemartlistend

LilycoveCity_DepartmentStore_2F_EventScript_ClerkRight::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart LilycoveCity_DepartmentStore_2F_Pokemart2
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LilycoveCity_DepartmentStore_2F_Pokemart2:
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_POTION
	.2byte ITEM_REVIVE
	.2byte ITEM_REPEL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_WAVE_MAIL
	.2byte ITEM_MECH_MAIL
	.2byte ITEM_SWEET_HEART
	.2byte ITEM_MAX_HONEY
	.2byte ITEM_REMEDY
	.2byte ITEM_FINE_REMEDY
	.2byte ITEM_SUPERB_REMEDY
	.2byte ITEM_PEWTER_CRUNCHIES
	.2byte ITEM_RAGE_CANDY_BAR
	.2byte ITEM_OLD_GATEAU
	.2byte ITEM_CASTELIACONE
	.2byte ITEM_LUMIOSE_GALETTE
	.2byte ITEM_SHALOUR_SABLE
	.2byte ITEM_BIG_MALASADA
	.2byte ITEM_JUBILIFE_MUFFIN
	.2byte ITEM_DREAM_MAIL
	.2byte ITEM_FAB_MAIL
	pokemartlistend

LilycoveCity_DepartmentStore_2F_Text_LearnToUseItemsProperly:
	.string "Learn to use items properly.\n"
	.string "That's basic, really.$"

LilycoveCity_DepartmentStore_2F_Text_GoodGiftForHusband:
	.string "My husband is waiting at home.\n"
	.string "What would make a good gift for him?$"

LilycoveCity_DepartmentStore_2F_Text_StockUpOnItems:
	.string "I'm leaving on a long journey soon.\n"
	.string "I need to stock up on items.$"

LilycoveCity_DepartmentStore_2F_Text_JasonGreeting:
	.string "JASON: Surprised?\p"
	.string "RETRO SALVAGE GAMES has a counter\n"
	.string "in the DEPARTMENT STORE too!\p"
	.string "What can I get you?$"
