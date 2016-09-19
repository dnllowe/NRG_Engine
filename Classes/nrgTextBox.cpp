#include "pch.h"
#include "nrgTextBox.h"


nrgTextBox::nrgTextBox(std::string textInput, std::string fontFilepath, int fontSize, int widthInput, int xCoord, int yCoord, cocos2d::Color4B textColor, cocos2d::TextHAlignment hAlignment, int boxBorderThickness, cocos2d::Color4F boxBorderColor, cocos2d::Color4F boxFillColor) :
	nrgText(textInput, fontFilepath, fontSize, widthInput, textColor, hAlignment)
{
	box = nrgBox::create(realWidth + scale * letterWidth + scale * boxBorderThickness, realHeight + scale * letterHeight / 3 + scale * boxBorderThickness + 3 * boxBorderThickness, 0, 0, scale * boxBorderThickness, boxBorderColor, boxFillColor);
	addChild(box);
	box->setAnchorPoint(cocos2d::Vec2(0, 0));
	setPosition(xCoord, yCoord);
	box->setPositionY(yCoord);
	box->setLocalZOrder(0);
	label->setLocalZOrder(1);
}


nrgTextBox * nrgTextBox::create(std::string textInput, std::string fontFilepath, int fontSize, int widthInput, int xCoord, int yCoord, cocos2d::Color4B textColor, cocos2d::TextHAlignment hAlignment, int boxBorderThickness, cocos2d::Color4F boxBorderColor, cocos2d::Color4F boxFillColor)
{
	nrgTextBox* textBox = new nrgTextBox(textInput, fontFilepath, fontSize, widthInput, xCoord, yCoord, textColor, hAlignment, boxBorderThickness, boxBorderColor, boxFillColor);
	textBox->setAnchorPoint(cocos2d::Vec2(0, 1));
	textBox->autorelease();
	
	return textBox;
}

nrgTextBox::~nrgTextBox()
{
}

void nrgTextBox::Center(int offsetX, int offsetY)
{
	nrgText::Center(offsetX, offsetY);
	box->setPosition(boxOffsetX + label->getPositionX() - box->GetBorderThickness() - scale * letterWidth / 2, boxOffsetY + label->getPositionY() - realHeight - scale * letterHeight / 2);
	return;
}

void nrgTextBox::setPosition(float x, float y)
{
	nrgText::setPosition(x ,y);
	box->setPosition(boxOffsetX + label->getPositionX() - box->GetBorderThickness() - scale * letterWidth / 2, boxOffsetY + label->getPositionY() - realHeight - scale * letterHeight / 2);
	return;
}

void nrgTextBox::setPositionX(float x)
{
	nrgText::setPositionX(x);
	box->setPosition(boxOffsetX + label->getPositionX() - box->GetBorderThickness() - scale * letterWidth / 2, boxOffsetY + label->getPositionY() - realHeight - scale * letterHeight / 2);
	return;
}

void nrgTextBox::setPositionY(float y)
{
	nrgText::setPositionY(y);
	box->setPosition(boxOffsetX + label->getPositionX() - box->GetBorderThickness() - scale * letterWidth / 2, boxOffsetY + label->getPositionY() - realHeight - scale * letterHeight / 2);
	return;
}

void nrgTextBox::SetTop(float y)
{
	nrgText::setPositionY(y);
	box->setPosition(boxOffsetX + label->getPositionX() - box->GetBorderThickness() - scale * letterWidth / 2, boxOffsetY + label->getPositionY() - realHeight - scale * letterHeight / 2);
	return;
}

void nrgTextBox::SetBottom(float y)
{
	nrgText::SetBottom(y);
	box->setPosition(boxOffsetX + label->getPositionX() - box->GetBorderThickness() - scale * letterWidth / 2, boxOffsetY + label->getPositionY() - realHeight - scale * letterHeight / 2);
	return;
}

void nrgTextBox::SetRightSide(float x)
{
	nrgText::SetRightSide(x);
	box->setPosition(boxOffsetX + label->getPositionX() - box->GetBorderThickness() - scale * letterWidth / 2, boxOffsetY + label->getPositionY() - realHeight - scale * letterHeight / 2);
	return;
}

void nrgTextBox::SetBoxOffset(int x, int y)
{
	boxOffsetX = x;
	boxOffsetY = y;
	return;
}

void nrgTextBox::SetBoxOffsetX(int x)
{
	boxOffsetX = x;
	return;
}

void nrgTextBox::SetBoxOffsetY(int y)
{
	boxOffsetY = y;
	return;
}

nrgBox * nrgTextBox::GetBox()
{
	return box;
}
