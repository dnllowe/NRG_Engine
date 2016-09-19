#pragma once
#include "nrgSprite.h"
#include "pch.h"

class nrgDbutton : public nrgSprite
{
public:
	//Create nrgDbutton from scene batch
	static nrgDbutton* create(cocos2d::SpriteBatchNode* batch, bool singleButton = false);

	//Register button press
	void TouchBegan();

	//Reset display frame to "non" pressed frame
	void TouchEnd();

	//Check whether button has been pressed
	bool IsPressed();

	//Clears input. Run after each frame
	void ClearInput();

	//Release idle and pressed button sprites
	void onExit();

	~nrgDbutton();

protected:
	nrgDbutton(bool singleButton = false);
	bool buttonPressed = false; //Whether the button was pressed in the current frame. (Clear after each frame in ClearInput)
	cocos2d::Sprite* idleButton = cocos2d::Sprite::create(); //Sprite image for idle button
	cocos2d::Sprite* pressedButton = cocos2d::Sprite::create(); //Sprite image for pressed button
};

