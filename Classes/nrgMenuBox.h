#pragma once
#include "nrgMenu.h"
#include "pch.h"

class nrgMenuBox : public nrgMenu
{
public:
	nrgMenuBox(std::vector<std::string> listInput, std::string fontFile = NULL, int limitInput = 0, int fontSizeInput = 10, int spacingInput = 0, cocos2d::Color4B textColorInput = cocos2d::Color4B::BLACK, cocos2d::Color4B textColor2Input = cocos2d::Color4B::YELLOW, bool highlightFirstOption = true, int boxBorderThickness = 5, cocos2d::Color4F boxBorderColor = cocos2d::Color4F::WHITE, cocos2d::Color4F boxFillColor = cocos2d::Color4F::BLUE);
	~nrgMenuBox();

	static nrgMenuBox* create(std::vector<std::string> listInput, std::string fontFile = NULL, int limitInput = 0, int fontSizeInput = 10, int spacingInput = 0, cocos2d::Color4B textColor1Input = cocos2d::Color4B::BLACK, cocos2d::Color4B textColor2Input = cocos2d::Color4B::YELLOW, bool highlightFirstOption = true, int boxBorderThickness = 5, cocos2d::Color4F boxBorderColor = cocos2d::Color4F::WHITE, cocos2d::Color4F boxFillColor = cocos2d::Color4F::BLUE);

	void setPosition(float x, float y);
	void setPositionX(float x);
	void setPositionY(float y);
	void SetTop(float y);
	void SetBottom(float y);
	void SetRightSide(float x);
	void SetBoxOffset(int x, int y);
	void SetBoxOffsetX(int x);
	void SetBoxOffsetY(int y);

	//Center onto screen at offset x and y
	void Center(int offsetX = 0, int offsetY = 0);

protected:
	nrgBox* box = NULL;
	int boxOffsetX = 0; //Offset to keep box and text positioned properly
	int boxOffsetY = 0; //Offset to keep box and text positioned properly
};

