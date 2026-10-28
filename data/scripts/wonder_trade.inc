@ Wonder Trade: the right-hand counter upstairs in every Pokémon Center
@ (replaces the Direct Corner). The player sends one Pokémon and gets a
@ random non-legendary one back at the same level.

WonderTrade_EventScript_Attendant::
	lock
	faceplayer
	msgbox WonderTrade_Text_Welcome, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, WonderTrade_EventScript_Decline
	msgbox WonderTrade_Text_WhichMon, MSGBOX_DEFAULT
	closemessage
	chooseboxmon SELECT_PC_MON_NORMAL
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, WonderTrade_EventScript_Decline
	specialvar VAR_RESULT, GetTradeSpecies
	goto_if_eq VAR_RESULT, SPECIES_NONE, WonderTrade_EventScript_NoEggs
	msgbox WonderTrade_Text_Searching, MSGBOX_DEFAULT
	closemessage
	special CreateWonderTradePokemon
	special DoInGameTradeScene
	msgbox WonderTrade_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

WonderTrade_EventScript_Decline::
	msgbox WonderTrade_Text_Decline, MSGBOX_DEFAULT
	release
	end

WonderTrade_EventScript_NoEggs::
	msgbox WonderTrade_Text_NoEggs, MSGBOX_DEFAULT
	release
	end

WonderTrade_Text_Welcome:
	.string "Welcome to the WONDER TRADE corner!\p"
	.string "Send one of your POKéMON to a\n"
	.string "mystery TRAINER far away.\p"
	.string "You'll get a random POKéMON back\n"
	.string "at the same level.\p"
	.string "Would you like to WONDER TRADE?$"

WonderTrade_Text_WhichMon:
	.string "Which POKéMON will you send?$"

WonderTrade_Text_Searching:
	.string "Searching for a trading partner…\p"
	.string "… … …\p"
	.string "We found one!\n"
	.string "Let's begin the trade!$"

WonderTrade_Text_ComeAgain:
	.string "Thank you for using WONDER TRADE!\n"
	.string "Please come again!$"

WonderTrade_Text_Decline:
	.string "Please come again!$"

WonderTrade_Text_NoEggs:
	.string "I'm sorry, EGGS can't be sent\n"
	.string "through WONDER TRADE.$"
