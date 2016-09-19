#pragma once
#include "nrgDbutton.h"
class nrgSquareButton : public nrgDbutton
{
public:

	static nrgSquareButton* create(cocos2d::SpriteBatchNode* batch);
	
	~nrgSquareButton();

protected:
	nrgSquareButton();
};

