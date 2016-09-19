#pragma once
/*
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "SuperpoweredSimple.h"
#include "SuperpoweredAdvancedAudioPlayer.h"
#include "SuperpoweredAndroidAudioIO.h"
#include <math.h>
#include <pthread.h>
#include <jni.h>

#define NUM_BUFFERS 2
#define HEADROOM_DECIBEL 3.0f
static const float headroom = powf(10.0f, -HEADROOM_DECIBEL * 0.025);

class AndroidAudio
{
public:
	
	//Initialize and load audio sample
	AndroidAudio(const char *path, int *params);
	~AndroidAudio();

	//Play audio sample. Set to false to pause
	void Play(bool play = true);

	bool process(short int *output, unsigned int numberOfSamples);

protected:

	pthread_mutex_t mutex; //Control threads
	SuperpoweredAndroidAudioIO* audioSystem; //Android audio system
	SuperpoweredAdvancedAudioPlayer* audio; //Audio sample
	float* stereoBuffer; //Audio buffer
	float crossValue, volA, volB;
	unsigned char activeFx;
};
#endif
*/