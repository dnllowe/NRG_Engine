#include "nrgAudio.h"

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
OSLESMediaPlayer* nrgAudio::androidAudioPlayer = NULL;
#endif
CocosDenshion::SimpleAudioEngine* nrgAudio::audioPlayer = NULL;
cocos2d::experimental::AudioEngine* nrgAudio::audioPlayer2 = NULL;
int nrgAudio::musicID;
cocos2d::experimental::AudioProfile* nrgAudio::audioProfile;
nrgAudio* nrgAudio::nrgAudioPlayer = NULL;

nrgAudio::nrgAudio()
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	androidAudioPlayer = new OSLESMediaPlayer;
#endif
	audioPlayer = CocosDenshion::SimpleAudioEngine::getInstance();
}

nrgAudio * nrgAudio::getInstance()
{
	if (nrgAudioPlayer == NULL)
		nrgAudioPlayer = new nrgAudio;

	return nrgAudioPlayer;
}

void nrgAudio::LoadClip(std::string filePathInput)
{
#if(CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)

	std::string loadFile; //String to hold modified file values

	//Add prefix and append filetype to filepath
	loadFile.append("audio/m4a/");
	loadFile.append(filePathInput);
	loadFile.append(".m4a");
	
	//Preload audio clip
	audioPlayer->preloadEffect(loadFile.c_str());

#endif
	return;
}

void nrgAudio::PlayClip(std::string clip)
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	androidAudioPlayer->Play(clip); //For Android, provide audio txt file
#else
	std::string loadFile; //String to hold modified file values
	//Add prefix and append filetype to filepath
	loadFile.append("audio/m4a/");
	loadFile.append(clip);
	loadFile.append(".m4a");
	audioPlayer->playEffect(loadFile.c_str()); //For iOS/Windows, provide filepath of audio
#endif
}

OSLESMediaPlayer * nrgAudio::GetAndroidAudioPlayer()
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	return androidAudioPlayer;
#else
	return NULL;
#endif
}

void nrgAudio::LoadMusic(std::string filePath)
{
	std::string loadFile; //String to hold modified file values
	//Add prefix and append filetype to filepath
	loadFile.append("audio/BGM/");
	loadFile.append(filePath);
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	loadFile.append(".ogg");
#else
	loadFile.append(".m4a");
#endif
	audioPlayer->preloadBackgroundMusic(loadFile.c_str());
	return;
}

void nrgAudio::PlayMusic(std::string filePath, bool loop)
{
	std::string loadFile; //String to hold modified file values
	//Add prefix and append filetype to filepath
	loadFile.append("audio/BGM/");
	loadFile.append(filePath);
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	loadFile.append(".ogg");
#else
	loadFile.append(".m4a");
#endif
	audioPlayer->playBackgroundMusic(loadFile.c_str(), loop);
	return;
}

void nrgAudio::PauseMusic()
{	
	if(audioPlayer != NULL && audioPlayer->isBackgroundMusicPlaying())
		audioPlayer->pauseBackgroundMusic();
	return;
}

void nrgAudio::ResumeMusic()
{
	if (audioPlayer != NULL && audioPlayer->isBackgroundMusicPlaying())
		audioPlayer->resumeBackgroundMusic();
	return;
}

void nrgAudio::StopMusic(bool release)
{
    if(audioPlayer != NULL && audioPlayer->isBackgroundMusicPlaying())
        audioPlayer->stopBackgroundMusic(release);
	return;
}

void nrgAudio::SetMusicVolume(float value)
{
	audioPlayer->setBackgroundMusicVolume(value);
	return;
}

void nrgAudio::SetClipVolume(float value)
{
    audioPlayer->setEffectsVolume(value);
    return;
}

void nrgAudio::MuteSound()
{
	audioPlayer->setEffectsVolume(0);
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	androidAudioPlayer->MuteSound(); 
#endif
	return;
}

void nrgAudio::UnmuteSound()
{
	audioPlayer->setEffectsVolume(1);
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	androidAudioPlayer->UnmuteSound();
#endif

	return;
}

void nrgAudio::PauseAudio()
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	androidAudioPlayer->Pause();
#else
	audioPlayer->pauseAllEffects();
#endif
	
    if(audioPlayer != NULL && audioPlayer->isBackgroundMusicPlaying())
        audioPlayer->pauseBackgroundMusic();
	return;
}

void nrgAudio::ResumeAudio()
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	androidAudioPlayer->Resume();
#else
	audioPlayer->resumeAllEffects();
#endif
	audioPlayer->resumeBackgroundMusic();

	return;
}

nrgAudio::~nrgAudio()
{
	if (nrgAudioPlayer != NULL)
		delete nrgAudioPlayer;
	nrgAudioPlayer = NULL;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if(androidAudioPlayer != NULL)
		delete androidAudioPlayer;
	androidAudioPlayer = NULL;
#endif
}
