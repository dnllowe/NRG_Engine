#pragma once
#include "nrgText.h"
#include "pch.h" 

//Forward declaration got nrgBox
class nrgBox;

//nrgText encapsulated by nrgBox
class nrgTextBox : public nrgText
{
public:
	//Create nrgText and nrgBox (nrgTextBox). NOTE: anchor point for nrgTextBox is TOP LEFT
	static nrgTextBox* create(std::string textInput, std::string fontFilepath, int fontSize = 12, int widthInput = 240, int xCoord = 0, int yCoord = 0, cocos2d::Color4B textColor = cocos2d::Color4B::WHITE, cocos2d::TextHAlignment hAlignment = cocos2d::TextHAlignment::LEFT, int boxBorderThickness = 5, cocos2d::Color4F boxBorderColor = cocos2d::Color4F::WHITE, cocos2d::Color4F boxFillColor = cocos2d::Color4F::BLUE);
	~nrgTextBox();

	//Center onto screen at offset x and y
	void Center(int offsetX = 0, int offsetY = 0);

	//Overload setPosition for box
	void setPosition(float x, float y);
	void setPositionX(float x);
	void setPositionY(float y);
	void SetTop(float y);
	void SetBottom(float y);
	void SetRightSide(float x);
	void SetBoxOffset(int x, int y);
	void SetBoxOffsetX(int x);
	void SetBoxOffsetY(int y);

	//Return box to add to scene in scene init
	nrgBox* GetBox();

protected:
	nrgTextBox(std::string textInput, std::string fontFilepath, int fontSize = 12, int widthInput = 240, int xCoord = 0, int yCoord = 0, cocos2d::Color4B textColor = cocos2d::Color4B::WHITE, cocos2d::TextHAlignment hAlignment = cocos2d::TextHAlignment::LEFT, int boxBorderThickness = 5, cocos2d::Color4F boxBorderColor = cocos2d::Color4F::WHITE, cocos2d::Color4F boxFillColor = cocos2d::Color4F::BLUE); //Default Constructor is protected. USE create
	nrgBox* box = NULL; //Box surrounding text
	int boxOffsetX = 0; //Offset to keep box and text positioned properly
	int boxOffsetY = 0; //Offset to keep box and text positioned properly
};

