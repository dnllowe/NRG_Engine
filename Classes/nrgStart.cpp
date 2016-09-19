#pragma once
#include "nrgStart.h"

cocos2d::Scene* nrgStart::CreateScene()
{
	//Create scene
	cocos2d::Scene* scene = cocos2d::Scene::create();

	//Create Layer for scene and autorelease it
	cocos2d::Layer* layer = nrgStart::create();

	//Add layer to scene
	scene->addChild(layer);

	return scene;
}

void nrgStart::Init()
{
	SetInit(true);
}

bool nrgStart::init()
{
	//Pause any previously playing music
	nrgAudio::StopMusic();

	//Create sprite cache and load all game assets
	cache->addSpriteFramesWithFile("SpriteBatch.plist");
	cache->addSpriteFramesWithFile("StartupScene.plist");
	
	//Add start up scene images to batch
	batch = cocos2d::SpriteBatchNode::create("StartupScene.png");
	addChild(batch);

	//Initialize origin
	SCREEN_WIDTH = glview->getDesignResolutionSize().width;
	SCREEN_HEIGHT = glview->getDesignResolutionSize().height;
	center.x = SCREEN_WIDTH / 2;
	center.y = SCREEN_HEIGHT / 2;

	//Set clear color to white
	director->setClearColor(cocos2d::Color4F(1, 1, 1, 1));

	//Preload audio for scene
	audio->preloadEffect("Audio/nrgTheme.m4a");

	//Set Sprites for nrgLogo animation
	nrgLogo_1 = nrgSprite::create(batch, "nrgLogo_1.png");
	nrgLogo_2 = nrgSprite::create(batch, "nrgLogo_2.png");
	nrgLogo_3 = nrgSprite::create(batch, "nrgLogo_3.png");
	nrgLogo_4 = nrgSprite::create(batch, "nrgLogo_4.png");
	nrgLogo_5 = nrgSprite::create(batch, "nrgLogo_5.png");
	nrgLogo_6 = nrgSprite::create(batch, "nrgLogo_6.png");
	nrgLogo_7 = nrgSprite::create(batch, "nrgLogo_7.png");
	nrgLogo_8 = nrgSprite::create(batch, "nrgLogo_8.png");
	nrgLogo_9 = nrgSprite::create(batch, "nrgLogo_9.png");
	nrgLogo_10 = nrgSprite::create(batch, "nrgLogo_10.png");
	nrgLogo_11 = nrgSprite::create(batch, "nrgLogo_11.png");
	nrgLogo_12 = nrgSprite::create(batch, "nrgLogo_12.png");
	
	//Create vector of SpriteFrames for animation
	cocos2d::Vector<cocos2d::SpriteFrame*> nrgLogoAnimationFrames;
	nrgLogoAnimationFrames.pushBack(nrgLogo_1->getSpriteFrame());
	nrgLogoAnimationFrames.pushBack(nrgLogo_2->getSpriteFrame());
	nrgLogoAnimationFrames.pushBack(nrgLogo_3->getSpriteFrame());
	nrgLogoAnimationFrames.pushBack(nrgLogo_4->getSpriteFrame());
	nrgLogoAnimationFrames.pushBack(nrgLogo_5->getSpriteFrame());
	nrgLogoAnimationFrames.pushBack(nrgLogo_6->getSpriteFrame());

	nrgLogoAnimationFrames.pushBack(nrgLogo_6->getSpriteFrame());
	nrgLogoAnimationFrames.pushBack(nrgLogo_7->getSpriteFrame());
	nrgLogoAnimationFrames.pushBack(nrgLogo_8->getSpriteFrame());
	nrgLogoAnimationFrames.pushBack(nrgLogo_9->getSpriteFrame());
	nrgLogoAnimationFrames.pushBack(nrgLogo_10->getSpriteFrame());
	nrgLogoAnimationFrames.pushBack(nrgLogo_11->getSpriteFrame());
	nrgLogoAnimationFrames.pushBack(nrgLogo_12->getSpriteFrame());
	nrgLogoAnimationFrames.pushBack(nrgLogo_6->getSpriteFrame());

	//Create animation action
	cocos2d::Animation* nrgLogoAnimation = cocos2d::Animation::createWithSpriteFrames(nrgLogoAnimationFrames, 0.1);
	
	//Scale logo and cnter
	nrgLogo_1->setScale(0.125);
	nrgLogo_1->Center();
	
	//Add other animation frames to scene to prevent touch crashes, but set to invisible	
	nrgLogo_2->setVisible(false);
	nrgLogo_3->setVisible(false);
	nrgLogo_4->setVisible(false);
	nrgLogo_5->setVisible(false);
	nrgLogo_6->setVisible(false);
	nrgLogo_7->setVisible(false);
	nrgLogo_8->setVisible(false);
	nrgLogo_9->setVisible(false);
	nrgLogo_10->setVisible(false);
	nrgLogo_11->setVisible(false);
	nrgLogo_12->setVisible(false);
	
	
	//Create animation 
	cocos2d::Animate* animation = cocos2d::Animate::create(nrgLogoAnimation);
	
	//Create Sequence to animate then delay
	cocos2d::Sequence* sequence = cocos2d::Sequence::create(animation, NULL);
	
	//Play intro theme
	audio->playEffect("Audio/nrgTheme.m4a");

	//Add logo to scene
	nrgLogo_1->addEvents();

	//Run logo animation
	nrgLogo_1->runAction(sequence);
	
	//Once animation is over, wait 1 second, then load next level
	scheduleUpdate();
	
	timer.Start();

	return true;
}

void nrgStart::update(float fl)
{
	//USE AS TEMPLATE FOR OTHER GAME START SCENES.
	//REPLACE DIRECTOR SCENE WITH FIRSt LEVEL OR MENU OF GAME

	//Once animation is over, wait 4 second, then load next level
//	if (timer.GetElapsedTime() > 4000)//nrgLogo_1->getNumberOfRunningActions() == 0)
//		director->replaceScene(Training::CreateScene());
		return;
}

void nrgStart::onExit()
{
	cocos2d::Layer::onExit();
	return;
}

nrgStart::~nrgStart()
{
	//Remove theme from cache after done playing
	audio->unloadEffect("Audio/nrgTheme.wav");
	nrgLogoAnimationFrames.clear();
	removeAllChildren();
	cache->removeUnusedSpriteFrames();
}
