#include "pch.h"
#include "nrgMenuBox.h"


nrgMenuBox::nrgMenuBox(std::vector<std::string> listInput, std::string fontFile, int limitInput, int fontSizeInput, int spacingInput, cocos2d::Color4B textColor1Input, cocos2d::Color4B textColor2Input, bool highlightFirstOption, int boxBorderThickness, cocos2d::Color4F boxBorderColor, cocos2d::Color4F boxFillColor)
	: nrgMenu(listInput, fontFile, limitInput, fontSizeInput, spacingInput, textColor1Input, textColor2Input, highlightFirstOption)

{
	box = nrgBox::create(realWidth + scale * letterWidth + scale * boxBorderThickness, realHeight + scale * letterHeight / 3 + scale * boxBorderThickness + 3 * boxBorderThickness, 0, 0, scale * boxBorderThickness, boxBorderColor, boxFillColor);
	addChild(box);
	box->setAnchorPoint(cocos2d::Vec2(0, 0));
	box->setPosition(0, 0);
	box->setLocalZOrder(0);
	
	for (int iii = 0; iii < numberOfOptions; iii++)
		option.at(iii)->setLocalZOrder(1);
}


nrgMenuBox::~nrgMenuBox()
{
}

nrgMenuBox * nrgMenuBox::create(std::vector<std::string> listInput, std::string fontFile, int limitInput, int fontSizeInput, int spacingInput, cocos2d::Color4B textColor1Input, cocos2d::Color4B textColor2Input, bool highlightFirstOption, int boxBorderThickness, cocos2d::Color4F boxBorderColor, cocos2d::Color4F boxFillColor)
{
	nrgMenuBox* menuBox = new nrgMenuBox(listInput, fontFile, limitInput, fontSizeInput, spacingInput, textColor1Input, textColor2Input, highlightFirstOption, boxBorderThickness, boxBorderColor, boxFillColor);
	menuBox->setAnchorPoint(cocos2d::Vec2(0, 1));
	menuBox->autorelease();
	return menuBox;
}

void nrgMenuBox::setPosition(float x, float y)
{
	nrgMenu::setPosition(x + box->GetWidth() / scale / 2 + box->GetBorderThickness() / 2, y - box->GetHeight() / scale / 2);
	box->setPosition(boxOffsetX + option.at(0)->getPositionX() - box->GetBorderThickness() - scale * letterWidth / 2, boxOffsetY + option.at(0)->getPositionY());
	return;
}

void nrgMenuBox::setPositionX(float x)
{
	nrgMenu::setPositionX(x + box->GetWidth() / scale / 2 - box->GetBorderThickness() / 2);
	box->setPosition(boxOffsetX + option.at(0)->getPositionX() - box->GetBorderThickness() - scale * letterWidth / 2, boxOffsetY + option.at(0)->getPositionY());
	return;
}

void nrgMenuBox::setPositionY(float y)
{
	nrgMenu::setPositionY(y - box->GetHeight() / scale / 2 - box->GetBorderThickness() / 2);
	box->setPosition(boxOffsetX + option.at(0)->getPositionX() - box->GetBorderThickness() - scale * letterWidth / 2, boxOffsetY + option.at(0)->getPositionY());
	return;
}

void nrgMenuBox::SetTop(float y)
{
	nrgMenu::SetTop(y - box->GetHeight() / scale - box->GetBorderThickness());
	box->setPosition(boxOffsetX + option.at(0)->getPositionX() - box->GetBorderThickness() - scale * letterWidth / 2, boxOffsetY + option.at(0)->getPositionY());
	return;
}

void nrgMenuBox::SetBottom(float y)
{
	nrgMenu::setPositionY(y + box->GetHeight() / scale - box->GetBorderThickness() * 2);
	box->setPosition(boxOffsetX + option.at(0)->getPositionX() - box->GetBorderThickness() - scale * letterWidth / 2, boxOffsetY + option.at(0)->getPositionY());
	return;
}

void nrgMenuBox::SetRightSide(float x)
{
	nrgMenu::SetRightSide(x - box->GetBorderThickness() / 2 - scale * letterWidth / 4);
	box->setPosition(boxOffsetX + option.at(0)->getPositionX() - box->GetBorderThickness() - scale * letterWidth / 2, boxOffsetY + option.at(0)->getPositionY());
	return;
}

void nrgMenuBox::SetBoxOffset(int x, int y)
{
	boxOffsetX = x;
	boxOffsetY = y;
	return;
}

void nrgMenuBox::SetBoxOffsetX(int x)
{
	boxOffsetX = x;
	return;
}

void nrgMenuBox::SetBoxOffsetY(int y)
{
	boxOffsetY = y;
	return;
}

void nrgMenuBox::Center(int offsetX, int offsetY)
{
	nrgMenu::Center(offsetX, offsetY);
	box->setPosition(boxOffsetX + option.at(0)->getPositionX() - box->GetBorderThickness() - scale * letterWidth / 2, boxOffsetY + option.at(0)->getPositionY());

	return;
}
