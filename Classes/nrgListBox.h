#pragma once
#include "pch.h"
#include "nrgList.h"

class nrgListBox : public nrgList
{
public:
	nrgListBox(std::vector<std::string> listInput, std::string fontFile = NULL, int fontSizeInput = 10, cocos2d::Color4B textColorInput = cocos2d::Color4B::BLACK, int boxBorderThickness = 5, cocos2d::Color4F boxBorderColor = cocos2d::Color4F::WHITE, cocos2d::Color4F boxFillColor = cocos2d::Color4F::BLUE);
	static nrgListBox* create(std::vector<std::string> listInput, std::string fontFile = NULL, int fontSizeInput = 10, cocos2d::Color4B textColorInput = cocos2d::Color4B::BLACK, int boxBorderThickness = 5, cocos2d::Color4F boxBorderColor = cocos2d::Color4F::WHITE, cocos2d::Color4F boxFillColor = cocos2d::Color4F::BLUE);
	~nrgListBox();
	
	void setPosition(float x, float y);
	void setPositionX(float x);
	void setPositionY(float y);
	void SetTop(float y);
	void SetBottom(float y);
	void SetRightSide(float x);

	//Center onto screen at offset x and y
	void Center(int offsetX = 0, int offsetY = 0);

protected:
	nrgBox* box = NULL;
};

