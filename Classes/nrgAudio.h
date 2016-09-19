#pragma once
#include "pch.h"

//Forward declarate for AppDelegate
class AppDelegate;

//Global audio player for nrgEngine. Retrieve with nrgAudio::getInstance()
class nrgAudio
{
public:

	//Give AppDelegate access to protected functions
	friend class AppDelegate;
	
	//Get instance of nrgAudio Player
	static nrgAudio* getInstance();

	//Load sound clips for iOS/Windows using filepath, and catalog soundID for Android
	static void LoadClip(std::string filePathInput); 

	//Plays preloaded clips
	static void PlayClip(std::string clip);

	//Returns Android audio player
	static OSLESMediaPlayer* GetAndroidAudioPlayer();

	//Load background music
	static void LoadMusic(std::string filePath);

	//Play background music
	static void PlayMusic(std::string filePath, bool loop = true);

	//Pause backgound music
	static void PauseMusic();

	//Resume music (after pause, not stop--which releases music)
	static void ResumeMusic();

	//Stop music. Release music.
	static void StopMusic(bool release = true);

	//Set music volume
	static void SetMusicVolume(float value);
    
    //Set sound effect volume
    static void SetClipVolume(float value);
    
	//Mutes sound volume
	static void MuteSound();

	//Unmute sound volume
	static void UnmuteSound();

	//Pause all audio
	static void PauseAudio();

	//Resumes all audio
	static void ResumeAudio();

	//Sets playback rate to a given value (alters pitch for iOS, alters playback rate for Android)
//	static void SetPlaybackRate(float value);

	//Set music to loop
//	static void SetLoop(bool value = true);

	//Release assets. Free memory
	~nrgAudio();
	static int musicID; //The audio ID for background music
protected:
	nrgAudio();
	static nrgAudio* nrgAudioPlayer;

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	static OSLESMediaPlayer* androidAudioPlayer; //OpenSL ES Audio player for android audio clips
#endif
	static CocosDenshion::SimpleAudioEngine* audioPlayer; //Cocos2d Audio player for iOs/Windows clips and bg music for all platforms
	static cocos2d::experimental::AudioEngine* audioPlayer2;
	
	static cocos2d::experimental::AudioProfile* audioProfile;
};

