#include "pch.h"
#include "nrgFileManager.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, "FileManager", __VA_ARGS__) 
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , "FileManager", __VA_ARGS__) 
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO   , "FileManager", __VA_ARGS__) 
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN   , "FileManager", __VA_ARGS__) 
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , "FileManager", __VA_ARGS__) 
#endif
nrgFileManager* nrgFileManager::nrgFM = NULL;

nrgFileManager::nrgFileManager()
{
	//Get file directory for device
	if(CC_PLATFORM_WIN32 || CC_PLATFORM_IOS)
		filepath = fileUtils->getWritablePath();
}

nrgFileManager * nrgFileManager::getInstance()
{
	//If singleton hasn't been created yet, create
	if (nrgFM == NULL)
		nrgFM = new nrgFileManager();

	return nrgFM;
}

void nrgFileManager::Create(std::string filename)
{
	//CREATE WINDOWS FILE

#if(CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID && CC_TARGET_PLATFORM != CC_PLATFORM_IOS)

	//Check to see if file already exists
	std::ifstream read(filepath + filename);
	if (read.is_open())
	{
		read.close();
		return;
	}

	//Create file of filename title and type if file does not already exist
	std::ofstream write(filepath + filename);
	if (write.is_open())
		write.close();

	else
		throw filename + " not created!";
#endif

	
	//CREATE ANDROID FILE
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	//Get helper to load java class, methods, and objects
	cocos2d::JniMethodInfo javaMethodHelper;
	
	//Method One
	
	//Get object
	jobject tempObject = NULL;
	jobject instance = NULL; //Will hold reference to object to prevent Java garbage collection
	
	//Instance object
	cocos2d::JniHelper::getStaticMethodInfo(javaMethodHelper, "org/cocos2dx/cpp/AppActivity", "create", "()Lorg/cocos2dx/cpp/AppActivity;");
	tempObject = javaMethodHelper.env->CallStaticObjectMethod(javaMethodHelper.classID, javaMethodHelper.methodID);
	if (tempObject == NULL)
		LOGD("Temp Object not created properly");
	else
		LOGD("Temp Object was successfully created");
	instance = cocos2d::JniHelper::getEnv()->NewGlobalRef(tempObject);
	if (tempObject == NULL)
		LOGD("Instance not created properly");
	else
		LOGD("Instance was successfully created");

	javaMethodHelper.env->DeleteLocalRef(javaMethodHelper.classID);

	//Call create file method
	jstring jfilename = cocos2d::JniHelper::getEnv()->NewStringUTF(filename.c_str());
	cocos2d::JniHelper::getMethodInfo(javaMethodHelper, "org/cocos2dx/cpp/AppActivity", "CreateFile", "(Ljava/lang/String;)V");
	javaMethodHelper.env->CallVoidMethod(instance, javaMethodHelper.methodID, jfilename);
	javaMethodHelper.env->DeleteLocalRef(javaMethodHelper.classID);
	
	//Free memory
	cocos2d::JniHelper::getEnv()->DeleteGlobalRef(instance);
#endif
	
	return;
}

void nrgFileManager::Delete(std::string filename)
{
	std::string file = filepath + filename;
	std::ifstream read(file);
	
	//First check that file exists
	if (read.is_open())
	{
		read.close();
		std::remove(file.c_str());
	}
	
	//Delete backup file if it exists
	std::string filePrefix; //Filename, not including path or extension
	
	//Get backup save filename
	std::string::iterator begin = filename.begin();
	std::string::iterator end = filename.begin();

	for (int iii = 0; end != filename.end(); end++, iii++)
	{
		if (filename.at(iii) == '.')
			break; //leave loop as soon as file extension starts
	}

	//Get file prefix from characters prior to .extension
	filePrefix.assign(begin, end);
	file = filepath + filePrefix + "_backup.txt";
	
	//First check that file exists
	read.open(file);
	if (read.is_open())
	{
		read.close();
		std::remove(file.c_str());
	}

	return;
}

void nrgFileManager::Save(std::string filenameInput)
{
	//Filename for new file
	std::string filename = filepath + filenameInput; //Full filename, including path and extension
	std::string filePrefix; //Filename, not including path or extension
	std::string relativeFilename = filenameInput; //Filename including extension, but not path

	//Create backup save filename
	std::string::iterator begin = filenameInput.begin();
	std::string::iterator end = filenameInput.begin();

	for (int iii = 0; end != filenameInput.end(); end++, iii++)
	{
		if (filenameInput.at(iii) == '.')		
			break; //leave loop as soon as file extension starts
	}

	//Get file prefix from characters prior to .extension
	filePrefix.assign(begin, end);

	//Check to see if file already exists
	std::ifstream read(filename);
	if (read.is_open())
	{
		read.close();
		//Rename current save file and replace with new save file
		std::string backupFilename = filepath + filePrefix + "_backup.txt";
		//Remove previous backup file
		std::remove(backupFilename.c_str());
		//Make current save file the new backup file
		std::rename(filename.c_str(), backupFilename.c_str());
	}

	//Create a temporary filename
	std::string tempFilename = filepath + filePrefix + "_temp.txt";
	std::ofstream temp(tempFilename);
	
	//Create iterators for loop
	std::map<std::string, std::string>::iterator stringIterator = stringMap[relativeFilename].begin();
	std::map<std::string, int>::iterator intIterator = intMap[relativeFilename].begin();
	std::map<std::string, float>::iterator floatIterator = floatMap[relativeFilename].begin();
	std::map<std::string, bool>::iterator boolIterator = boolMap[relativeFilename].begin();
	
	//Make sure file opens
	if (temp.is_open())
	{
		//Add all data to file. First, the first part of pair (key string), then second part of pair (type value)
		for (stringIterator; stringIterator != stringMap[relativeFilename].end(); stringIterator++)
		{
			temp << stringIterator->first << "\n";
			temp << stringIterator->second << "\n";
		}

		for (intIterator; intIterator != intMap[relativeFilename].end(); intIterator++)
		{
			temp << intIterator->first << "\n";
			temp << intIterator->second << "\n";
		}

		for (floatIterator; floatIterator != floatMap[relativeFilename].end(); floatIterator++)
		{
			temp << floatIterator->first << "\n";
			temp << floatIterator->second << "\n";
		}

		for (boolIterator; boolIterator != boolMap[relativeFilename].end(); boolIterator++)
		{
			temp << boolIterator->first << "\n";
			temp << boolIterator->second << "\n";
		}

		//Close file after writing new data
		temp.close();
		std::rename(tempFilename.c_str(), filename.c_str());
	}

	else
		throw "Unable to open file to save: " + filename;

	return;
}

void nrgFileManager::Load(std::string filenameInput)
{
	//Filename for new file
	std::string filename = filepath + filenameInput; //Full filename, including path and extension
	std::string relativeFilename = filenameInput; //Filename including extension, but not path

	//Open file
	std::ifstream read(filename);
	if (!read.is_open())
		throw "File: " + filename + " does not exist";

	std::string keyLine; //Reads key (first) line of file
	std::string throwAway; //Discard remainder of empty line
	std::string stringInput; //Stores string values for input
	int intInput; //Stores int values for input
	float floatInput; //Stores float values for input
	bool boolInput; //Stores bool values for input
	

	//Read file line by line until end of file/lines
	while (std::getline(read, keyLine))
	{
		//Get tag (first tree characters of line
		std::string tag(keyLine.begin(), keyLine.begin() + 3);

		//Add next line to appropriate map based on tag 

		if (tag == "(S)")
		{
			std::getline(read, stringInput);
			stringMap[relativeFilename][keyLine] = stringInput;
		}

		else if (tag == "(I)")
		{
			read >> intInput;
			intMap[relativeFilename][keyLine] = intInput;
			std::getline(read, throwAway);
		}

		else if (tag == "(F)")
		{
			read >> floatInput;
			floatMap[relativeFilename][keyLine] = floatInput;
			std::getline(read, throwAway);
		}

		else if (tag == "(B)")
		{
			read >> boolInput;
			boolMap[relativeFilename][keyLine] = boolInput;
			std::getline(read, throwAway);
		}
	}

	return;
}


void nrgFileManager::WriteToFile(std::string filename, std::string key, std::string input)
{
	//Tag as string
	tag = "(S)";
	tag.append(key);
	key = tag;

	//Create or update value for key
	stringMap[filename][key] = input;
	return;
}

void nrgFileManager::WriteToFile(std::string filename, std::string key, int input)
{
	//Tag as int
	tag = "(I)";
	tag.append(key);
	key = tag;

	//Create or update value for key
	intMap[filename][key] = input;
	return;
}

void nrgFileManager::WriteToFile(std::string filename, std::string key, float input)
{
	//Tag as float
	tag = "(F)";
	tag.append(key);
	key = tag;

	//Create or update value for key
	floatMap[filename][key] = input;
	return;
}

void nrgFileManager::WriteToFile(std::string filename, std::string key, bool input)
{
	//Tag as bool
	tag = "(B)";
	tag.append(key);
	key = tag;

	//Create or update value for key
	boolMap[filename][key] = input;
	return;
}

nrgFileManager::~nrgFileManager()
{
	if(nrgFM != NULL)
		delete nrgFM;
	nrgFM = NULL;
}
