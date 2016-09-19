#ifndef  _NRG_FUNCTIONS_H_
#define  _NRG_FUNCTIONS_H_

#pragma once
#include "pch.h"

//Forward declarations
class nrgScene;
class nrgSprite;
class nrgText;

//Defines hash for unordered set of pairs
struct pair_hash 
{
	size_t operator()(const std::pair<int, int>& p)
		const
	{
		return p.first ^ p.second;
	}
};

class nrgFunctions
{
public:

	/* Load files from specific resolution folders.
	Run in AppDelegate applicationDidFinishLaunching
	File folders for project must be in "Resources" under "iphone, iphonehd, iphonehd5, ipad, ipadhd" 
	*/

	static void MultiResolutionSupport(ResolutionPolicy);

	//Create Sprite batch and cache from file
	static void CreateSpriteBatch(std::string fileName, cocos2d::SpriteBatchNode*& batch, cocos2d::SpriteFrameCache*& cache);

	//Resizes an image(background) for appropriate device aspect ratio
	static void ResizeForDevice(cocos2d::Sprite* sprite, float additionalScaling = 1.0);

	//Resize nrgSprite for appropriate device aspect ratio
	static void ResizeForDevice(nrgSprite* sprite, float additionalScaling = 1.0);

	//Resize entire sprite batch for appropriate device aspect ratio
	static void ResizeForDevice(cocos2d::SpriteBatchNode* batch, float additionalScaling = 1.0);

	//Create horizontal letterbox bars
	static void AddHorizontalLetterbox(nrgScene* scene, float percentage);

	//Create vertical letterbox bars
	static void AddVerticalLetterbox(nrgScene* scene, float percentage);

	//Return random number between min and max (including min and max), or random number if no range specified
	static int GetRandom(int min = 0, int max = 0);

    //Return random number between min and max (including min and max), excluding specific number
    static int GetRandom(int min, int max, int excludedNumber);
    
	//Return random number between min and max (including min and max), or random number if no range specified, excluding specific numbers
	static int GetRandom(int min, int max, std::unordered_set<int> excludedNumbers);

	//Return random pair between min and max (including min and max), or random number if no range specified
	static std::pair<int, int> GetRandomPair(int xMin, int xMax, int yMin, int yMax);

	//Return random pair between min and max (including min and max), or random number if no range specified, excluding pairs of specific numbers
	static std::pair<int, int> GetRandomPair(int xMin, int xMax, int yMin, int yMax, std::unordered_set<std::pair<int, int>, pair_hash> excludedNumbers);

	//Randomly choose between two numbers
	static int GetRandomChoice(int n1, int n2);

	//Center Node/Sprite onto screen
	static void Center(cocos2d::Node* node);
	
	//Center sprite 1 onto sprite 2
	static void Center(nrgSprite* sprite1, nrgSprite* sprite2, int offsetX = 0, int offsetY = 0);

	//Center text onto sprite sprite
	static void Center(nrgText* text, nrgSprite* sprite, int offsetX = 0, int offsetY = 0);

	static float GetRatio();

	static float GetZoomRatio();

	static cocos2d::Size GetScreenSize();

	static float GetAssetSize();

	//Depcrecated. Use MultiResolutionSupport instead
	static void CreateBatchFromResolutionFolder(std::string file, cocos2d::SpriteBatchNode*& batch, cocos2d::SpriteFrameCache* cache, bool landscape = true);

	static char* StringToUTF8(std::string sz);
	
protected:

	static float ratio; //Aspect ratio of device
	static float zoomRatio; //Zoom ratio between designResolutionSize and device Frame Size
	static float assetSize; //Which assets were loaded (from which resolution folder)
	static float ar16x9;
	static float ar5x3;
	static float ar16x10;
	static float ar3x2;
	static float ar4x3;
	static float ar1x1;
	static bool landscape;
};

#endif