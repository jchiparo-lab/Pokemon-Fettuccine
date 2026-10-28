DewfordTown_Hall_MapScripts::
	.byte 0

DewfordTown_Hall_EventScript_Girl::
	lock
	faceplayer
	msgbox DewfordTown_Hall_Text_CantImagineLifeWithoutTrend, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_Woman::
	lock
	faceplayer
	msgbox DewfordTown_Hall_Text_TeachingMonAboutTrend, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_Man::
	lock
	faceplayer
	msgbox DewfordTown_Hall_Text_DeepLinkBetweenXAndY, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, DewfordTown_Hall_EventScript_ConfirmTrendLink
	goto_if_eq VAR_RESULT, NO, DewfordTown_Hall_EventScript_RejectTrendLink
	end

DewfordTown_Hall_EventScript_ConfirmTrendLink::
	msgbox DewfordTown_Hall_Text_MyHunchWasRight, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_RejectTrendLink::
	msgbox DewfordTown_Hall_Text_NotEasyToKeepUp, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_ExpertM::
	lock
	faceplayer
	msgbox DewfordTown_Hall_Text_TVShowAboutTrend, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEWFORD_HALL_EXPERT_M, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	release
	end

DewfordTown_Hall_EventScript_Twin::
	lock
	faceplayer
	msgbox DewfordTown_Hall_Text_IsTrendMorePopularAcrossSea, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEWFORD_HALL_TWIN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	release
	end

DewfordTown_Hall_EventScript_LittleBoy::
	lock
	faceplayer
	msgbox DewfordTown_Hall_Text_CollectTrendMerchandise, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_Bookshelf::
	lockall
	msgbox DewfordTown_Hall_Text_BooksAboutTrend, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_Painting::
	msgbox DewfordTown_Hall_Text_RetrotopiaPoster, MSGBOX_SIGN
	end

DewfordTown_Hall_EventScript_SchoolKidM::
	lockall
	setvar VAR_0x8008, 0
	goto DewfordTown_Hall_EventScript_DoTrendDebate
	end

DewfordTown_Hall_EventScript_PsychicM::
	lockall
	setvar VAR_0x8008, 1
	goto DewfordTown_Hall_EventScript_DoTrendDebate
	end

DewfordTown_Hall_EventScript_DoTrendDebate::
	random 5
	switch VAR_RESULT
	case 0, DewfordTown_Hall_EventScript_TrendDebate1
	case 1, DewfordTown_Hall_EventScript_TrendDebate2
	case 2, DewfordTown_Hall_EventScript_TrendDebate3
	case 3, DewfordTown_Hall_EventScript_TrendDebate4
	case 4, DewfordTown_Hall_EventScript_TrendDebate5
	end

DewfordTown_Hall_EventScript_TrendDebate1::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_SawTrendCoolestThing, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_AllegedTrendNotAuthentic, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate2::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_ComposedTrendThemeSong, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_WorkOnYourSinging, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate3::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_OrganizeTrendParty, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_BrilliantIndeed, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate4::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_TrendHasBecomePartOfLife, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_TrendWeighsHeavilyOnMind, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate5::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_IfWeTeamUpWellBeInvincible, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_WellBeTrendDuo, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_DontMovePlayer1::
	return

DewfordTown_Hall_EventScript_DebateReact1::
	applymovement LOCALID_DEWFORD_HALL_PSYCHIC_M, DewfordTown_Hall_Movement_PsychicWalkInPlaceLeft
	waitmovement 0
	goto_if_eq VAR_0x8008, 0, DewfordTown_Hall_EventScript_PlayerReactWest
	goto_if_eq VAR_0x8008, 1, DewfordTown_Hall_EventScript_DontMovePlayer2
	end

DewfordTown_Hall_EventScript_PlayerReactWest::
	goto_if_eq VAR_FACING, DIR_EAST, DewfordTown_Hall_EventScript_DontMovePlayer1
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

DewfordTown_Hall_EventScript_DontMovePlayer2::
	return

DewfordTown_Hall_EventScript_DebateReact2::
	applymovement LOCALID_DEWFORD_HALL_SCHOOL_KID_M, DewfordTown_Hall_Movement_SchoolKidWalkInPlaceRight
	waitmovement 0
	goto_if_eq VAR_0x8008, 0, DewfordTown_Hall_EventScript_PlayerReactNorthSouth
	goto_if_eq VAR_0x8008, 1, DewfordTown_Hall_EventScript_PlayerReactEast
	end

DewfordTown_Hall_EventScript_PlayerReactNorthSouth::
	call_if_eq VAR_FACING, DIR_NORTH, DewfordTown_Hall_EventScript_PlayerWalkInPlaceUp
	call_if_eq VAR_FACING, DIR_SOUTH, DewfordTown_Hall_EventScript_PlayerWalkInPlaceDown
	return

DewfordTown_Hall_EventScript_PlayerWalkInPlaceUp::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

DewfordTown_Hall_EventScript_PlayerWalkInPlaceDown::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

DewfordTown_Hall_EventScript_PlayerReactEast::
	goto_if_eq VAR_FACING, DIR_WEST, DewfordTown_Hall_EventScript_DontMovePlayer1
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

DewfordTown_Hall_Movement_PsychicWalkInPlaceLeft:
	walk_in_place_left
	step_end

DewfordTown_Hall_Movement_SchoolKidWalkInPlaceRight:
	walk_in_place_right
	step_end

DewfordTown_Hall_EventScript_SludgeBombMan::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_SLUDGE_BOMB, DewfordTown_Hall_EventScript_ReceivedSludgeBomb
	msgbox DewfordTown_Hall_Text_GiveYouSludgeBomb, MSGBOX_DEFAULT
	giveitem ITEM_TM_SLUDGE_BOMB
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_SLUDGE_BOMB
	release
	end

DewfordTown_Hall_EventScript_ReceivedSludgeBomb::
	msgbox DewfordTown_Hall_Text_LoveSludgeBombButTrendInToo, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_Text_CantImagineLifeWithoutTrend:
	.string "I found RETROTOPIA last week, and\n"
	.string "I've already heard every episode!\p"
	.string "I can't imagine life without it now!$"

DewfordTown_Hall_Text_TeachingMonAboutTrend:
	.string "I play RETROTOPIA for my POKéMON\n"
	.string "while we train.\p"
	.string "They don't understand a word,\n"
	.string "but they love it anyway!$"

DewfordTown_Hall_Text_DeepLinkBetweenXAndY:
	.string "All the young folks are talking about\n"
	.string "this RETROTOPIA show.\p"
	.string "Is it true that it's all about\n"
	.string "classic video games?$"

DewfordTown_Hall_Text_MyHunchWasRight:
	.string "Oh!\n"
	.string "So, my hunch was right!\p"
	.string "The games from my day are back in\n"
	.string "style! Yowza!$"

DewfordTown_Hall_Text_NotEasyToKeepUp:
	.string "What?!\n"
	.string "Is that so?!\p"
	.string "Then what have I been listening to\n"
	.string "all this time?!$"

DewfordTown_Hall_Text_TVShowAboutTrend:
	.string "I hung that RETROTOPIA poster\n"
	.string "up myself.\p"
	.string "Pretty sharp, isn't it?$"

DewfordTown_Hall_Text_IsTrendMorePopularAcrossSea:
	.string "Across the sea…\p"
	.string "Do they listen to RETROTOPIA\n"
	.string "over there, too?$"

DewfordTown_Hall_Text_CollectTrendMerchandise:
	.string "I'm RETROTOPIA's number one fan!\p"
	.string "I've told every kid at school\n"
	.string "to listen.\p"
	.string "Some of them even did!\p"
	.string "Heheh, I'm basically part of\n"
	.string "the show now!$"

DewfordTown_Hall_Text_BooksAboutTrend:
	.string "THE RETROTOPIA EPISODE GUIDE…\p"
	.string "CLASSIC GAMES YOU MISSED…\p"
	.string "HOW TO START A PODCAST…\p"
	.string "It's packed with books and old\n"
	.string "game magazines.$"

DewfordTown_Hall_Text_RetrotopiaPoster:
	.string "It's a RETROTOPIA poster.\n"
	.string "“New episodes! Tune in!”$"

DewfordTown_Hall_Text_SawTrendCoolestThing:
	.string "I heard the newest RETROTOPIA\n"
	.string "episode!\p"
	.string "It was the best one yet!\n"
	.string "It was awesome, oh yeah!$"

DewfordTown_Hall_Text_AllegedTrendNotAuthentic:
	.string "Oh, no, no, no.\p"
	.string "The best episode was an older one,\n"
	.string "my friend.\p"
	.string "Ah, no matter.\n"
	.string "They're all smashing listens!$"

DewfordTown_Hall_Text_ComposedTrendThemeSong:
	.string "Hey, listen, I wrote a theme song\n"
	.string "for RETROTOPIA!\p"
	.string "Okay, listen!\n"
	.string "… …\p"
	.string "Oh!\n"
	.string "RETROTOPIA!\p"
	.string "Wonderful\n"
	.string "RETROTOPIA!$"

DewfordTown_Hall_Text_WorkOnYourSinging:
	.string "… …\p"
	.string "I dare say, chap, it would pay for\n"
	.string "you to work on your singing first.$"

DewfordTown_Hall_Text_OrganizeTrendParty:
	.string "Anyway, as I was saying, we should\n"
	.string "throw a RETROTOPIA listening party\l"
	.string "on the island.$"

DewfordTown_Hall_Text_BrilliantIndeed:
	.string "Oh, a smashing good idea!\p"
	.string "Starting today, our lives will\n"
	.string "revolve around RETROTOPIA!$"

DewfordTown_Hall_Text_TrendHasBecomePartOfLife:
	.string "I was thinking, though…\p"
	.string "RETROTOPIA isn't just a show.\n"
	.string "It's part of my daily life!$"

DewfordTown_Hall_Text_TrendWeighsHeavilyOnMind:
	.string "Absolutely, old sport!\p"
	.string "You're a true RETROTOPIA\n"
	.string "PROFESSOR!$"

DewfordTown_Hall_Text_IfWeTeamUpWellBeInvincible:
	.string "If you and me team up, we'll be the\n"
	.string "biggest RETROTOPIA fans ever!$"

DewfordTown_Hall_Text_WellBeTrendDuo:
	.string "Spot on, my friend!\p"
	.string "We shall be the\n"
	.string "RETROTOPIA DUO!\p"
	.string "Isn't that a ripe image?\n"
	.string "Hahahah!$"

DewfordTown_Hall_Text_GiveYouSludgeBomb:
	.string "For me, RETROTOPIA is at the peak\n"
	.string "of popularity. It's the one.\p"
	.string "Hunh? You've never listened?\n"
	.string "That's outright pitiful.\p"
	.string "Here, take this while you catch up.$"

DewfordTown_Hall_Text_LoveSludgeBombButTrendInToo:
	.string "I love RETROTOPIA.\p"
	.string "New episodes are the best part\n"
	.string "of my week!$"
