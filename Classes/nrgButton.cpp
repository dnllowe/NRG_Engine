#include "pch.h"
#include "nrgButton.h"


nrgButton::nrgButton(std::string defaultFile, std::string selectedFile, bool alias)
{
	//Create temporary sprite to get sprite frame
	cocos2d::Sprite* defaultSprite = cocos2d::Sprite::create();
	cocos2d::Sprite*selectedSprite = cocos2d::Sprite::create();

	defaultSprite->initWithFile(defaultFile);
	selectedSprite->initWithFile(selectedFile);

	//Create temporary sprite to get sprite frame
	defaultImage->initWithSpriteFrame(defaultSprite->getSpriteFrame());
	selectedImage->initWithSpriteFrame(selectedSprite->getSpriteFrame());

	//Turn alias on or off (antialiasing)
	if (alias)
	{
		defaultImage->getTexture()->setAliasTexParameters();
		selectedImage->getTexture()->setAliasTexParameters();
	}
	else
	{
		defaultImage->getTexture()->setAntiAliasTexParameters();
		selectedImage->getTexture()->setAntiAliasTexParameters();
	}

	initWithSpriteFrame(defaultImage->getSpriteFrame());

	defaultImage->retain();
	selectedImage->retain();
}

nrgButton::nrgButton(cocos2d::SpriteBatchNode * batch, std::string defaultFile, std::string selectedFile, bool alias)
{
	defaultImage->initWithSpriteFrameName(defaultFile);
	selectedImage->initWithSpriteFrameName(selectedFile);
	initWithSpriteFrameName(defaultFile);

	defaultImage->retain();
	selectedImage->retain();

	//Turn alias on or off (antialiasing)
	if (alias)
	{
		defaultImage->getTexture()->setAliasTexParameters();
		selectedImage->getTexture()->setAliasTexParameters();
		getTexture()->setAliasTexParameters();
	}
	else
	{
		defaultImage->getTexture()->setAntiAliasTexParameters();
		selectedImage->getTexture()->setAntiAliasTexParameters();
		getTexture()->setAntiAliasTexParameters();
	}

	return;
}


nrgButton* nrgButton::create(std::string defaultFile, std::string selectedFile, bool alias)
{
	//Create pointer for to initialize sprite/nrgSprite
	nrgButton* sprite = new nrgButton(defaultFile, selectedFile);

	//Set to autorelease for safe memory management
	sprite->autorelease();

	//Turn alias on or off (antialiasing)
	if (alias)
		sprite->getTexture()->setAliasTexParameters();
	else
		sprite->getTexture()->setAntiAliasTexParameters();

	//Set anchor to bottom left
	sprite->setAnchorPoint(cocos2d::Vec2(0, 0));

	return sprite;
}

nrgButton * nrgButton::create(cocos2d::SpriteBatchNode * batch, std::string defaultFile, std::string selectedFile, bool alias)
{
	//Create pointer for to initialize sprite/nrgSprite
	nrgButton* sprite = new nrgButton(batch, defaultFile, selectedFile);

	//Set to autorelease for safe memory management
	sprite->autorelease();

	//Turn alias on or off (antialiasing)
	if (alias)
		sprite->getTexture()->setAliasTexParameters();
	else
		sprite->getTexture()->setAntiAliasTexParameters();

	batch->addChild(sprite);

	//Set anchor to bottom left
	sprite->setAnchorPoint(cocos2d::Vec2(0, 0));

	return sprite;
}

void nrgButton::addEvents()
{
	//Set flag for events added
	eventsAdded = true;
	
	//Create listener for touch events
	touchListener = cocos2d::EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);

	//On touch, check to see if sprite was touched
	touchListener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		//Record touch location
		cocos2d::Vec2 touchLocation = touch->getLocation();
		cocos2d::Rect rect = getBoundingBox();

		if (partOfScrollView)
		{
			touchLocation.y -= scrollView->getInnerContainerPosition().y;
			touchLocation.x -= scrollView->getInnerContainerPosition().x;
		}

		if (rect.containsPoint(touchLocation))
		{
			setSpriteFrame(selectedImage->getSpriteFrame());
			if (linkedText)
				linkedText->ChangeColor(textPressColor);

			return true;
		}

		return false;
	};
		

	// Code for what to do when touch is released
	touchListener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		cocos2d::Vec2 touchReleaseLocation = touch->getLocation();
		cocos2d::Rect rect = getBoundingBox();
		cocos2d::Vec2 touchStartLocation = touch->getStartLocation();

		if (partOfScrollView)
		{
			touchStartLocation.y -= scrollView->getInnerContainerPosition().y;
			touchStartLocation.x -= scrollView->getInnerContainerPosition().x;
			touchReleaseLocation.y -= scrollView->getInnerContainerPosition().y;
			touchReleaseLocation.x -= scrollView->getInnerContainerPosition().x;
		}

		if (rect.containsPoint(touchReleaseLocation) && rect.containsPoint(touchStartLocation))
			pressed = true;

		setSpriteFrame(defaultImage->getSpriteFrame());
		if (linkedText)
			linkedText->ChangeColor(textDefaultColor);

	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(touchListener, 1);
	return;
}

void nrgButton::LinkWithText(nrgText*& text, cocos2d::Color3B pressColorInput)
{
	linkedText = text;
	textDefaultColor = text->GetTextColor();
	textPressColor = pressColorInput;
	nrgFunctions::Center(text, this);
	return;
}

void nrgButton::setPosition(float x, float y)
{
	cocos2d::Sprite::setPosition(x, y);
	if (linkedText)
		nrgFunctions::Center(linkedText, this);
	return;
}

void nrgButton::setPositionX(float x)
{
	cocos2d::Sprite::setPositionX(x);
	if (linkedText)
		nrgFunctions::Center(linkedText, this);
	return;
}

void nrgButton::setPositionY(float y)
{
	cocos2d::Sprite::setPositionY(y);
	if (linkedText)
		nrgFunctions::Center(linkedText, this);
	return;
}

void nrgButton::SetRightSide(int x)
{
	nrgSprite::SetRightSide(x);
	if (linkedText)
		nrgFunctions::Center(linkedText, this);
	return;
}

void nrgButton::SetTop(int y)
{
	nrgSprite::SetTop(y);
	if (linkedText)
		nrgFunctions::Center(linkedText, this);
	return;
}

void nrgButton::Center(int offsetX, int offsetY)
{
	nrgSprite::Center(offsetX, offsetY);
	if (linkedText)
		nrgFunctions::Center(linkedText, this);
	return;
}

void nrgButton::SetCenter(int x, int y)
{
	nrgSprite::SetCenter(x, y);
	if (linkedText)
		nrgFunctions::Center(linkedText, this);
	return;
}

void nrgButton::SetCenterX(int x)
{
	nrgSprite::SetCenterX(x);
	if (linkedText)
		nrgFunctions::Center(linkedText, this);
	return;
}

void nrgButton::SetCenterY(int y)
{
	nrgSprite::SetCenterY(y);
	if (linkedText)
		nrgFunctions::Center(linkedText, this);
	return;
}

void nrgButton::Move(float xValue, float yValue)
{
	nrgSprite::Move(xValue, yValue);
	if (linkedText)
		nrgFunctions::Center(linkedText, this);
	return;
}


bool nrgButton::WasPressed(bool savePress)
{
	if (pressed)
	{
		pressed = savePress;
		return true;
	}

	else
		return false;
}

void nrgButton::onExit()
{
	nrgSprite::onExit();
	return;
}


nrgButton::~nrgButton()
{
	defaultImage->release();
	selectedImage->release();

	defaultImage = NULL;
	selectedImage = NULL;
}
