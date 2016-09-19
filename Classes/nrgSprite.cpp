#pragma once
#include "nrgSprite.h"

nrgSprite::nrgSprite() {}

nrgSprite* nrgSprite::create(cocos2d::SpriteBatchNode* batch, std::string frameFile, bool alias)
{
	//Create pointer for to initialize sprite/nrgSprite
	nrgSprite* sprite = new nrgSprite();
	
	//Create sprite frame from cache image name (frameFile) if valid
	if (sprite->initWithSpriteFrameName(frameFile))
	{
		//Set to autorelease for safe memory management
		sprite->autorelease();

		//Add frame as child of batch for batch processing
		batch->addChild(sprite);

		//Turn alias on or off (antialiasing)
		if (alias)
			sprite->getTexture()->setAliasTexParameters();
		else
			sprite->getTexture()->setAntiAliasTexParameters();

		//Set anchor to bottom left
		sprite->setAnchorPoint(cocos2d::Vec2(0, 0));

		return sprite;
	}

	//If sprite didn't load properly
	CC_SAFE_DELETE(sprite);
	return NULL;
}

nrgSprite* nrgSprite::create(std::string frameFile, bool alias)
{
	//Create pointer for to initialize sprite/nrgSprite
	nrgSprite* sprite = new nrgSprite();

	//Create temporary sprite to get sprite frame
	cocos2d::Sprite* tempSprite = cocos2d::Sprite::create();
    tempSprite->initWithFile(frameFile);

	//Create sprite frame from cache image if valid
	if (sprite->initWithSpriteFrame(tempSprite->getSpriteFrame()))
	{
		//Set to autorelease for safe memory management
		sprite->autorelease();

		//Turn alias on or off (antialiasing)
		if (alias)
			sprite->getTexture()->setAliasTexParameters();
		else
			sprite->getTexture()->setAntiAliasTexParameters();

		//Center on screen
		sprite->Center();

		//Set anchor to bottom left
		sprite->setAnchorPoint(cocos2d::Vec2(0, 0));

		return sprite;
	}

	//If sprite didn't load properly
	CC_SAFE_DELETE(sprite);
	return NULL;
}

std::string nrgSprite::GetDefaultFrame()
{
	return defaultFrame;
}

void nrgSprite::SetCurrentAnimation(cocos2d::Animation * animation)
{
	currentAnimation = animation;
	return;
}
	
void nrgSprite::addEvents()
{
	//Set flag for events added
	eventsAdded = true;
	touchEnabled = true;

	//Create listener for touch events
    touchListener = cocos2d::EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);

	//Create lister for keyboard events
	keyboardListener = cocos2d::EventListenerKeyboard::create();
	keyboardListener->setEnabled(false);

	//On touch, check to see if sprite was touched
	touchListener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		touchLocation = touch->getLocation();
		cocos2d::Rect rect = getBoundingBox();

		if (partOfScrollView)
		{
			touchLocation.y += scrollView->getInnerContainerPosition().y;
			touchLocation.x += scrollView->getInnerContainerPosition().x;
		}

		if (rect.containsPoint(touchLocation))
		{
			TouchBegan();
			return true; // to indicate that we have consumed it.
		}

		return false; // we did not consume this event, pass thru.
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


void nrgSprite::touchEvent(cocos2d::Touch* touch, cocos2d::Vec2 _point)
{
	CCLOG("touched MySprite");
}

void nrgSprite::TouchBegan()
{
	wasTouched = true;
	return;
}

void nrgSprite::TouchMove(cocos2d::Touch* touch)
{
	/*
	cocos2d::Vec2 startLocation = touch->getStartLocation();
	cocos2d::Vec2 endLocation = touch->getLocation();

	setPosition(endLocation);
	*/
	return;
}

void nrgSprite::TouchEnd()
{
	return;
}

void nrgSprite::TouchHold(float time)
{
	return;
}

void nrgSprite::ToggleKeyboard(bool value)
{
	if(keyboardListener != NULL)
		keyboardListener->setEnabled(value);
	return;
}

void nrgSprite::ToggleTouch(bool value)
{
	if(touchListener != NULL)
    {
		touchListener->setEnabled(value);
        touchEnabled = value;
    }
	return;
}

void nrgSprite::ToggleEnabled(bool value)
{
	touchEnabled = value;
	setVisible(value);
	if (touchListener != NULL)
		ToggleTouch(value);
	if (keyboardListener != NULL)
		ToggleKeyboard(value);

	return;
}

bool nrgSprite::WasTouched(bool resetTouch)
{
	if (wasTouched && resetTouch)
	{
		wasTouched = false;
		return true;
	}

	return wasTouched;
}

bool nrgSprite::IsTouchEnabled()
{
	return touchEnabled;
}

cocos2d::Vec2 nrgSprite::GetLastTouchLocation()
{
	return touchLocation;
}

void nrgSprite::HandleKeyPress(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	return;
}

void nrgSprite::HandleKeyRelease(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	return;
}

void nrgSprite::ChangeKeyboardListenerPriority(int value)
{
	if (keyboardListener != NULL)
		cocos2d::Director::getInstance()->getEventDispatcher()->setPriority(keyboardListener, value);
	return;
}

void nrgSprite::ChangeTouchListenerPriority(int value)
{
	if (touchListener != NULL)
		cocos2d::Director::getInstance()->getEventDispatcher()->setPriority(touchListener, value);
	return;
}

void nrgSprite::Animate(bool repeatForever)
{
	//First stop any current animatons/actions
	stopAllActions();

	if (repeatForever)
		runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(currentAnimation)));
	else
		runAction(cocos2d::Animate::create(currentAnimation));

	return;
}

void nrgSprite::InitPhysics()
{
	float width = getContentSize().width;
	float height = getContentSize().height;
	auto physicsBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(getScaleX() * width, getScaleY() * height));
	this->setPhysicsBody(physicsBody);
	physicsAdded = true;

	return;
}

void nrgSprite::SetPhysicsMaterial(float density, float friction, float restitution)
{
	//Can only set if physics is enabled
	if (!physicsAdded)
		return;

	//Low friction, high bounce material
	cocos2d::PhysicsMaterial material;
	material.density = density;
	material.friction = friction;
	material.restitution = restitution;

	int tag = getPhysicsBody()->getTag();
	getPhysicsBody()->getShape(tag)->setMaterial(material);
	
	return;
}

void nrgSprite::SetPhysicsVelocity(float velocityX, float velocityY)
{
	getPhysicsBody()->setVelocity(cocos2d::Vect(velocityX, velocityY));
	return;
}

void nrgSprite::SetRightSide(int x)
{
	setPositionX((x - getScaleX() * getContentSize().width) + getAnchorPoint().x * getScaleX() * getContentSize().width);
	return;
}

int nrgSprite::GetRightSide()
{
	return (getPositionX() + getScaleX() * getContentSize().width) - getAnchorPoint().x * getScaleX() * getContentSize().width;
}

void nrgSprite::SetTop(int y)
{
	setPositionY((y - getScaleY() * getContentSize().height) + getAnchorPoint().y * getScaleY() * getContentSize().height);
	return;
}

int nrgSprite::GetTop()
{
	return (getPositionY() + getScaleY() * getContentSize().height) - getAnchorPoint().y * getScaleY() * getContentSize().height;
}

void nrgSprite::Center(int offsetX, int offsetY)
{
	//Get screen width and height
	auto director = cocos2d::Director::getInstance();
	int width = director->getOpenGLView()->getDesignResolutionSize().width;
	int height = director->getOpenGLView()->getDesignResolutionSize().height;
	float scaleX = getScaleX();
	float scaleY = getScaleY();

	//Center the image
	setPosition(width / 2 - scaleX * getContentSize().width / 2 + offsetX, height / 2 - scaleY * getContentSize().height / 2 + offsetY);

	return;
}

int nrgSprite::GetWidth()
{
	return getScaleX() * getContentSize().width;
}

int nrgSprite::GetHeight()
{
	return getScaleY() * getContentSize().height;
}

void nrgSprite::SetCenter(int x, int y)
{
	setPosition(x - GetWidth() / 2, y - GetHeight() / 2);
	return;
}

void nrgSprite::SetCenterX(int x)
{
	setPositionX(x - GetWidth() / 2);
	return;
}

void nrgSprite::SetCenterY(int y)
{
	setPositionY(y - GetHeight() / 2);
	return;
}

int nrgSprite::GetCenterX(int x)
{ 
	return getPositionX() + GetWidth() / 2;	
}

int nrgSprite::GetCenterY(int y)
{
	return getPositionX() + GetHeight() / 2;
}

void nrgSprite::Move(float xValue, float yValue)
{
	setPosition(getPositionX() + xValue, getPositionY() + yValue);
	return;
}

void nrgSprite::FadeIn(float value)
{
	isFading = true;
	cocos2d::FadeIn* fade = cocos2d::FadeIn::create(value);
	cocos2d::CallFunc* opacityFull = cocos2d::CallFunc::create([this]() {setOpacity(255); isFading = false;});
	cocos2d::Sequence* fadeSequence = cocos2d::Sequence::create(fade, opacityFull, NULL);
	runAction(fadeSequence);
	return;
}

void nrgSprite::FadeOut(float value)
{
	isFading = true;
	cocos2d::FadeOut* fade = cocos2d::FadeOut::create(value);
	cocos2d::CallFunc* opacityZero = cocos2d::CallFunc::create([this]() {setOpacity(0); setVisible(false); isFading = false;});
	cocos2d::Sequence* fadeSequence = cocos2d::Sequence::create(fade, opacityZero, NULL);
	runAction(fadeSequence);
	return;
}

bool nrgSprite::IsFading()
{
	return isFading;
}

void nrgSprite::setOpacity(float value)
{
	cocos2d::Node::setOpacity(value);
	return;
}

GLubyte nrgSprite::getOpacity()
{
	return cocos2d::Node::getOpacity();
}

void nrgSprite::AddToScrollView(cocos2d::ui::ScrollView * scrollViewInput)
{
	scrollView = scrollViewInput;

	//Make sure object isn't already a child of another object
	if (getParent() == NULL)
		scrollView->addChild(this);

	//Set to true so touch events track touch correctly based  on container offset
	partOfScrollView = true;
	
	return;
}

void nrgSprite::onExit()
{
	cocos2d::Node::onExit();
	return;
}

nrgSprite::~nrgSprite() 
{
	if (touchListener != NULL)
		cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(touchListener);
	if (keyboardListener != NULL)
		cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(keyboardListener);

	touchListener = NULL;
	keyboardListener = NULL;
}

