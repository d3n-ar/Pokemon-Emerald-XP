ShadowBallTutorHouse_MapScripts::
	.byte 0


ShadowBallTutorHouse_EventScript_Teacher::
    lock
    faceplayer
    msgbox ShadowBallTutorHouse_Text_Greeting, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, ShadowBallTutorHouse_EventScript_Decline
    checkitem ITEM_HEART_SCALE, 1
    goto_if_eq VAR_RESULT, FALSE, ShadowBallTutorHouse_EventScript_NoHeartScale
    
    msgbox ShadowBallTutorHouse_Text_TeachShadowBall, MSGBOX_DEFAULT
    removeitem ITEM_HEART_SCALE, 1
    playfanfare MUS_OBTAIN_ITEM
    waitfanfare
    
    msgbox ShadowBallTutorHouse_Text_ChooseMon, MSGBOX_DEFAULT
    // Ensure MOVE_SHADOW_BALL is defined in your move tutor table
    special ChooseMonForMoveTutor
    waitstate
    
    goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, ShadowBallTutorHouse_EventScript_Decline
    
    msgbox ShadowBallTutorHouse_Text_Enjoy, MSGBOX_DEFAULT
    release
    end

ShadowBallTutorHouse_EventScript_NoHeartScale::
    msgbox ShadowBallTutorHouse_Text_NeedHeartScale, MSGBOX_DEFAULT
    release
    end

ShadowBallTutorHouse_EventScript_Decline::
    msgbox ShadowBallTutorHouse_Text_ComeBack, MSGBOX_DEFAULT
    release
    end

ShadowBallTutorHouse_Text_Greeting:
    .string "I can teach your Pokémon SHADOW BALL,\n"
    .string "but I require a HEART SCALE.\l"
    .string "Shall we proceed?$"

ShadowBallTutorHouse_Text_TeachShadowBall:
    .string "Excellent. Let's begin.$"

ShadowBallTutorHouse_Text_ChooseMon:
    .string "Which Pokémon shall learn it?$"

ShadowBallTutorHouse_Text_NeedHeartScale:
    .string "You don't have a HEART SCALE.\n"
    .string "They are quite rare, you know.$"

ShadowBallTutorHouse_Text_Enjoy:
    .string "A fine choice. Use it wisely.$"

ShadowBallTutorHouse_Text_ComeBack:
    .string "I'll be here if you change your mind.$"

