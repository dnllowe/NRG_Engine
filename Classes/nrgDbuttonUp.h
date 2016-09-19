#pragma once
#include "pch.h"
#include "nrgDbutton.h"

class nrgDbuttonUp : public nrgDbutton
{
public:
	static nrgDbuttonUp* create(cocos2d::SpriteBatchNode* batch);
	~nrgDbuttonUp();

protected:
	nrgDbuttonUp();
};

