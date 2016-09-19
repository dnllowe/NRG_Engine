#pragma once
#include "nrgScene.h"

std::vector<nrgTimer*> nrgScene::timers;
cocos2d::UserDefault* nrgScene::gameData = NULL;

cocos2d::Scene* nrgScene::CreateScene()
{
	//Create Scene
	cocos2d::Scene* scene = cocos2d::Scene::create();

	//Create layer
	cocos2d::Layer* layer = nrgScene::create();

	scene->addChild(layer);

	return scene;
}

void nrgScene::Init()
{
	//VIRTUAL FUNCTION. INCLUDE ANY SCENE/LEVEL SPECIFIC VARIABLE INITIALIZATIONS HERE

	SetInit(false);

	return;
}

bool nrgScene::init()
{
	//EVERY SCENE SHOULD START BY GETTING AN INSTANCE OF SPRITEFRAMECACHE AND BATCH
    if(!gameData)
        gameData = cocos2d::UserDefault::getInstance();

	//Initialize origin
	SCREEN_WIDTH = glview->getDesignResolutionSize().width;
	SCREEN_HEIGHT = glview->getDesignResolutionSize().height;
	center.x = SCREEN_WIDTH / 2;
	center.y = SCREEN_HEIGHT / 2;

	

	//VIRTUAL FUNCTION. WHEN DERIVING SCENE/LEVEL, INSERT GAME LOOP CODE HERE
	return true;
}

void nrgScene::SetBG(std::string file)
{
	//Load bg image
	bg->initWithFile(file);

	//Resize for device
	nrgFunctions::ResizeForDevice(bg);

	//Always center bg image
	bg->setPosition(center);

	this->addChild(bg);

	return;
}

bool nrgScene::Paused()
{
	return paused;
}

void nrgScene::Pause()
{
	paused = true;
	return;
}

void nrgScene::Unpause()
{
	paused = false;
	return;
}

cocos2d::Vec2 nrgScene::GetCenter()
{
	return center;
}

bool nrgScene::IsInit()
{
	return initialized;
}

void nrgScene::SetInit(bool value)
{ 
	initialized = value;
	return;
}

void nrgScene::addEvents()
{
	//Set flag for events added
	eventsAdded = true;
    touchEnabled = true;
    
	//Create listener for touch events
	touchListener = cocos2d::EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);

	//Create lister for keyboard events
	keyboardListener = cocos2d::EventListenerKeyboard::create();
	keyboardListener->setEnabled(true);

	//On touch, check to see if sprite was touched
	touchListener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		touchLocation = touch->getLocation();
        TouchBegan();
        return true; // to indicate that we have consumed it.
	};

	//Code for what to do when touch is swiped across screen
	touchListener->onTouchMoved = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		TouchMove(touch);
		touchEvent(touch, touch->getLocation());
	};
	//Code for what to do when touch is released
	touchListener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		TouchEnd();
		touchEvent(touch, touch->getLocation());
	};

	//Key press event handling
	keyboardListener->onKeyPressed = [=](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		HandleKeyPress(keyCode, event);
	};

	//Key release event handling
	keyboardListener->onKeyReleased = [=](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		HandleKeyRelease(keyCode, event);
	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(touchListener, 1);
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(keyboardListener, 1);
}

void nrgScene::InitPhysics()
{
	float width = getContentSize().width;
	float height = getContentSize().height;
	auto physicsBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(getScaleX() * width, getScaleY() * height));
	this->setPhysicsBody(physicsBody);
	physicsAdded = true;

	return;
}

void nrgScene::SetPhysicsVelcoity(float velocityX, float velocityY)
{
		getPhysicsBody()->setVelocity(cocos2d::Vect(velocityX, velocityY));
		return;
}

void nrgScene::touchEvent(cocos2d::Touch * touch, cocos2d::Vec2 _p)
{
	return;
}

void nrgScene::TouchBegan()
{
    wasTouched = true;
	return;
}

void nrgScene::TouchEnd()
{
	return;
}

void nrgScene::TouchHold(float time)
{
	return;
}

void nrgScene::TouchMove(cocos2d::Touch * touch)
{
	return;
}

void nrgScene::ToggleKeyboard(bool value)
{
	keyboardListener->setEnabled(value);
	return;
}

void nrgScene::ToggleTouch(bool value)
{
    if(touchListener != NULL)
    {
        touchEnabled = value;
        touchListener->setEnabled(value);
    }
	return;
}



bool nrgScene::WasTouched(bool resetTouch)
{
    if (wasTouched && resetTouch)
    {
        wasTouched = false;
        return true;
    }
    
    return wasTouched;
}

bool nrgScene::IsTouchEnabled()
{
    return touchEnabled;
}

cocos2d::Vec2 nrgScene::GetLastTouchLocation()
{
    return lastTouchLocation;
}

void nrgScene::SetLastTouchLocation(cocos2d::Vec2 vec)
{
	lastTouchLocation = vec;
	return;
}

void nrgScene::HandleKeyPress(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	return;
}

void nrgScene::HandleKeyRelease(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	return;
}

void nrgScene::ChangeKeyboardListenerPriority(int value)
{
    if (keyboardListener != NULL)
        cocos2d::Director::getInstance()->getEventDispatcher()->setPriority(keyboardListener, value);
    return;
}

void nrgScene::ChangeTouchListenerPriority(int value)
{
    if (touchListener != NULL)
        cocos2d::Director::getInstance()->getEventDispatcher()->setPriority(touchListener, value);
    return;
}

void nrgScene::onExit()
{
	cocos2d::Layer::onExit();
	return;
}

nrgScene::~nrgScene()
{
	if (touchListener != NULL)
		cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(touchListener);
	if (keyboardListener != NULL)
		cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(keyboardListener);

	touchListener = NULL;
	keyboardListener = NULL;
}
