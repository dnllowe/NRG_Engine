#include "pch.h"
#include "nrgBox.h"


nrgBox::nrgBox(float widthInput, float heightInput, int xCoord, int yCoord, int borderThicknessInput, cocos2d::Color4F borderColorInput, cocos2d::Color4F fillColorInput)
{
	//Initialize members
	draw = cocos2d::DrawNode::create();
	width = widthInput;
	height = heightInput;
	borderThickness = borderThicknessInput;
	setPositionX(xCoord);
	setPositionY(yCoord);
	borderColor = borderColorInput;
	fillColor = fillColorInput;

	//Add draw to object
	addChild(draw);

	//Anchor to bottom left
	draw->setAnchorPoint(cocos2d::Vec2(0, 0));
	setAnchorPoint(cocos2d::Vec2(0, 0));

	//Temp input for box
	float outerX1 = xCoord;
	float outerY1 = yCoord;
	float outerX2 = xCoord + widthInput;
	float outerY2 = yCoord + heightInput;
	float innerX1 = xCoord + borderThicknessInput;
	float innerY1 = yCoord + borderThicknessInput;
	float innerX2 = xCoord + widthInput - borderThicknessInput;
	float innerY2 = yCoord + heightInput - borderThicknessInput;

	//Draw the outer box
	draw->drawSegment(cocos2d::Vec2(outerX1, outerY1), cocos2d::Vec2(outerX2, outerY1), borderThickness, borderColor);
	draw->drawSegment(cocos2d::Vec2(outerX1, outerY2), cocos2d::Vec2(outerX2, outerY2), borderThickness, borderColor);
	draw->drawSegment(cocos2d::Vec2(outerX1, outerY1), cocos2d::Vec2(outerX1, outerY2), borderThickness, borderColor);
	draw->drawSegment(cocos2d::Vec2(outerX2, outerY1), cocos2d::Vec2(outerX2, outerY2), borderThickness, borderColor);

	//Draw the inner box
	draw->drawSegment(cocos2d::Vec2(innerX1, innerY1), cocos2d::Vec2(innerX2, innerY1), borderThickness, fillColor);
	draw->drawSegment(cocos2d::Vec2(innerX1, innerY2), cocos2d::Vec2(innerX2, innerY2), borderThickness, fillColor);
	draw->drawSegment(cocos2d::Vec2(innerX1, innerY1), cocos2d::Vec2(innerX1, innerY2), borderThickness, fillColor);
	draw->drawSegment(cocos2d::Vec2(innerX2, innerY1), cocos2d::Vec2(innerX2, innerY2), borderThickness, fillColor);

	//Fill the inner box
	draw->drawSolidRect(cocos2d::Vec2(innerX1, innerY1), cocos2d::Vec2(innerX2, innerY2), fillColor);

	setContentSize(cocos2d::Size(0, 0));
	draw->setContentSize(cocos2d::Size(0, 0));

	return;
}


nrgBox * nrgBox::create(float widthInput, float heightInput, int xCoord, int yCoord, int borderThicknessInput, cocos2d::Color4F borderColorInput, cocos2d::Color4F fillColorInput)
{
	//Initialize members
	nrgBox* node = new nrgBox(widthInput, heightInput, xCoord, yCoord, borderThicknessInput, borderColorInput, fillColorInput);
	node->autorelease();
	return node;
}

int nrgBox::GetBorderThickness()
{
	return borderThickness;
}

float nrgBox::GetWidth()
{
	return width;
}

float nrgBox::GetHeight()
{
	return height;
}

void nrgBox::Center(int offsetX, int offsetY)
{
	//Get screen width and height
	auto director = cocos2d::Director::getInstance();
	float screenWidth = director->getOpenGLView()->getDesignResolutionSize().width;
	float screenHeight = director->getOpenGLView()->getDesignResolutionSize().height;

	//Center the image
	x = screenWidth / 2 - width / 2 + offsetX;
	y = screenHeight / 2 - height / 2 + offsetY;
	Node::setPosition(x, y);

	return;
}

cocos2d::DrawNode * nrgBox::GetDrawNode()
{
	return draw;
}

nrgBox::~nrgBox()
{
}
