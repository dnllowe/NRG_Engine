#pragma once
#include "pch.h"
#include "nrgDbutton.h"

//Forward declaration for nrgDbutton
class nrgDbutton;

class nrgDbuttonTouchRegion : public nrgDbutton
{
public:
	
	//Create nrgDbutton from scene batch
	static nrgDbuttonTouchRegion* create(cocos2d::SpriteBatchNode* batch, nrgDbutton* link);

	//Create and link touch events to another dButton
	void addEvents();

	~nrgDbuttonTouchRegion();

protected:
	nrgDbutton* linkedButton = NULL;
	nrgDbuttonTouchRegion(nrgDbutton* link);
};

