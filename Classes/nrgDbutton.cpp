#pragma once
#include "nrgDbutton.h"


nrgDbutton::nrgDbutton(bool singleButton)
{
	//Only create and retain sprites if this button is a single button (and not part of a dpad)
	if (singleButton)
	{
		pressedButton->initWithSpriteFrameName("dButtonPressed.png");
		idleButton->initWithSpriteFrameName("dButton.png");

		pressedButton->retain();
		idleButton->retain();
	}
}

nrgDbutton* nrgDbutton::create(cocos2d::SpriteBatchNode* batch, bool singleButton)
{
	//Create pointer for to initialize sprite/nrgSprite
	nrgDbutton* sprite = new nrgDbutton(singleButton);

	//Create sprite frame from cache image name (frameFile) if valid
	if (sprite->initWithSpriteFrameName("dButton.png"))
	{
		//Set to autorelease for safe memory management
		sprite->autorelease();

		//Add frame as child of batch for batch processing
		batch->addChild(sprite);

		//Add keyboard and touch functionality
		sprite->addEvents();

		//Turn on keyboard input
		sprite->ToggleKeyboard(false);

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

void nrgDbutton::TouchBegan()
{
	buttonPressed = true;
	setSpriteFrame(pressedButton->getSpriteFrame());
}

void nrgDbutton::TouchEnd()
{
	setSpriteFrame(idleButton->getSpriteFrame());
	return;
}

bool nrgDbutton::IsPressed()
{
	return buttonPressed;
}

void nrgDbutton::ClearInput()
{
	buttonPressed = false;
	return;
}

void nrgDbutton::onExit()
{
	nrgSprite::onExit();
	return;
}

nrgDbutton::~nrgDbutton()
{
	idleButton->release();
	pressedButton->release();

	idleButton = NULL;
	pressedButton = NULL;
}
