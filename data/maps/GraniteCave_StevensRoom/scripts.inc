GraniteCave_StevensRoom_MapScripts::
	.byte 0

GraniteCave_StevensRoom_EventScript_Steven::
	lock
	faceplayer
	msgbox GraniteCave_StevensRoom_Text_ImStevenLetterForMe, MSGBOX_DEFAULT
	setvar VAR_0x8004, ITEM_LETTER
	call Common_EventScript_PlayerHandedOverTheItem
	setflag FLAG_DELIVERED_STEVEN_LETTER
	msgbox GraniteCave_StevensRoom_Text_ThankYouTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM_STEEL_WING
	call_if_eq VAR_RESULT, FALSE, GraniteCave_StevensRoom_EventScript_BagFull
	@ Fettuccine: Steven (Sam) gives the Mega Ring here
	msgbox GraniteCave_StevensRoom_Text_TakeMegaRing, MSGBOX_DEFAULT
	giveitem ITEM_MEGA_RING
	msgbox GraniteCave_StevensRoom_Text_ExplainMegaRing, MSGBOX_DEFAULT
	msgbox GraniteCave_StevensRoom_Text_CouldBecomeChampionLetsRegister, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox GraniteCave_StevensRoom_Text_RegisteredSteven, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_REGISTERED_STEVEN_POKENAV
	msgbox GraniteCave_StevensRoom_Text_IveGotToHurryAlong, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_NORTH, GraniteCave_StevensRoom_EventScript_StevenExitNorth
	call_if_eq VAR_FACING, DIR_SOUTH, GraniteCave_StevensRoom_EventScript_StevenExitSouth
	call_if_eq VAR_FACING, DIR_WEST, GraniteCave_StevensRoom_EventScript_StevenExitWestEast
	call_if_eq VAR_FACING, DIR_EAST, GraniteCave_StevensRoom_EventScript_StevenExitWestEast
	playse SE_EXIT
	removeobject LOCALID_GRANITE_CAVE_STEVEN
	release
	end

GraniteCave_StevensRoom_EventScript_StevenExitNorth::
	applymovement LOCALID_GRANITE_CAVE_STEVEN, GraniteCave_StevensRoom_Movement_StevenExit
	waitmovement 0
	return

GraniteCave_StevensRoom_EventScript_StevenExitWestEast::
	applymovement LOCALID_PLAYER, GraniteCave_StevensRoom_Movement_PlayerTurnTowardExit
	applymovement LOCALID_GRANITE_CAVE_STEVEN, GraniteCave_StevensRoom_Movement_StevenExit
	waitmovement 0
	return

GraniteCave_StevensRoom_EventScript_StevenExitSouth::
	applymovement LOCALID_PLAYER, GraniteCave_StevensRoom_Movement_PlayerTurnTowardExit
	applymovement LOCALID_GRANITE_CAVE_STEVEN, GraniteCave_StevensRoom_Movement_StevenExitSouth
	waitmovement 0
	return

GraniteCave_StevensRoom_EventScript_BagFull::
	msgbox GraniteCave_StevensRoom_Text_OhBagIsFull, MSGBOX_DEFAULT
	return

GraniteCave_StevensRoom_Movement_StevenExit:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	delay_8
	step_end

GraniteCave_StevensRoom_Movement_PlayerTurnTowardExit:
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_up
	step_end

GraniteCave_StevensRoom_Movement_StevenExitSouth:
	walk_left
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	delay_8
	step_end

GraniteCave_StevensRoom_Text_ImStevenLetterForMe:
	.string "Oh, hey there! My name is SAM.\p"
	.string "I collect rare cheeses.\p"
	.string "This cave is cool and damp.\n"
	.string "Perfect for aging a wheel of\l"
	.string "cheddar!\p"
	.string "Oh?\n"
	.string "A LETTER for me?$"

GraniteCave_StevensRoom_Text_ThankYouTakeThis:
	.string "SAM: Oh, that's awful nice of you.\p"
	.string "You came all this way just to\n"
	.string "deliver that? I need to thank you.\p"
	.string "Let me see…\n"
	.string "Here, take this TM.\p"
	.string "It's got my favorite move in it,\n"
	.string "STEEL WING.$"

GraniteCave_StevensRoom_Text_CouldBecomeChampionLetsRegister:
	.string "SAM: Your POKéMON look pretty\n"
	.string "capable.\p"
	.string "Keep training, and you could become\n"
	.string "the CHAMPION of the POKéMON LEAGUE\l"
	.string "someday. I really think so.\p"
	.string "Hey, now that we're friends, let's\n"
	.string "register each other in our\l"
	.string "POKéNAVS.\p"
	.string "… … … … … …$"

GraniteCave_StevensRoom_Text_RegisteredSteven:
	.string "Registered SAM\n"
	.string "in the POKéNAV.$"

GraniteCave_StevensRoom_Text_IveGotToHurryAlong:
	.string "Well, I'd better get going.\p"
	.string "This cheddar won't age itself!$"

GraniteCave_StevensRoom_Text_OhBagIsFull:
	.string "Oh, your BAG is full…\n"
	.string "That's a shame.$"

GraniteCave_StevensRoom_Text_TakeMegaRing:
	.string "SAM: Oh, and one more thing.\p"
	.string "I found a rare stone while I was\n"
	.string "down here. Not cheese, but still\l"
	.string "pretty neat!\p"
	.string "I set it into this ring.\n"
	.string "I'd like you to have it.$"

GraniteCave_StevensRoom_Text_ExplainMegaRing:
	.string "SAM: That's a MEGA RING.\p"
	.string "When a POKéMON holds its MEGA STONE,\n"
	.string "the MEGA RING lets it MEGA EVOLVE\l"
	.string "in battle.\p"
	.string "MEGA STONES are hidden all over\n"
	.string "PASTALIA.\p"
	.string "In fact, I hear there's one deep\n"
	.string "inside this very cave…$"
