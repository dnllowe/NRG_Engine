#pragma once
#include "nrgFunctions.h"

using namespace cocos2d;
float nrgFunctions::ratio;
float nrgFunctions::zoomRatio;
float nrgFunctions::ar16x9 = 1.7;
float nrgFunctions::ar5x3 = 1.65;
float nrgFunctions::ar16x10 = 1.59;
float nrgFunctions::ar3x2 = 1.49;
float nrgFunctions::ar4x3 = 1.3;
float nrgFunctions::ar1x1 = 1.0;
float nrgFunctions::assetSize = 0;
bool nrgFunctions::landscape = false;

void nrgFunctions::MultiResolutionSupport(ResolutionPolicy resolutionPolicy)
{
	//Get CC Director to obtain window specs
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
    
	//Get CC FileUtils to control file command
	auto fileUtils = FileUtils::getInstance();
	auto screenSize = glview->getFrameSize();
	float screenRatio;

	if (screenSize.width > screenSize.height)
	{
		landscape = true;
		screenRatio = screenSize.width / screenSize.height;
		CCLOG("App is landscape");
	}

	if(screenSize.height > screenSize.width)
	{
		landscape = false;
		screenRatio = screenSize.height / screenSize.width;
		CCLOG("App is portrait");
	}

	ratio = screenRatio; 
	
	//Set design resolution to lowest accepted screen, and scale sprites during creation
	if (landscape)
	{
		if (screenRatio >= ar16x9)
		{
			glview->setDesignResolutionSize(480, 270, resolutionPolicy);
			CCLOG("Aspect ratio is 16:9");
		}
		else if (screenRatio >= ar5x3)
		{
			glview->setDesignResolutionSize(480, 288, resolutionPolicy);
			CCLOG("Aspect ratio is 5:3");
		}
		else if (screenRatio >= ar16x10)
		{
			glview->setDesignResolutionSize(480, 300, resolutionPolicy);
			CCLOG("Aspect ratio is 16:10");
		}
		else if (screenRatio >= ar3x2)
		{
			glview->setDesignResolutionSize(480, 320, resolutionPolicy);
			CCLOG("Aspect ratio is 3:2");
		}
		else if (screenRatio >= ar4x3)
		{
			glview->setDesignResolutionSize(512, 384, resolutionPolicy);
			CCLOG("Aspect ratio is 4:3");
		}
		else if (screenRatio >= ar1x1)
		{
			glview->setDesignResolutionSize(512, 384, resolutionPolicy);
			CCLOG("Using Aspect ratio 1:1");
		}
	}

	if (!landscape)
	{
		if (screenRatio >= ar16x9)
		{
			glview->setDesignResolutionSize(270, 480, resolutionPolicy);
			CCLOG("Aspect ratio is 16:9");
		}
		else if (screenRatio >= ar5x3)
		{
			glview->setDesignResolutionSize(288, 480, resolutionPolicy);
			CCLOG("Aspect ratio is 5:3");
		}
		else if (screenRatio >= ar16x10)
		{
			glview->setDesignResolutionSize(300, 480, resolutionPolicy);
			CCLOG("Aspect ratio is 16:10");
		}
		else if (screenRatio >= ar3x2)
		{
			glview->setDesignResolutionSize(320, 480, resolutionPolicy);
			CCLOG("Aspect ratio is 3:2");
		}
		else if (screenRatio >= ar4x3)
		{
			glview->setDesignResolutionSize(384, 512, resolutionPolicy);
			CCLOG("Aspect ratio is 4:3");
		}
		else if (screenRatio >= ar1x1)
		{
			glview->setDesignResolutionSize(384, 512, resolutionPolicy);
			CCLOG("Using Aspect ratio 1:1");
		}
	}

	//Get zoom ratio between design resolution size and actual device screen size.
	//The Cocos2dX Enginie will automatically scale sprites to this when using design ratios
	//To render at correct zoom level, you must divide sprite by this zoomRatio (in ResizeForDevice)
	zoomRatio = MAX(glview->getFrameSize().width / glview->getDesignResolutionSize().width, glview->getFrameSize().height / glview->getDesignResolutionSize().height);

	//Sets file paths for different resolution director folders in Resources
	std::vector<std::string> resolutionDirectories;
	
	//Add resolution directory paths based on aspect ratio
	if (screenRatio >= ar16x9)
	{
		//Start with screen resolution, then search folders of descending size
		if (2560 <= screenSize.width || 2560 <= screenSize.height)
		{
			resolutionDirectories.push_back("images/16x9/2560x1440/");
			CCLOG("Added \"images/16x9/2560x1440/\" to resolution directory");
			
			if (assetSize == 0)
				assetSize = 2560;
		}
		if (1920 <= screenSize.width || 1920 <= screenSize.height)
		{
			resolutionDirectories.push_back("images/16x9/1920x1080/");
			CCLOG("Added \"images/16x9/1920x1080/\" to resolution directory");

			if (assetSize == 0)
				assetSize = 1920;
		}
		if (1280 <= screenSize.width || 1280 <= screenSize.height)
		{
			resolutionDirectories.push_back("images/16x9/1280x720");
			CCLOG("Added \"images/16x9/1280x720/\" to resolution directory");

			if (assetSize == 0)
				assetSize = 1280;
		}
		if (1136 <= screenSize.width || 1136 <= screenSize.height)
		{
			resolutionDirectories.push_back("images/16x9/1136x640");
			CCLOG("Added \"images/16x9/1136x640/\" to resolution directory");

			if (assetSize == 0)
				assetSize = 1136;
		}
		if (960 <= screenSize.width || 960 <= screenSize.height)
		{
			resolutionDirectories.push_back("images/16x9/960x540/");
			CCLOG("Added \"images/16x9/960x540/\" to resolution directory");

			if (assetSize == 0)
				assetSize = 960;
		}
		resolutionDirectories.push_back("images/16x9/480x270/");
		CCLOG("Added \"images/16x9/480x270/\" to resolution directory");

		if (assetSize == 0)
			assetSize = 480;
	}

	else if (screenRatio >= ar5x3)
	{
		//Uses same assets as 1280x720
		resolutionDirectories.push_back("images/16x9/1280x720/");
		CCLOG("Added \"images/16x9/1280x720/\" to resolution directory (5:3 1280x768 uses same assets as 16x9 1280x720");

		if (assetSize == 0)
			assetSize = 1280;
	}

	else if (screenRatio >= ar16x10)
	{
		//Uses same assets as 16:9 2560x1440
		if (2560 <= screenSize.width || 2560 <= screenSize.height)
		{
			resolutionDirectories.push_back("images/16x9/2560x1440/");
			CCLOG("Added \"images/16x9/2560x1440/\" to resolution directory 16:10 2560x1600 uses same assets as 16x9 2560x1440");

			if (assetSize == 0)
				assetSize = 2560;
		}
		
		//Uses same assets as 1280x720
		resolutionDirectories.push_back("images/16x9/1280x720/");
		CCLOG("Added \"images/16x9/1280x720/\" to resolution directory (16:10 1280x800 uses same assets as 16x9 1280x720");

		if (assetSize == 0)
			assetSize = 1280;
	}

	else if (screenRatio >= ar3x2)
	{
		//Start with screen resolution, then search folders of descending size
		if (1920 <= screenSize.width || 1920 <= screenSize.height)
		{
			resolutionDirectories.push_back("images/3x2/1920x1280/");
			CCLOG("Added \"images/3x2/1920x1280/\" to resolution directory");

			if (assetSize == 0)
				assetSize = 1920;
		}
		if (1440 <= screenSize.width || 1440 <= screenSize.height)
		{
			resolutionDirectories.push_back("images/3x2/1440x960/");
			CCLOG("Added \"images/3x2/1440x960/\" to resolution directory");

			if (assetSize == 0)
				assetSize = 1440;
		}
		if (960 <= screenSize.width || 960 <= screenSize.height)
		{
			resolutionDirectories.push_back("images/3x2/960x640/");
			CCLOG("Added \"images/3x2/960x640/\" to resolution directory");

			if (assetSize == 0)
				assetSize = 960;
		}
		resolutionDirectories.push_back("images/3x2/480x320/");
		CCLOG("Added \"images/3x2/480x320/\" to resolution directory");

		if (assetSize == 0)
			assetSize = 480;
	}

	else if (screenRatio >= ar4x3 || screenRatio >= ar1x1)
	{
		//If device is not exact resolution (such as Android navigation bar cutting off pixels), find out which resolution it's closest to
		bool use2048 = false;
		bool use1024 = false;
		bool use512 = false;
		int dimension;

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if (landscape)
			dimension = screenSize.width;
		else if (!landscape)
			dimension = screenSize.height;
		
		if (dimension >= 1600)
			use2048 = true;
		else if (dimension >= 800)
			use1024 = true;
		else
			use512 = true;
#endif

		//Start with screen resolution, then search folders of descending size
		if (2048 <= screenSize.width || 2048 <= screenSize.height || use2048)
		{
			resolutionDirectories.push_back("images/4x3/2048x1536/");
			CCLOG("Added \"images/4x3/2048x1536/\" to resolution directory");

			if (assetSize == 0)
				assetSize = 2048;
		}
		if (1024 <= screenSize.width || 1024 <= screenSize.height || use1024)
		{
			resolutionDirectories.push_back("images/4x3/1024x768/");
			CCLOG("Added \"images/4x3/1024x768/\" to resolution directory");

			if (assetSize == 0)
				assetSize = 1024;
		}
		resolutionDirectories.push_back("images/4x3/512x384/");
		CCLOG("Added \"images/4x3/512x384/\" to resolution directory");

		if (assetSize == 0)
			assetSize = 512;
	}

	//Character array to hold file folder strings
	char file[256];

	//Now search pixel-density-specific folders
	for (int iii = 8; iii > 1; iii--)
	{
		sprintf(file, "images/all_aspect_ratios/%dx/", iii);

		//Use next highest zoomRatio if zoom factor is any amount above
		if (zoomRatio > iii - 1)
			resolutionDirectories.push_back(file);
	}

	//Now push back aspect ratio-independent directory
	resolutionDirectories.push_back("images/all_aspect_ratios/all_devices/");
	CCLOG("Added \"images/all_aspect_ratios/all_devices\" to resolution directory");
	
	//Now search the general images folder
	resolutionDirectories.push_back("images/");
	CCLOG("Added \"images/\" to resolution directory");
	
	fileUtils->setSearchPaths(resolutionDirectories);
	
	if (fileUtils->getSearchPaths().size() == resolutionDirectories.size() + 1)
		CCLOG("All search paths added");
	else
		CCLOG("Search paths not added properly");

	return;
}

void nrgFunctions::CreateSpriteBatch(std::string fileName, cocos2d::SpriteBatchNode*& batch, cocos2d::SpriteFrameCache*& cache)
{
	//Load sprite batch png
	batch = cocos2d::SpriteBatchNode::create(fileName + ".png");

	//Create cache of sprite information from plist
	cache->addSpriteFramesWithFile(fileName + ".plist");
}

void nrgFunctions::ResizeForDevice(cocos2d::Sprite* sprite, float additionalScaling)
{
	//Get CC Director to obtain window specs
	auto glview = cocos2d::Director::getInstance()->getOpenGLView();
	auto screenSize = glview->getFrameSize();

	//Scale assuming asset size matches device screen size
	float presumedScale = 1 / zoomRatio;

	//Figure out how close device screen is to assets loaded
	float dimension;
	if (landscape)
		dimension = screenSize.width;
	else if (!landscape)
		dimension = screenSize.height;
	float adjustedScale = dimension / assetSize;

	//The presumed scale is how different the asset is from the design resolution. 
	//Then, this must be multiplied by the adjusted scale, which is how different the screen size is from the intended asset size
	//If the design resolution = asset size, this will equal a scale of 1 because the Cocos2d Engine will automatically scale the assets down
	//If the design resolution != asset size, then this will adjust the assets accordingly (whether they need to be larger or smaller for device)
	//Finally, if we need to scale further than what is done automatically, use additionalScaling argument (defaults to 1.0)
	sprite->setScale(presumedScale * adjustedScale * additionalScaling);
    
	return;
}

void nrgFunctions::ResizeForDevice(nrgSprite* sprite, float additionalScaling)
{
	//Get CC Director to obtain window specs
	auto glview = cocos2d::Director::getInstance()->getOpenGLView();
	auto screenSize = glview->getFrameSize();

	//Scale assuming asset size matches device screen size
	float presumedScale = 1 / zoomRatio;

	//Figure out how close device screen is to assets loaded
	float dimension;
	if (landscape)
		dimension = screenSize.width;
	else if (!landscape)
		dimension = screenSize.height;
	float adjustedScale = dimension / assetSize;

	//The presumed scale is how different the asset is from the design resolution. 
	//Then, this must be multiplied by the adjusted scale, which is how different the screen size is from the intended asset size
	//If the design resolution = asset size, this will equal a scale of 1 because the Cocos2d Engine will automatically scale the assets down
	//If the design resolution != asset size, then this will adjust the assets accordingly (whether they need to be larger or smaller for device)
	//Finally, if we need to scale further than what is done automatically, use additionalScaling argument (defaults to 1.0)
	sprite->setScale(presumedScale * adjustedScale * additionalScaling);

	return;
}

void nrgFunctions::ResizeForDevice(cocos2d::SpriteBatchNode* batch, float additionalScaling)
{
	//Get CC Director to obtain window specs
	auto glview = cocos2d::Director::getInstance()->getOpenGLView();
	auto screenSize = glview->getFrameSize();

	//Scale assuming asset size matches device screen size
	float presumedScale = 1 / zoomRatio;

	//Figure out how close device screen is to assets loaded
	float dimension;
	if (landscape)
		dimension = screenSize.width;
	else if (!landscape)
		dimension = screenSize.height;
	float adjustedScale = dimension / assetSize;

	//The presumed scale is how different the asset is from the design resolution. 
	//Then, this must be multiplied by the adjusted scale, which is how different the screen size is from the intended asset size
	//If the design resolution = asset size, this will equal a scale of 1 because the Cocos2d Engine will automatically scale the assets down
	//If the design resolution != asset size, then this will adjust the assets accordingly (whether they need to be larger or smaller for device)
	//Finally, if we need to scale further than what is done automatically, use additionalScaling argument (defaults to 1.0)
	batch->setScale(presumedScale * adjustedScale * additionalScaling);

	return;
}

void nrgFunctions::AddHorizontalLetterbox(nrgScene* scene, float percentage)
{
	//Change screen height based on percentage, set x and y origins, set letterbox size based on remaining percentage
	scene->SCREEN_HEIGHT = scene->glview->getDesignResolutionSize().height * percentage;
	scene->HORIZONTAL_LETTERBOX_WIDTH = scene->SCREEN_WIDTH;
	scene->HORIZONTAL_LETTERBOX_HEIGHT = scene->glview->getDesignResolutionSize().height * (1 - percentage ) / 2 + 1; //Oversize by one pixel to make sure no white lines appear
	scene->X_ORIGIN = scene->VERTICAL_LETTERBOX_WIDTH;
	scene->Y_ORIGIN = scene->HORIZONTAL_LETTERBOX_HEIGHT - 1; //Bring down by one pixel to make sure there are no white lines

	//Create letterbox bars
	scene->LETTERBOX_BOTTOM = cocos2d::Sprite::create("square.png");
	scene->LETTERBOX_TOP = cocos2d::Sprite::create("square.png");

	//Add letterbox bars to scene
	scene->addChild(scene->LETTERBOX_BOTTOM);
	scene->addChild(scene->LETTERBOX_TOP);
	scene->LETTERBOX_BOTTOM->setAnchorPoint(cocos2d::Vec2(0, 0));
	scene->LETTERBOX_TOP->setAnchorPoint(cocos2d::Vec2(0, 0));

	//Size letterbox bars
	scene->LETTERBOX_TOP->setScale(scene->HORIZONTAL_LETTERBOX_WIDTH, scene->HORIZONTAL_LETTERBOX_HEIGHT);
	scene->LETTERBOX_BOTTOM->setScale(scene->HORIZONTAL_LETTERBOX_WIDTH, scene->HORIZONTAL_LETTERBOX_HEIGHT);

	//Place letterbox bars
	scene->LETTERBOX_BOTTOM->setPosition(scene->VERTICAL_LETTERBOX_WIDTH, 0);
	scene->LETTERBOX_TOP->setPosition(scene->VERTICAL_LETTERBOX_WIDTH, scene->SCREEN_HEIGHT + scene->HORIZONTAL_LETTERBOX_HEIGHT - 2); //Bring down by 2 pixels to cover any white lines

	//Set letterbox bars to black
	scene->LETTERBOX_BOTTOM->setColor(cocos2d::Color3B::BLACK);
	scene->LETTERBOX_TOP->setColor(cocos2d::Color3B::BLACK);

	//Make sure boxes are rendered last
	scene->LETTERBOX_BOTTOM->setLocalZOrder(1000);
	scene->LETTERBOX_TOP->setLocalZOrder(1000);
	
	return;
}

void nrgFunctions::AddVerticalLetterbox(nrgScene * scene, float percentage)
{
	//Change screen height based on percentage, set x and y origins, set letterbox size based on remaining percentage
	scene->SCREEN_WIDTH = scene->glview->getDesignResolutionSize().width * percentage;
	scene->VERTICAL_LETTERBOX_HEIGHT = scene->SCREEN_HEIGHT;
	scene->VERTICAL_LETTERBOX_WIDTH = scene->glview->getDesignResolutionSize().width * (1 - percentage) / 2 + 1; //Oversize by one pixel to make sure no white lines appear
	scene->X_ORIGIN = scene->VERTICAL_LETTERBOX_WIDTH;
	scene->Y_ORIGIN = scene->HORIZONTAL_LETTERBOX_HEIGHT;

	//Create letterbox bars
	scene->LETTERBOX_LEFT = cocos2d::Sprite::create("square.png");
	scene->LETTERBOX_RIGHT = cocos2d::Sprite::create("square.png");

	//Add letterbox bars to scene
	scene->addChild(scene->LETTERBOX_LEFT);
	scene->addChild(scene->LETTERBOX_RIGHT);
	scene->LETTERBOX_BOTTOM->setAnchorPoint(cocos2d::Vec2(0, 0));
	scene->LETTERBOX_TOP->setAnchorPoint(cocos2d::Vec2(0, 0));

	//Size letterbox bars
	scene->LETTERBOX_TOP->setScale(scene->VERTICAL_LETTERBOX_WIDTH, scene->VERTICAL_LETTERBOX_HEIGHT);
	scene->LETTERBOX_BOTTOM->setScale(scene->VERTICAL_LETTERBOX_WIDTH, scene->VERTICAL_LETTERBOX_HEIGHT);

	//Place letterbox bars
	scene->LETTERBOX_LEFT->setPosition(0, scene->HORIZONTAL_LETTERBOX_HEIGHT);
	scene->LETTERBOX_RIGHT->setPosition(scene->VERTICAL_LETTERBOX_WIDTH + scene->SCREEN_WIDTH - 2, scene->HORIZONTAL_LETTERBOX_HEIGHT); //Bring left by 2 pixels to cover any white lines

	//Set letterbox bars to black
	scene->LETTERBOX_BOTTOM->setColor(cocos2d::Color3B::BLACK);
	scene->LETTERBOX_TOP->setColor(cocos2d::Color3B::BLACK);
	
	return;
}

int nrgFunctions::GetRandom(int min, int max)
{
    //Return random number if no range specified
    if (min == 0 && max == 0)
        return cocos2d::random();
    
    //Same number given for min and max (no range exists).
    else if (min == max)
        return min;
    
    //Select random number between range
    else
    {
        int value = cocos2d::random(min, max);
        return value;
    }
}

int nrgFunctions::GetRandom(int min, int max, int excludedNumber)
{
    //If same number given, return number
    if (min == max)
		return min;
	
	//Select random number between range. Repeat if excluded number is selected
	else
	{
		int value = cocos2d::random(min, max);
        int loopIterations = 0;
        
		//If exluding number, check to make sure this number isn't exluded
		while (value == excludedNumber)
		{
            value = cocos2d::random(min, max);
            
            loopIterations++;
            
            if(loopIterations >= 50)
                CCLOG("Stuck in Get Random Loop");
        }
        return value;
	}
}

int nrgFunctions::GetRandom(int min, int max, std::unordered_set<int> excludedNumbers)
{
	//No numbers to exclude, run normal GetRandom function
	if (excludedNumbers.size() == 0)
		return GetRandom(min, max);

	//Make sure at least one value is not excluded
	int maxPossibilities = (max - min + 1);

	//Check excluded numbers here
	if (excludedNumbers.size() == maxPossibilities)
	{
		CCLOG("GetRandom() excludes all possible values");
		throw;
	}

	//Now, get random value within range
	int value = cocos2d::random(min, max);

	int loopIterations = 0;

	//Check to make sure value isn't exluded (if iterator reaches end, value is not in vector)
	while (excludedNumbers.find(value) != excludedNumbers.end())
	{
		value = cocos2d::random(min, max);
		
		loopIterations++;

		if(loopIterations >= 50)
			CCLOG("Stuck in Get Random Loop");
	}

	//Return only a non-excluded value here
	return value;
}

std::pair<int, int> nrgFunctions::GetRandomPair(int xMin, int xMax, int yMin, int yMax)
{
	//Pair to hold random numbers
	std::pair<int, int> randomPair;

	//Get values within x/y range
	int value1 = cocos2d::random(xMin, xMax);
	int value2 = cocos2d::random(yMin, yMax);

	//Place into pair and return
	randomPair.first = value1;
	randomPair.second = value2; 

	return randomPair;
}

std::pair<int, int> nrgFunctions::GetRandomPair(int xMin, int xMax, int yMin, int yMax, std::unordered_set<std::pair<int, int>, pair_hash> excludedPairs)
{
	//No numbers to exclude, run normal GetRandom function
	if (excludedPairs.size() == 0)
		return GetRandomPair(xMin, xMax, yMin, yMax);

	//Make sure at least one value is not excluded
	int maxPossibilities = (xMax - xMin + 1) * (yMax - yMin + 1);

	//Check excluded numbers here
	if (excludedPairs.size() == maxPossibilities)
	{
		CCLOG("GetRandomPairs() excludes all possible values");
		throw;
	}

	//Now, get random values within range
	int value1 = cocos2d::random(xMin, xMax);
	int value2 = cocos2d::random(yMin, yMax);

	//Create pair using random values
	std::pair<int, int> randomPair;
	randomPair.first = value1;
	randomPair.second = value2;

	//Iterator for end of set
	std::unordered_set<std::pair<int, int>, pair_hash>::iterator end = excludedPairs.end();

	//Check to make sure value isn't exluded (if iterator reaches end, value is not in vector)
	while (excludedPairs.find(randomPair) != end)
	{
		//Get new random values within range
		value1 = cocos2d::random(xMin, xMax);
		value2 = cocos2d::random(yMin, yMax);

		//Create new pair using random values
		randomPair.first = value1;
		randomPair.second = value2;
	}

	//Return only a non-excluded value here
	return randomPair;
}

int nrgFunctions::GetRandomChoice(int n1, int n2)
{
	int value = cocos2d::random(0, 1);
	
	if (value == 0)
		return n1;
	else
		return n2;
}

void nrgFunctions::Center(cocos2d::Node * node)
{
	//Set anchor point to center of sprite
	node->setAnchorPoint(cocos2d::Vec2(0, 0));

	//Get screen width and height
	auto director = cocos2d::Director::getInstance();
	int width = director->getOpenGLView()->getFrameSize().width;
	int height = director->getOpenGLView()->getFrameSize().height;

	//Center image
	node->setPosition(width / 2 - node->getContentSize().width / 2, height / 2 - node->getContentSize().height / 2);

	return;
}

void nrgFunctions::Center(nrgSprite * sprite1, nrgSprite * sprite2, int offsetX, int offsetY)
{
	sprite1->setPositionX(sprite2->getPositionX() + sprite2->GetWidth() / 2 - sprite1->GetWidth() / 2 + offsetX);
	sprite1->setPositionY(sprite2->getPositionY() + sprite2->GetHeight() / 2 - sprite1->GetHeight() / 2 + offsetY);
	return;
}

void nrgFunctions::Center(nrgText * text, nrgSprite * sprite, int offsetX, int offsetY)
{
	text->setPositionX(sprite->getPositionX() + sprite->GetWidth() / 2 - text->GetScaledWidth() / 2 + offsetX);
	text->setPositionY(sprite->getPositionY() + sprite->GetHeight() / 2 + text->GetScaledHeight() / 2 + offsetY);
	return;
}

float nrgFunctions::GetRatio()
{
	return ratio;
}

float nrgFunctions::GetZoomRatio()
{
	return zoomRatio;
}

cocos2d::Size nrgFunctions::GetScreenSize()
{
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	auto screenSize = glview->getFrameSize();
	return screenSize;
}

float nrgFunctions::GetAssetSize()
{
	return assetSize;
}

//Deprecated. Use MultiReslutionSupport instead
void nrgFunctions::CreateBatchFromResolutionFolder(std::string file, cocos2d::SpriteBatchNode*& batch, cocos2d::SpriteFrameCache * cache, bool landscape)
{
	//Load batch and plist from correct resolution folder
	auto screenSize = nrgFunctions::GetScreenSize();
	float screenRatio = 0;

	if (screenSize.width > screenSize.height)
		landscape = true;
	else if (screenSize.height > screenSize.width)
		landscape = false;

	if (landscape)
		screenRatio = screenSize.width / screenSize.height;
	else if (!landscape)
		screenRatio = screenSize.height / screenSize.width;

	std::string filePrefix;

	if (screenRatio >= ar16x9)
		filePrefix.append("images/16x9/");
	else if (screenRatio >= ar3x2)
		filePrefix.append("images/3x2/");
	else if (screenRatio >= ar4x3)
		filePrefix.append("images/4x3/");

	if (screenSize.width >= 2560 || screenSize.height >= 2560)
		filePrefix.append("2560x1440/");
	else if (screenSize.width >= 2048 || screenSize.height >= 2048)
		filePrefix.append("2048x1536/");
	else if ((screenSize.width >= 1920 || screenSize.height >= 1920) && screenRatio >= ar16x9)
		filePrefix.append("1920x1080/");
	else if ((screenSize.width >= 1920 || screenSize.height >= 1920) && screenRatio >= ar3x2)
		filePrefix.append("1920x1280/");
	else if (screenSize.width >= 1440 || screenSize.height >= 1440)
		filePrefix.append("1440x960/");
	else if (screenSize.width >= 1136 || screenSize.height >= 1136)
		filePrefix.append("1280x720/");
	else if (screenSize.width >= 1024 || screenSize.height >= 1024)
		filePrefix.append("1024x768/");
	else if (screenSize.width >= 960 || screenSize.height >= 960)
		filePrefix.append("960x640/");
	else if (screenSize.width >= 480 || screenSize.height >= 480)
		filePrefix.append("480x320/");

	filePrefix.append(file);

	std::string plist = filePrefix;
	std::string png = filePrefix;

	plist.append(".plist");
	png.append(".png");

	cache->addSpriteFramesWithFile(plist);
	batch = cocos2d::SpriteBatchNode::create(png);

	return;
}

char * nrgFunctions::StringToUTF8(std::string sz)
{
	//Get new char array for UTF8 sequence
	char* utf8 = new char[sz.length()];

	//Loop through string and manually convert characters to UTF8 integers
	for (int iii = 0; iii < sz.length(); iii++)
		utf8[iii] = int(sz[iii]);
	return utf8;
}

