#pragma once
#include "pch.h"
#include <fstream>
#include <iostream>

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "android\CCFileUtils-android.h"
#include "platform/android/jni/JniHelper.h"
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/log.h>
#endif

#include "platform/android/CCFileUtils-android.h"

class nrgFileManager
{
public:
	static nrgFileManager* getInstance();

	//Create file
	void Create(std::string filename);

	///Delete file
	void Delete(std::string filename);

	//Save all current mapped values to file
	void Save(std::string filename);

	//Load all data from file into maps
	void Load(std::string filename);

	//Write string  value to file
	void WriteToFile(std::string filename, std::string key, std::string input);

	//Write integer value to file
	void WriteToFile(std::string filename, std::string key, int input); 

	//Write float value to file
	void WriteToFile(std::string filename, std::string key, float input);

	//Write bool value to file
	void WriteToFile(std::string filename, std::string key, bool input);

	~nrgFileManager();

protected:
	nrgFileManager(); //Default constructor is protected. Use getInstance()
	static nrgFileManager* nrgFM; //Single instance of nrgFileManager
	std::fstream fileIO; //Read/Write file object for functios
	std::string filepath; //Filepath for files on device
	std::string line; //Line to read from file
	std::string tag; //Tag key as either string (S), int (I), float (F) or bool (B)
	cocos2d::FileUtils* fileUtils = cocos2d::FileUtils::getInstance(); //Cocos File Utility helper
	std::map<std::string, std::map<std::string, std::string>> stringMap; //Map for string values. <filename, key, value>
	std::map<std::string, std::map<std::string, int>> intMap; //Map for integer values. <filename, key, value>
	std::map<std::string, std::map<std::string, float>> floatMap; //Map for float values. <filename, key, value>
	std::map<std::string, std::map<std::string, bool>> boolMap; //Map for bool values. <filename, key, value>
};

