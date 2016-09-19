#include "pch.h"
#include "nrgDbuttonUp.h"


nrgDbuttonUp::nrgDbuttonUp()
{
	idleButton->initWithSpriteFrameName("dButtonUp.png");
	pressedButton->initWithSpriteFrameName("dButtonUpPressed.png");
	pressedButton->retain();
	idleButton->retain();
}


nrgDbuttonUp* nrgDbuttonUp::create(cocos2d::SpriteBatchNode * batch)
{
	nrgDbuttonUp* sprite = new nrgDbuttonUp;

	if (sprite->initWithSpriteFrameName("dButtonUp.png"))
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

nrgDbuttonUp::~nrgDbuttonUp()
{
}
