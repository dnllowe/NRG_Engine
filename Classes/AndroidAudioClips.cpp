#pragma once
#include "pch.h"
#include "AndroidAudioClips.h"
#include <stdio.h>
#include <iostream>

unsigned long int AndroidAudioClips::deviceBufferSize;

AndroidAudioClips::AndroidAudioClips()
{
}

AndroidAudioClips::~AndroidAudioClips()
{
}

void AndroidAudioClips::SetAndroidDeviceBufferSize()
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//Get helper to load java class, methods, and objects
	cocos2d::JniMethodInfo javaMethodHelper;

	//Get the getDeviceBufferSize() method from AppActivity
	cocos2d::JniHelper::getStaticMethodInfo(javaMethodHelper, "org/cocos2dx/cpp/AppActivity", "getDeviceBufferSize", "()I");

	//Store output from method
	jint size = 0;
	size = javaMethodHelper.env->CallStaticIntMethod(javaMethodHelper.classID, javaMethodHelper.methodID);

	//Set device buffer size to size * 1000 (OpenSL ES takes sample rate in milliseconds vs seconds)
	deviceBufferSize = size * 1000;
#else
	deviceBufferSize = 44100000;
#endif
}

void AndroidAudioClips::LoadAndroidAudioFiles()
{/*
	//String to hold modified file values
	std::string loadFilePrefix;
	std::string loadFileSuffix = ".txt";

	//Get device sample rate
	int sampleRate = deviceBufferSize / 1000;

	//Only load files for correct sample rate
	switch (sampleRate)
	{
	case 8000:
		loadFilePrefix = "Audio/Android/8000/";
		break;
	case 11025:
		loadFilePrefix = "Audio/Android/11025/";
		break;
	case 16000:
		loadFilePrefix = "Audio/Android/16000/";
		break;
	case 22050:
		loadFilePrefix = "Audio/Android/22050/";
		break;
	case 44100:
		loadFilePrefix = "Audio/Android/44100/";
		break;
	case 48000:
		loadFilePrefix = "Audio/Android/48000/";
		break;
	}

	//Keep track of file locations in vector
	//Vector of all audio file names to loop through
	std::vector<std::string>filenames;
	filenames.push_back("test");
//	filenames.push_back("test2");
	unsigned char* fileContent; //Loads non converted data
	std::string currentByte; //Holds current converted byte	from file
	unsigned int output; //Receives byte from stringstream and outputs to vector
	std::string bytes; //Loads all the data, converts to char* and transfers to stringstream
	
	std::vector<unsigned char> byteVector; //Holds the complete set of converted bytes to pass to Android Audio Clips File 
	ssize_t fileSize; //Will keep track of file size

	char currentCharacter; //Iterates through the current byte character
	std::string characterString; //Holds the string for the hex byte
	std::stringstream byteStreamConverter; //Stores the hex strings, converts them, and places to output

	for (int iii = 0; iii < filenames.size(); iii++)
	{
		std::string loadFile = loadFilePrefix;
		loadFile += filenames[iii];
		loadFile += loadFileSuffix;

//		std::string fullFilePath = loadFilePrefix + loadFile + loadFileSuffix; //NEW
		fileContent = cocos2d::FileUtils::getInstance()->getFileData(loadFile, "r", &fileSize);
		
		//Get string for content to determine total number of characters
		std::string fileContentDuplicate = (char *)fileContent; 
	
		//Get clip length (original length less the 44 bytes subtracted from the header, with each byte as 5 characters
		clipLengths.push_back(fileContentDuplicate.length() - 44 * 5);

		//Iterate through string, starting after header (44th byte)
		for (int iii = 0; iii < fileContentDuplicate.length(); iii++)
		{
			// Get the current character
			currentCharacter = fileContent[iii];

			//Make sure current character isn't a space, comma, tab, or new line
			if (currentCharacter == ',' || currentCharacter == ' ' || currentCharacter == '\t' || currentCharacter == '\n' || currentCharacter == '\r')
				;//do nothing

			else
				characterString += currentCharacter; //If not, add hex code to the character string

			//Commas delineate new bytes
			if (currentCharacter == ',')
			{
				//Load current string
				byteStreamConverter << characterString;

				//Convert to hex and load into byte
				byteStreamConverter >> std::hex >> output;

				//Add to vector
				byteVector.push_back((unsigned char)output);

				//Clear string and string stream for next loop
				characterString.clear();
				byteStreamConverter.clear();
			}
		}
		
		//Delete first 44 characters (this is just the header file)
		byteVector.erase(byteVector.begin(), byteVector.begin() + 44);

		//Place byteArray into audioFiles vector
		audioFiles.push_back(byteVector);

		//Clear file content for next loop
		byteVector.clear();
	}
	*/
	return;
}

unsigned long int AndroidAudioClips::GetDeviceBufferSize()
{
	return deviceBufferSize;
}