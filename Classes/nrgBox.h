#pragma once
#include "pch.h"

class nrgBox : public cocos2d::Node
{
public:

	//Creates an nrgBox with width, height, and border thickness.  Border = color1, fill color = color2
	static nrgBox* create(float widthInput, float heightInput, int xCoord, int yCoord, int borderThicknessInput = 5, cocos2d::Color4F borderColorInput = cocos2d::Color4F::BLACK, cocos2d::Color4F fillColorInput = cocos2d::Color4F::WHITE);

	//Returns thickness of border
	int GetBorderThickness();
	float GetWidth();
	float GetHeight();

	//Center box on screen with offset x and y
	void Center(int offsetX = 0, int offsetY = 0);

	//Returns draw node (the actual graphic for the box)
	cocos2d::DrawNode* GetDrawNode();

	~nrgBox();

protected:
	nrgBox(float widthInput, float heightInput, int xCoord, int yCoord, int borderThicknessInput = 5, cocos2d::Color4F borderColorInput = cocos2d::Color4F::BLACK, cocos2d::Color4F fillColorInput = cocos2d::Color4F::WHITE); //Default constructor is protected. USE create
	cocos2d::DrawNode* draw = NULL; //DrawNode to create box shapes
	float width; //Width of box
	float height; //Height of box
	float x; //xCoordinate
	float y; //yCoordinate
	int borderThickness; //Thickness of border
	cocos2d::Color4F borderColor; //Color of border
	cocos2d::Color4F fillColor; //Color of fill rectangle

};

