#pragma once
#include "pch.h"
#include "nrgDbutton.h"

class nrgDbuttonLeft : public nrgDbutton
{
public:

	//Create the DbuttonDown button graphics
	static nrgDbuttonLeft* create(cocos2d::SpriteBatchNode* batch);

	~nrgDbuttonLeft();

protected:
	nrgDbuttonLeft();
	
};

