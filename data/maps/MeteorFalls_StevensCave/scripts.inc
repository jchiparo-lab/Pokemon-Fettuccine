MeteorFalls_StevensCave_MapScripts::
	.byte 0

MeteorFalls_StevensCave_EventScript_Steven::
	lock
	goto_if_set FLAG_DEFEATED_METEOR_FALLS_STEVEN, MeteorFalls_StevensCave_EventScript_Defeated
	waitse
	playse SE_PIN
	applymovement LOCALID_METEOR_FALLS_STEVEN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_METEOR_FALLS_STEVEN, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_METEOR_FALLS_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MeteorFalls_StevensCave_Text_ShouldKnowHowGoodIAmExpectWorst, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_STEVEN, MeteorFalls_StevensCave_Text_StevenDefeat
	msgbox MeteorFalls_StevensCave_Text_MyPredictionCameTrue, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_METEOR_FALLS_STEVEN
	release
	end

MeteorFalls_StevensCave_EventScript_Defeated::
	applymovement LOCALID_METEOR_FALLS_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MeteorFalls_StevensCave_Text_MyPredictionCameTrue, MSGBOX_DEFAULT
	release
	end

MeteorFalls_StevensCave_Text_ShouldKnowHowGoodIAmExpectWorst:
	.string "SAM: Oh, wow, {PLAYER}{KUN}.\n"
	.string "I'm amazed you found me here.\p"
	.string "Do you, uh…maybe think of me as\n"
	.string "just a cheese fanatic?\p"
	.string "Okay, fair.\p"
	.string "But we battled side by side at the\n"
	.string "MOSTACCIDEEP SPACE CENTER.\p"
	.string "You should have a pretty good idea\n"
	.string "how strong I am.\p"
	.string "Okay, {PLAYER}{KUN}, if you want a\n"
	.string "serious challenge, expect the worst!$"

MeteorFalls_StevensCave_Text_StevenDefeat:
	.string "You…\n"
	.string "I had no idea you'd gotten this\l"
	.string "strong…$"

MeteorFalls_StevensCave_Text_MyPredictionCameTrue:
	.string "SAM: You know, ever since we first\n"
	.string "met in GRANITE CAVE in DITALINFORD,\l"
	.string "I had this feeling.\p"
	.string "I thought you'd become the\n"
	.string "CHAMPION someday.\p"
	.string "My hunches are usually right.\n"
	.string "Like knowing when a cheddar's\l"
	.string "ready.\p"
	.string "So where will you go from here?\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "Ha! Even I couldn't tell you that.$"

