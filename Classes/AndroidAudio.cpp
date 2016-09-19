#include "AndroidAudio.h"
/*
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
static void playerEventCallback(void *clientData, SuperpoweredAdvancedAudioPlayerEvent event, void *value) 
{
	if (event == SuperpoweredAdvancedAudioPlayerEvent_LoadSuccess) {
		SuperpoweredAdvancedAudioPlayer *audio = *((SuperpoweredAdvancedAudioPlayer **)clientData);
		audio->setBpm(126.0f);
		audio->setFirstBeatMs(353);
		audio->setPosition(audio->firstBeatMs, false, false);
	};
}

static bool audioProcessing(void *clientdata, short int *audioIO, int numberOfSamples, int samplerate) 
{
	return ((AndroidAudio *)clientdata)->process(audioIO, numberOfSamples);
}

AndroidAudio::AndroidAudio(const char *path, int *params) : activeFx(0), crossValue(0.0f), volB(0.0f), volA(1.0f * headroom) 
{

	pthread_mutex_init(&mutex, NULL); // This will keep our audio volumes and playback states in sync.

	unsigned int samplerate = params[4], buffersize = params[5];

	stereoBuffer = (float *)memalign(16, (buffersize + 16) * sizeof(float) * 2);


	audio = new SuperpoweredAdvancedAudioPlayer(&audio, playerEventCallback, samplerate, 0);
	audio->open(path, params[0], params[1]);

	audioSystem = new SuperpoweredAndroidAudioIO(samplerate, buffersize, false, true, audioProcessing, this, buffersize * 2);
}

AndroidAudio::~AndroidAudio() 
{
	delete audio;
	delete audioSystem;
	free(stereoBuffer);

	pthread_mutex_destroy(&mutex);

}

void AndroidAudio::Play(bool play) 
{

	pthread_mutex_lock(&mutex);
	if (!play)
		audio->pause();
	else 
	{
		bool masterIsA = (crossValue <= 0.5f);
		audio->play(!masterIsA);
	}
	pthread_mutex_unlock(&mutex);

}

#define MINFREQ 60.0f
#define MAXFREQ 20000.0f

static inline float floatToFrequency(float value) 
{
	if (value > 0.97f) return MAXFREQ;
	if (value < 0.03f) return MINFREQ;
	value = powf(10.0f, (value + ((0.4f - fabsf(value - 0.4f)) * 0.3f)) * log10f(MAXFREQ - MINFREQ)) + MINFREQ;
	return value < MAXFREQ ? value : MAXFREQ;
}

bool AndroidAudio::process(short int *output, unsigned int numberOfSamples)
{

	pthread_mutex_lock(&mutex);

	bool masterIsA = (crossValue <= 0.5f);
	float masterBpm = masterIsA ? audio->currentBpm : audio->currentBpm;
	double msElapsedSinceLastBeatA = audio->msElapsedSinceLastBeat; // When playerB needs it, playerA has already stepped this value, so save it now.

	bool silence = !audio->process(stereoBuffer, false, numberOfSamples, volA, masterBpm, audio->msElapsedSinceLastBeat);
	if (audio->process(stereoBuffer, !silence, numberOfSamples, volB, masterBpm, msElapsedSinceLastBeatA)) silence = false;

	pthread_mutex_unlock(&mutex);

	// The stereoBuffer is ready now, let's put the finished audio into the requested buffers.
	if (!silence) SuperpoweredFloatToShortInt(stereoBuffer, output, numberOfSamples);
	return !silence;
}


extern "C" 
{
	JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_AndroidAudio(JNIEnv *javaEnvironment, jobject self, jstring apkPath, jlongArray offsetAndLength);
	JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_Play(JNIEnv *javaEnvironment, jobject self, jboolean play);
}

static AndroidAudio *example = NULL;

// Android is not passing more than 2 custom parameters, so we had to pack file offsets and lengths into an array.
JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_AndroidAudio(JNIEnv *javaEnvironment, jobject self, jstring apkPath, jlongArray params) 
{
	// Convert the input jlong array to a regular int array.
	jlong *longParams = javaEnvironment->GetLongArrayElements(params, JNI_FALSE);
	int arr[6];
	for (int n = 0; n < 6; n++) arr[n] = longParams[n];
	javaEnvironment->ReleaseLongArrayElements(params, longParams, JNI_ABORT);

	const char *path = javaEnvironment->GetStringUTFChars(apkPath, JNI_FALSE);
	example = new AndroidAudio(path, arr);
	javaEnvironment->ReleaseStringUTFChars(apkPath, path);

}

JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_Play(JNIEnv *javaEnvironment, jobject self, jboolean play) 
{
	example->Play(play);
}
#endif
*/
