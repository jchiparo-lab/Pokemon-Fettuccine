CaveOfOrigin_B1F_MapScripts::
	.byte 0

CaveOfOrigin_B1F_EventScript_Wallace::
	lock
	faceplayer
	msgbox CaveOfOrigin_B1F_Text_WallaceStory, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CAVE_OF_ORIGIN_WALLACE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 60
	playse SE_PIN
	applymovement LOCALID_CAVE_OF_ORIGIN_WALLACE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_CAVE_OF_ORIGIN_WALLACE, Common_Movement_Delay48
	waitmovement 0
	delay 30
	applymovement LOCALID_CAVE_OF_ORIGIN_WALLACE, Common_Movement_FacePlayer
	waitmovement 0
	message CaveOfOrigin_B1F_Text_WhereIsRayquaza
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_WheresRayquaza::
	multichoice 0, 0, MULTI_WHERES_RAYQUAZA, FALSE
	switch VAR_RESULT
	case 0, CaveOfOrigin_B1F_EventScript_AtCaveOfOrigin
	case 1, CaveOfOrigin_B1F_EventScript_AtMtPyre
	case 2, CaveOfOrigin_B1F_EventScript_AtSkyPillar
	case 3, CaveOfOrigin_B1F_EventScript_DontRemember
	goto CaveOfOrigin_B1F_EventScript_DontRemember
	end

CaveOfOrigin_B1F_EventScript_AtCaveOfOrigin::
	message CaveOfOrigin_B1F_Text_ButWereInCaveOfOrigin
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_AtMtPyre::
	message CaveOfOrigin_B1F_Text_OldLadyDidntMentionThat
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_DontRemember::
	message CaveOfOrigin_B1F_Text_CantYouRememberSomehow
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_AtSkyPillar::
	msgbox CaveOfOrigin_B1F_Text_WellHeadToSkyPillar, MSGBOX_DEFAULT
	closemessage
	playse SE_EXIT
	fadescreenspeed FADE_TO_BLACK, 4
	setflag FLAG_WALLACE_GOES_TO_SKY_PILLAR
	setvar VAR_SOOTOPOLIS_CITY_STATE, 3
	removeobject LOCALID_CAVE_OF_ORIGIN_WALLACE
	clearflag FLAG_HIDE_SKY_PILLAR_WALLACE
	fadescreen FADE_FROM_BLACK
	release
	end

CaveOfOrigin_B1F_Text_WallaceStory:
	.string "Ayyy, you must be {PLAYER}.\n"
	.string "I heard all about you.\p"
	.string "Name's MIKE.\p"
	.string "I used to run the GYM in SUGOPOLIS.\n"
	.string "Then somethin' came up, so I gave\l"
	.string "it back to my old teacher, JUAN.\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "OK, here's the deal.\p"
	.string "GROUDON and KYOGRE, the two goin'\n"
	.string "at it out there? Super-ancient\l"
	.string "POKéMON. The real deal.\p"
	.string "But there's a third one.\n"
	.string "RAYQUAZA.\p"
	.string "Way back when, RAYQUAZA broke up\n"
	.string "their fight. Calmed 'em right down.\p"
	.string "Problem is, even I don't know where\n"
	.string "RAYQUAZA's hangin' out these days…$"

CaveOfOrigin_B1F_Text_WhereIsRayquaza:
	.string "MIKE: {PLAYER}, you got any idea\n"
	.string "where RAYQUAZA might be?\p"
	.string "If you know, lay it on me.$"

CaveOfOrigin_B1F_Text_ButWereInCaveOfOrigin:
	.string "MIKE: The CAVE OF OREGANO?\p"
	.string "Ayyy, we're standin' in it!\n"
	.string "C'mon, you're better than that.\p"
	.string "Think hard. Where could RAYQUAZA\n"
	.string "be right now?$"

CaveOfOrigin_B1F_Text_OldLadyDidntMentionThat:
	.string "MIKE: MT. PENNE?\p"
	.string "Nah… I just talked to the old lady\n"
	.string "up there. She didn't say nothin'.\p"
	.string "And that sweet lady wouldn't keep\n"
	.string "secrets from me. She makes the best\l"
	.string "gnocchi in PASTALIA!\p"
	.string "{PLAYER}, think it over again\n"
	.string "for me.$"

CaveOfOrigin_B1F_Text_CantYouRememberSomehow:
	.string "MIKE: Whoa, you don't remember?\n"
	.string "Hmm… That's a problem.\p"
	.string "Take a breath. It'll come to you.$"

CaveOfOrigin_B1F_Text_WellHeadToSkyPillar:
	.string "MIKE: The SKY BREADSTICK?\p"
	.string "Correctamundo!\n"
	.string "It's gotta be the SKY BREADSTICK!\p"
	.string "{PLAYER}, no time to waste!\n"
	.string "To the SKY BREADSTICK, pronto!$"

