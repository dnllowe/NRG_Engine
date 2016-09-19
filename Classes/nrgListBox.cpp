#include "pch.h"
#include "nrgListBox.h"

nrgListBox::nrgListBox(std::vector<std::string> listInput, std::string fontFile, int fontSizeInput, cocos2d::Color4B textColorInput, int boxBorderThickness, cocos2d::Color4F boxBorderColor, cocos2d::Color4F boxFillColor)
{
	box = nrgBox::create(realWidth + scale * letterWidth + scale * boxBorderThickness, realHeight + scale * letterHeight / 3 + scale * boxBorderThickness + 3 * boxBorderThickness, 0, 0, scale * boxBorderThickness, boxBorderColor, boxFillColor);
	addChild(box);
	box->setAnchorPoint(cocos2d::Vec2(0, 0));
	box->setPosition(0, 0);
	box->setLocalZOrder(0);
	
	for (int iii = 0; iii < numberOfItems; iii++)
		labels.at(iii)->setLocalZOrder(1);
	
}

nrgListBox * nrgListBox::create(std::vector<std::string> listInput, std::string fontFile, int fontSizeInput, cocos2d::Color4B textColorInput, int boxBorderThickness, cocos2d::Color4F boxBorderColor, cocos2d::Color4F boxFillColor)
{
	nrgListBox* listBox = new nrgListBox(listInput, fontFile, fontSizeInput, textColorInput, boxBorderThickness, boxBorderColor, boxFillColor);
	listBox->setAnchorPoint(cocos2d::Vec2(0, 1));
	listBox->autorelease();
	return listBox;
}

void nrgListBox::setPosition(float x, float y)
{
	nrgList::setPosition(x, y);
	//box->setPosition(-realWidth / 4, 1.3 * -realHeight);
	box->setPosition(0, 0);
	return;
}

void nrgListBox::setPositionX(float x)
{
	nrgList::setPositionX(x);
	//box->setPosition(-realWidth / 4, 1.3 * -realHeight);
	box->setPosition(0, 0);
	return;
}

void nrgListBox::setPositionY(float y)
{
	nrgList::setPositionY(y);
	//box->setPosition(-realWidth / 4, 1.3 * -realHeight);
	box->setPosition(0, 0);
	return;
}

void nrgListBox::SetTop(float y)
{
	nrgList::SetTop(y);
	//box->setPosition(-realWidth / 4, 1.3 * -realHeight);
	box->setPosition(0, 0);
	return;
}

void nrgListBox::SetBottom(float y)
{
	nrgList::SetBottom(y);
	//box->setPosition(-realWidth / 4, 1.3 * -realHeight);
	box->setPosition(0, 0);
	return;
}

void nrgListBox::SetRightSide(float x)
{
	nrgList::SetRightSide(x);
	//box->setPosition(-realWidth / 4, 1.3 * -realHeight);
	box->setPosition(0, 0);
	return;
}

void nrgListBox::Center(int offsetX, int offsetY)
{
	nrgList::Center(offsetX, offsetY);
	//box->setPosition(-realWidth / 4, 1.3 * -realHeight);
	box->setPosition(0, 0);
	return;
}

nrgListBox::~nrgListBox()
{
}


