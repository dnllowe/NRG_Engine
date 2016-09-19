#include "pch.h"
#include "nrgDbuttonRight.h"


nrgDbuttonRight::nrgDbuttonRight()
{
	idleButton->initWithSpriteFrameName("dButtonRight.png");
	pressedButton->initWithSpriteFrameName("dButtonRightPressed.png");
	pressedButton->retain();
	idleButton->retain();
}


nrgDbuttonRight * nrgDbuttonRight::create(cocos2d::SpriteBatchNode * batch)
{
	nrgDbuttonRight* sprite = new nrgDbuttonRight;

	if (sprite->initWithSpriteFrameName("dButtonRight.png"))
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

nrgDbuttonRight::~nrgDbuttonRight()
{
}
