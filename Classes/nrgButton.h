#pragma once
#include "pch.h"

class nrgButton : public nrgSprite
{
public:
	

	//Initialize Sprite using filename
	static nrgButton* create(std::string defaultFile, std::string selectedFile, bool alias = true);

	static nrgButton* create(cocos2d::SpriteBatchNode* batch, std::string defaultFile, std::string selectedFile, bool alias = true);

	//Enable eventListener for touch/mouse events
	void addEvents();

	//Link nrgText with button to control text color on press, hold, release
	void LinkWithText(nrgText*& text, cocos2d::Color3B pressColorInput);

	void setPosition(float x, float y);

	void setPositionX(float x);

	void setPositionY(float y);

	//Sets right side of sprite to coordinate
	void SetRightSide(int x);

	//Sets top of sprite to coordinate
	void SetTop(int y);

	//Centers sprite on screen with x and y offset
	void Center(int offsetX = 0, int offsetY = 0);

	//Set center x coordinate at x
	void SetCenter(int x = 0, int y = 0);

	//Set center x coordinate at x
	void SetCenterX(int x = 0);

	//Set center y coordinate at y
	void SetCenterY(int y = 0);

	//Move from current position by xValue and yValue
	void Move(float xValue = 0, float yValue = 0);

	//Check whether button was pressed
	bool WasPressed(bool savePress = false);

	void onExit();

	~nrgButton();

protected:

	nrgButton(std::string defaultFile, std::string selectedFile, bool alias = true);
	nrgButton(cocos2d::SpriteBatchNode* batch, std::string defaultFile, std::string selectedFile, bool alias = true);

	cocos2d::Sprite* defaultImage = cocos2d::Sprite::create(); //Default image
	cocos2d::Sprite* selectedImage = cocos2d::Sprite::create(); //Selected image
	nrgText* linkedText = NULL; //Text on button
	cocos2d::Color3B textPressColor; //Color of text on press
	cocos2d::Color3B textDefaultColor; //Color of text when not pressed
	bool pressed = false; //Whether the button was pressed
};

