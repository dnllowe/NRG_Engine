#pragma once
#include "pch.h"

//Forward declaration for nrgSprite and nrgText
class nrgSprite;
class nrgText;
class nrgTimer;

class nrgStart : public nrgScene
{
public:

	//Creates scene and initializes necessary variables using Init()
	static cocos2d::Scene* CreateScene();

	//Initializes members for scene (runs from CreateScene on instance)
	void Init();

	//Function that runs game loop using CREATE_FUNC from Cocos2dx
	virtual bool init();

	//Override update loop
	void update(float fl);

	void onExit();

	~nrgStart();

	CREATE_FUNC(nrgStart);

protected:

	//Loading text
	nrgText* loading = NULL;

	cocos2d::SpriteBatchNode* batch = NULL;
	cocos2d::SpriteFrameCache* cache = cocos2d::SpriteFrameCache::getInstance();

	//Audio controller 
	CocosDenshion::SimpleAudioEngine* audio = CocosDenshion::SimpleAudioEngine::getInstance();
	
	//Logo for NRG
	nrgSprite* nrgLogo_1 = NULL; //Frame one of logo intro animation

	
	nrgSprite* nrgLogo_2 = NULL; //Frame two of logo intro animation
	nrgSprite* nrgLogo_3 = NULL; //Frame three of logo intro animation
	nrgSprite* nrgLogo_4 = NULL; //Frame four of logo intro animation
	nrgSprite* nrgLogo_5 = NULL; //Frame five of logo intro animation
	nrgSprite* nrgLogo_6 = NULL; //Frame six of logo intro animation

	nrgSprite* nrgLogo_7 = NULL; //Frame one of logo intro animation
	nrgSprite* nrgLogo_8 = NULL; //Frame two of logo intro animation
	nrgSprite* nrgLogo_9 = NULL; //Frame three of logo intro animation
	nrgSprite* nrgLogo_10 = NULL; //Frame four of logo intro animation
	nrgSprite* nrgLogo_11 = NULL; //Frame five of logo intro animation
	nrgSprite* nrgLogo_12 = NULL; //Frame six of logo intro animation
	
	cocos2d::Vector<cocos2d::SpriteFrame*> nrgLogoAnimationFrames{ NULL };
	
	nrgTimer timer; //General timer for scene
};
