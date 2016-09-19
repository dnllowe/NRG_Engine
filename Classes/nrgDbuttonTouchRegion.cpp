#include "pch.h"
#include "nrgDbuttonTouchRegion.h"


nrgDbuttonTouchRegion::nrgDbuttonTouchRegion(nrgDbutton* link)
{
	pressedButton->initWithSpriteFrameName("dButtonTouchRegion.png");
	idleButton->initWithSpriteFrameName("dButtonTouchRegion.png");
	pressedButton->retain();
	idleButton->retain();
	linkedButton = link;
	addEvents();
}


nrgDbuttonTouchRegion * nrgDbuttonTouchRegion::create(cocos2d::SpriteBatchNode * batch, nrgDbutton* link)
{
	nrgDbuttonTouchRegion* sprite = new nrgDbuttonTouchRegion(link);

	if (sprite->initWithSpriteFrameName("dButtonTouchRegion.png"))
	{
		//Set to autorelease for safe memory management
		sprite->autorelease();

		//Add frame as child of batch for batch processing
		batch->addChild(sprite);

		//Turn alias off 
		sprite->getTexture()->setAliasTexParameters();

		//Set anchor to bottom left
		sprite->setAnchorPoint(cocos2d::Vec2(0, 0));

		return sprite;
	}

	//If sprite didn't load properly
	CC_SAFE_DELETE(sprite);
	return NULL;
}

void nrgDbuttonTouchRegion::addEvents()
{
	//Set flag for events added
	eventsAdded = true;

	//Create listener for touch events
	touchListener = cocos2d::EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);

	//Create lister for keyboard events
	keyboardListener = cocos2d::EventListenerKeyboard::create();
	keyboardListener->setEnabled(false);

	//On touch, check to see if sprite was touched
	touchListener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		cocos2d::Vec2 touchLocation = touch->getLocation();
		cocos2d::Rect rect = getBoundingBox();

		if (rect.containsPoint(touchLocation))
		{
			linkedButton->TouchBegan();
			return true; // to indicate that we have consumed it.
		}

		return false; // we did not consume this event, pass thru.
	};

	//Code for what to do when touch is released
	touchListener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		linkedButton->TouchEnd();
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

nrgDbuttonTouchRegion::~nrgDbuttonTouchRegion()
{
}
