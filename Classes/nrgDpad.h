#pragma once
#include "pch.h"

//Forward declaration for nrgDbutton
class nrgDbutton;

class nrgDpad : public cocos2d::Node
{
public:
	nrgDpad(cocos2d::SpriteBatchNode* batch);

	//Create nrgDpad object using scene batch
	static nrgDpad* create(cocos2d::SpriteBatchNode* batch);

	//Clear input of all buttons
	virtual void ClearInput();

	//Reset frames back to default 
	virtual void ResetButtonFrames();

	//Check if left buton was pressed
	virtual bool IsLeftPressed();

	//Check if right button was pressed
	virtual bool IsRightPressed();

	//Check if up button was pressed
	virtual bool IsUpPressed();

	//Check if down button was pressed
	virtual bool IsDownPressed();

	//Sets right side of sprite to coordinate
	virtual void SetRightSide(int x);

	//Return Right Side coordinate (x coordinate + width)
	virtual int GetRightSide();

	//Sets top of sprite to coordinate
	virtual void SetTop(int y);

	//Return Top coordinate (y coordinate + height)
	virtual int GetTop();

	//Centers sprite on screen with x and y offset
	virtual void Center(int offsetX = 0, int offsetY = 0);


	//Override Node Functions

	//
	virtual void setScale(float value);

	//
	virtual void setPositionX(float x);

	//
	virtual void setPositionY(float y);

	//
	virtual void setPosition(float x, float y);

	//
	virtual void setPosition(const cocos2d::Vec2& pos);

	//Enable/Disable dpad, visibility, and touch listeners
	virtual void ToggleEnabled(bool value);

	~nrgDpad();

protected:
	nrgDpad(); //Default constructor for derived dpad objects
	float scale = 1; //Scale factor for all objects
	nrgDbutton* leftButton = NULL; //Handle input and placement for left button
	nrgDbutton* rightButton = NULL; //Handle input and placement for right button
	nrgDbutton* upButton = NULL; //Handle input and placement for up button
	nrgDbutton* downButton = NULL; //Handle input and placement for down button

	nrgDbuttonTouchRegion* upperLeftRegion = NULL; //Detects touches above left direction button and runs TouchBegan
	nrgDbuttonTouchRegion* upperRightRegion = NULL; //Detects touches above right direction button and runs TouchBegan
	nrgDbuttonTouchRegion* lowerLeftRegion = NULL; //Detects touches below left direction button and runs TouchBegan
	nrgDbuttonTouchRegion* lowerRightRegion = NULL; //Detects touches below right direction button and runs TouchBegan

	float leftRightWidth = 0;
	float leftRightHeight = 0;
	float upDownWidth = 0;
	float upDownHeight = 0;
	float innerLeftRightSpace = 0;
	float innerUpDownSpace = 0;
	float outerLeftRightSpace = 0;

	float width = 0; //Width of entire dpad
	float height = 0; //Height of entire dpad

};

