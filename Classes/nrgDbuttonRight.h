#pragma once
#include "pch.h"
#include "nrgDbutton.h"

class nrgDbuttonRight : public nrgDbutton
{
public:

	static nrgDbuttonRight* create(cocos2d::SpriteBatchNode* batch);
	~nrgDbuttonRight();

protected:
	nrgDbuttonRight();
};

