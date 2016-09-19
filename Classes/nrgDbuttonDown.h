#pragma once
#include "pch.h"
#include "nrgDbutton.h"

class nrgDbuttonDown : public nrgDbutton
{
public:

	//Create the DbuttonDown button graphics
	static nrgDbuttonDown* create(cocos2d::SpriteBatchNode* batch);

	~nrgDbuttonDown();

protected:
	nrgDbuttonDown();
};

