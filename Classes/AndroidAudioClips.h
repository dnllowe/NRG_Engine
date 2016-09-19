#pragma once
#include "pch.h"

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//Include all audio clip headers
#include "block.h"
#include "chime.h"
#include "hitEnemy1.h"
#include "hitEnemy2.h"
#include "hitEnemy3.h"
#include "hitPlayer1.h"
#include "hitPlayer2.h"
#include "hitPlayer3.h"
#include "miss1.h"
#include "miss2.h"
#include "multiplierDown.h"
#include "multiplierUp.h"
#include "tick.h"
#include "silence.h"

#include <jni.h> //For Java code interface
#include "platform/android/jni/JniHelper.h"
#endif

class AndroidAudioClips
{

public:

	//Obtaini Android device buffer size sample rate and set for program
	static void SetAndroidDeviceBufferSize();

	//Load all the Android audio clips
	static void LoadAndroidAudioFiles();

	//Get the Android device buffer size sample rate
	static unsigned long int GetDeviceBufferSize();

protected:
	AndroidAudioClips();
	~AndroidAudioClips(); //Release android audio files from memory

	static unsigned long int deviceBufferSize; //Stores device sample rate buffer size
};