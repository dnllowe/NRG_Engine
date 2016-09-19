#include "pch.h"
#include "nrgDpad.h"

nrgDpad::nrgDpad()
{
}

nrgDpad::nrgDpad(cocos2d::SpriteBatchNode* batch)
{
	//Create all buttons
	leftButton = nrgDbuttonLeft::create(batch);
	rightButton = nrgDbuttonRight::create(batch);
	upButton = nrgDbuttonUp::create(batch);
	downButton = nrgDbuttonDown::create(batch);

	upperLeftRegion = nrgDbuttonTouchRegion::create(batch, leftButton);
	upperRightRegion = nrgDbuttonTouchRegion::create(batch, rightButton);
	lowerLeftRegion = nrgDbuttonTouchRegion::create(batch, leftButton);
	lowerRightRegion = nrgDbuttonTouchRegion::create(batch, rightButton);

	//Set scale for all buttons and padding
	scale = 1;
	
	//Add children, anchor to bottom left
	
	leftButton->setScale(scale);
	leftButton->setPosition(0, 0);
	rightButton->setScale(scale);
	rightButton->setPosition(0, 0);
	upButton->setScale(scale);
	upButton->setPosition(0, 0);
	downButton->setScale(scale);
	downButton->setPosition(0, 0);
	
	leftButton->setZOrder(2);
	rightButton->setZOrder(2);
	upButton->setZOrder(2);
	downButton->setZOrder(2);

	upperLeftRegion->setScale(scale);
	upperLeftRegion->setPosition(0, 0);
	lowerLeftRegion->setScale(scale);
	lowerLeftRegion->setPosition(0, 0);
	upperRightRegion->setScale(scale);
	upperRightRegion->setPosition(0, 0);
	lowerRightRegion->setScale(scale);
	lowerRightRegion->setPosition(0, 0);

	//Set size of buttons
	leftRightWidth = leftButton->getContentSize().width * scale;
	leftRightHeight = leftButton->getContentSize().height * scale; 
	upDownWidth = upButton->getContentSize().width * scale;
	upDownHeight = upButton->getContentSize().height * scale;
	innerLeftRightSpace = 38 * scale;
	innerUpDownSpace = 19 * scale;
	outerLeftRightSpace = 19 * scale;

	//Raise left button by 1.5 height to give room for bottom button (1) plus extra space (0.5)
	leftButton->Move(0, (leftRightHeight * 1.5));

	//Save leftButton coordinates
	float leftX = leftButton->getPositionX();
	float leftY = leftButton->getPositionY();

	//Move bottom button over 1 left/right width, then down one left/right height
	downButton->setPosition(leftX + leftRightWidth - innerLeftRightSpace, leftY - leftRightHeight - innerUpDownSpace);

	//Move bottom button over 1 left/right width, then up one left/right height
	upButton->setPosition(leftX + leftRightWidth - innerLeftRightSpace, leftY + leftRightHeight - innerUpDownSpace);

	//Move right button over 1 left/right width and 1 up/down width, then set height equal to left button height
	rightButton->setPosition(leftX + leftRightWidth + upDownWidth - innerLeftRightSpace * 2, leftY);

	//Set extra upper and lower touch region positions
	upperLeftRegion->setPosition(leftX + outerLeftRightSpace, leftY + leftRightHeight);
	lowerLeftRegion->setPosition(leftX + outerLeftRightSpace, leftY - leftRightHeight);
	upperRightRegion->setPosition(leftX + leftRightWidth + upDownWidth - innerLeftRightSpace, leftY + leftRightHeight);
	lowerRightRegion->setPosition(leftX + leftRightWidth + upDownWidth - innerLeftRightSpace, leftY - leftRightHeight);

	//Set size of dpad based on button sizes and overlapping areas
	setContentSize(cocos2d::Size(leftRightWidth * 2 + upDownWidth - innerLeftRightSpace * 2, leftRightHeight + upDownHeight * 2 - innerUpDownSpace * 2));
	width = getContentSize().width;
	height = getContentSize().height;
}

nrgDpad * nrgDpad::create(cocos2d::SpriteBatchNode * batch)
{
	nrgDpad* dpad = new nrgDpad(batch);
	dpad->autorelease();
	dpad->setAnchorPoint(cocos2d::Vec2(0, 0));
	return dpad;
}

void nrgDpad::ClearInput()
{
	leftButton->ClearInput();
	rightButton->ClearInput();
	upButton->ClearInput();
	downButton->ClearInput();
	upperLeftRegion->ClearInput();
	upperRightRegion->ClearInput();
	lowerLeftRegion->ClearInput();
	lowerRightRegion->ClearInput();

	return;
}

void nrgDpad::ResetButtonFrames()
{
	leftButton->setSpriteFrame("dButtonLeft.png");
	rightButton->setSpriteFrame("dButtonRight.png");
	upButton->setSpriteFrame("dButtonUp.png");
	downButton->setSpriteFrame("dButtonDown.png");

	return;
}

bool nrgDpad::IsLeftPressed()
{
	return leftButton->IsPressed();
}

bool nrgDpad::IsRightPressed()
{
	return rightButton->IsPressed();
}

bool nrgDpad::IsUpPressed()
{
	return upButton->IsPressed();
}

bool nrgDpad::IsDownPressed()
{
	return downButton->IsPressed();
}

void nrgDpad::SetRightSide(int x)
{
	leftButton->setPositionX(x - width);

	//Reposition buttons

	//Save leftButton coordinates
	float leftX = leftButton->getPositionX();
	float leftY = leftButton->getPositionY();

	//Move bottom button over 1 left/right width, then down one left/right height
	downButton->setPosition(leftX + leftRightWidth - innerLeftRightSpace, leftY - leftRightHeight - innerUpDownSpace);

	//Move bottom button over 1 left/right width, then up one left/right height
	upButton->setPosition(leftX + leftRightWidth - innerLeftRightSpace, leftY + leftRightHeight - innerUpDownSpace);

	//Move right button over 1 left/right width and 1 up/down width, then set height equal to left button height
	rightButton->setPosition(leftX + leftRightWidth + upDownWidth - innerLeftRightSpace * 2, leftY);

	//Set extra upper and lower touch region positions
	upperLeftRegion->setPosition(leftX + outerLeftRightSpace, leftY + leftRightHeight);
	lowerLeftRegion->setPosition(leftX + outerLeftRightSpace, leftY - leftRightHeight);
	upperRightRegion->setPosition(leftX + leftRightWidth + upDownWidth - innerLeftRightSpace, leftY + leftRightHeight);
	lowerRightRegion->setPosition(leftX + leftRightWidth + upDownWidth - innerLeftRightSpace, leftY - leftRightHeight);

	Node::setPositionX(x - width);
	
	return;
}

int nrgDpad::GetRightSide()
{
	return Node::getPositionX() + width;
}

void nrgDpad::SetTop(int y)
{
	leftButton->setPositionY(y - upDownHeight);

	//Reposition buttons

	//Save leftButton coordinates
	float leftX = leftButton->getPositionX();
	float leftY = leftButton->getPositionY();

	//Move bottom button over 1 left/right width, then down one left/right height
	downButton->setPosition(leftX + leftRightWidth - innerLeftRightSpace, leftY - leftRightHeight - innerUpDownSpace);

	//Move bottom button over 1 left/right width, then up one left/right height
	upButton->setPosition(leftX + leftRightWidth - innerLeftRightSpace, leftY + leftRightHeight - innerUpDownSpace);

	//Move right button over 1 left/right width and 1 up/down width, then set height equal to left button height
	rightButton->setPosition(leftX + leftRightWidth + upDownWidth - innerLeftRightSpace * 2, leftY);

	//Set extra upper and lower touch region positions
	upperLeftRegion->setPosition(leftX + outerLeftRightSpace, leftY + leftRightHeight);
	lowerLeftRegion->setPosition(leftX + outerLeftRightSpace, leftY - leftRightHeight);
	upperRightRegion->setPosition(leftX + leftRightWidth + upDownWidth - innerLeftRightSpace, leftY + leftRightHeight);
	lowerRightRegion->setPosition(leftX + leftRightWidth + upDownWidth - innerLeftRightSpace, leftY - leftRightHeight);

	Node::setPositionY(y - height);

	return;
}

int nrgDpad::GetTop()
{
	return Node::getPositionY() + height;
}

void nrgDpad::Center(int offsetX, int offsetY)
{
	//Get screen width and height
	auto director = cocos2d::Director::getInstance();
	int screenWidth = director->getOpenGLView()->getDesignResolutionSize().width;
	int screenHeight = director->getOpenGLView()->getDesignResolutionSize().height;

	//Center the image
	Node::setPosition(screenWidth / 2 - width / 2 + offsetX, screenHeight / 2 - height / 2 + offsetY);

	//Set left button to appropriate x and y coordinate
	leftButton->setPosition(Node::getPositionX() + offsetX, Node::getPositionY() + leftRightHeight + offsetY);

	//Save leftButton coordinates
	float leftX = leftButton->getPositionX();
	float leftY = leftButton->getPositionY();

	//Move bottom button over 1 left/right width, then down one left/right height
	downButton->setPosition(leftX + leftRightWidth - innerLeftRightSpace, leftY - leftRightHeight - innerUpDownSpace);

	//Move bottom button over 1 left/right width, then up one left/right height
	upButton->setPosition(leftX + leftRightWidth - innerLeftRightSpace, leftY + leftRightHeight - innerUpDownSpace);

	//Move right button over 1 left/right width and 1 up/down width, then set height equal to left button height
	rightButton->setPosition(leftX + leftRightWidth + upDownWidth - innerLeftRightSpace * 2, leftY);

	//Set extra upper and lower touch region positions
	upperLeftRegion->setPosition(leftX + outerLeftRightSpace, leftY + leftRightHeight);
	lowerLeftRegion->setPosition(leftX + outerLeftRightSpace, leftY - leftRightHeight);
	upperRightRegion->setPosition(leftX + leftRightWidth + upDownWidth - innerLeftRightSpace, leftY + leftRightHeight);
	lowerRightRegion->setPosition(leftX + leftRightWidth + upDownWidth - innerLeftRightSpace, leftY - leftRightHeight);

	return;
}

void nrgDpad::setScale(float value)
{
	float previousScale = scale;
	scale = value;
	float dScale = scale / previousScale; //The proportional change from the previous scale to the new scale
	Node::setScale(value);
	
	float oldCenterX = Node::getPositionX() + width / 2;
	float oldCenterY = Node::getPositionY() + height / 2;
	float oldDistanceFromCenterX = oldCenterX - leftButton->getPositionX();
	float oldDistanceFromCenterY = oldCenterY - leftButton->getPositionY();
	float newDistanceFromCenterX = oldDistanceFromCenterX * dScale;
	float newDistanceFromCenterY = oldDistanceFromCenterY * dScale;
	leftButton->setScale(scale);
	leftButton->setPosition(oldCenterX - newDistanceFromCenterX, oldCenterY - newDistanceFromCenterY);
	
	float newCenterX = leftButton->getPositionX() + leftRightWidth / 2 * scale;
	float newCenterY = leftButton->getPositionY() + leftRightHeight / 2 * scale;

	rightButton->setScale(scale);
	upButton->setScale(scale);
	downButton->setScale(scale);

	upperLeftRegion->setScale(scale);
	lowerLeftRegion->setScale(scale);
	upperRightRegion->setScale(scale);
	lowerRightRegion->setScale(scale);

	//Set size of buttons
	leftRightWidth = leftButton->getContentSize().width * scale;
	leftRightHeight = leftButton->getContentSize().height * scale;
	upDownWidth = upButton->getContentSize().width * scale;
	upDownHeight = upButton->getContentSize().height * scale;
	innerLeftRightSpace = 38 * scale;
	innerUpDownSpace = 19 * scale;
	outerLeftRightSpace = 19 * scale;

	//Reposition buttons

	//Save leftButton coordinates
	float leftX = leftButton->getPositionX();
	float leftY = leftButton->getPositionY();

	//Move bottom button over 1 left/right width, then down one left/right height
	downButton->setPosition(leftX + leftRightWidth - innerLeftRightSpace, leftY - leftRightHeight - innerUpDownSpace);

	//Move bottom button over 1 left/right width, then up one left/right height
	upButton->setPosition(leftX + leftRightWidth - innerLeftRightSpace, leftY + leftRightHeight - innerUpDownSpace);

	//Move right button over 1 left/right width and 1 up/down width, then set height equal to left button height
	rightButton->setPosition(leftX + leftRightWidth + upDownWidth - innerLeftRightSpace * 2, leftY);

	//Set extra upper and lower touch region positions
	upperLeftRegion->setPosition(leftX + outerLeftRightSpace, leftY + leftRightHeight);
	lowerLeftRegion->setPosition(leftX + outerLeftRightSpace, leftY - leftRightHeight);
	upperRightRegion->setPosition(leftX + leftRightWidth + upDownWidth - innerLeftRightSpace, leftY + leftRightHeight);
	lowerRightRegion->setPosition(leftX + leftRightWidth + upDownWidth - innerLeftRightSpace, leftY - leftRightHeight);

	//Set size of dpad based on button sizes and overlapping areas
	setContentSize(cocos2d::Size(leftRightWidth * 2 + upDownWidth - innerLeftRightSpace * 2, leftRightHeight + upDownHeight * 2 - innerUpDownSpace * 2));
	width = getContentSize().width;
	height = getContentSize().height;

	return;
}

void nrgDpad::setPositionX(float x)
{
	leftButton->setPositionX(x);

	//Reposition buttons

	//Save leftButton coordinates
	float leftX = leftButton->getPositionX();
	float leftY = leftButton->getPositionY();

	//Move bottom button over 1 left/right width, then down one left/right height
	downButton->setPosition(leftX + leftRightWidth - innerLeftRightSpace, leftY - leftRightHeight - innerUpDownSpace);

	//Move bottom button over 1 left/right width, then up one left/right height
	upButton->setPosition(leftX + leftRightWidth - innerLeftRightSpace, leftY + leftRightHeight - innerUpDownSpace);

	//Move right button over 1 left/right width and 1 up/down width, then set height equal to left button height
	rightButton->setPosition(leftX + leftRightWidth + upDownWidth - innerLeftRightSpace * 2, leftY);

	//Set extra upper and lower touch region positions
	upperLeftRegion->setPosition(leftX + outerLeftRightSpace, leftY + leftRightHeight);
	lowerLeftRegion->setPosition(leftX + outerLeftRightSpace, leftY - leftRightHeight);
	upperRightRegion->setPosition(leftX + leftRightWidth + upDownWidth - innerLeftRightSpace, leftY + leftRightHeight);
	lowerRightRegion->setPosition(leftX + leftRightWidth + upDownWidth - innerLeftRightSpace, leftY - leftRightHeight);

	Node::setPositionX(x);

	return;
}

void nrgDpad::setPositionY(float y)
{
	leftButton->setPositionY(y + upDownHeight - innerUpDownSpace);

	//Reposition buttons

	//Save leftButton coordinates
	float leftX = leftButton->getPositionX();
	float leftY = leftButton->getPositionY();

	//Move bottom button over 1 left/right width, then down one left/right height
	downButton->setPosition(leftX + leftRightWidth - innerLeftRightSpace, leftY - leftRightHeight - innerUpDownSpace);

	//Move bottom button over 1 left/right width, then up one left/right height
	upButton->setPosition(leftX + leftRightWidth - innerLeftRightSpace, leftY + leftRightHeight - innerUpDownSpace);

	//Move right button over 1 left/right width and 1 up/down width, then set height equal to left button height
	rightButton->setPosition(leftX + leftRightWidth + upDownWidth - innerLeftRightSpace * 2, leftY);

	//Set extra upper and lower touch region positions
	upperLeftRegion->setPosition(leftX + outerLeftRightSpace, leftY + leftRightHeight);
	lowerLeftRegion->setPosition(leftX + outerLeftRightSpace, leftY - leftRightHeight);
	upperRightRegion->setPosition(leftX + leftRightWidth + upDownWidth - innerLeftRightSpace, leftY + leftRightHeight);
	lowerRightRegion->setPosition(leftX + leftRightWidth + upDownWidth - innerLeftRightSpace, leftY - leftRightHeight);

	Node::setPositionY(y);

	return;
}

void nrgDpad::setPosition(float x, float y)
{
	leftButton->setPosition(x, y + upDownHeight - innerUpDownSpace);

	//Reposition buttons

	//Save leftButton coordinates
	float leftX = leftButton->getPositionX();
	float leftY = leftButton->getPositionY();

	//Move bottom button over 1 left/right width, then down one left/right height
	downButton->setPosition(leftX + leftRightWidth - innerLeftRightSpace, leftY - leftRightHeight - innerUpDownSpace);

	//Move bottom button over 1 left/right width, then up one left/right height
	upButton->setPosition(leftX + leftRightWidth - innerLeftRightSpace, leftY + leftRightHeight - innerUpDownSpace);

	//Move right button over 1 left/right width and 1 up/down width, then set height equal to left button height
	rightButton->setPosition(leftX + leftRightWidth + upDownWidth - innerLeftRightSpace * 2, leftY);

	//Set extra upper and lower touch region positions
	upperLeftRegion->setPosition(leftX + outerLeftRightSpace, leftY + leftRightHeight);
	lowerLeftRegion->setPosition(leftX + outerLeftRightSpace, leftY - leftRightHeight);
	upperRightRegion->setPosition(leftX + leftRightWidth + upDownWidth - innerLeftRightSpace, leftY + leftRightHeight);
	lowerRightRegion->setPosition(leftX + leftRightWidth + upDownWidth - innerLeftRightSpace, leftY - leftRightHeight);

	Node::setPosition(x, y);
	
	return;
}

void nrgDpad::setPosition(const cocos2d::Vec2 & pos)
{
	float x = pos.x;
	float y = pos.y;

	leftButton->setPosition(x, y + upDownHeight - innerUpDownSpace);

	//Reposition buttons

	//Save leftButton coordinates
	float leftX = leftButton->getPositionX();
	float leftY = leftButton->getPositionY();

	//Move bottom button over 1 left/right width, then down one left/right height
	downButton->setPosition(leftX + leftRightWidth - innerLeftRightSpace, leftY - leftRightHeight - innerUpDownSpace);

	//Move bottom button over 1 left/right width, then up one left/right height
	upButton->setPosition(leftX + leftRightWidth - innerLeftRightSpace, leftY + leftRightHeight - innerUpDownSpace);

	//Move right button over 1 left/right width and 1 up/down width, then set height equal to left button height
	rightButton->setPosition(leftX + leftRightWidth + upDownWidth - innerLeftRightSpace * 2, leftY);

	//Set extra upper and lower touch region positions
	upperLeftRegion->setPosition(leftX + outerLeftRightSpace, leftY + leftRightHeight);
	lowerLeftRegion->setPosition(leftX + outerLeftRightSpace, leftY - leftRightHeight);
	upperRightRegion->setPosition(leftX + leftRightWidth + upDownWidth - innerLeftRightSpace, leftY + leftRightHeight);
	lowerRightRegion->setPosition(leftX + leftRightWidth + upDownWidth - innerLeftRightSpace, leftY - leftRightHeight);

	Node::setPosition(x, y);

	return;
}

void nrgDpad::ToggleEnabled(bool value)
{
	leftButton->setVisible(value);
	leftButton->ToggleTouch(value);
	rightButton->setVisible(value);
	rightButton->ToggleTouch(value);
	upButton->setVisible(value);
	upButton->ToggleTouch(value);
	downButton->setVisible(value);
	downButton->ToggleTouch(value);
	upperLeftRegion->setVisible(value);
	upperLeftRegion->ToggleTouch(value);
	upperRightRegion->setVisible(value);
	upperRightRegion->ToggleTouch(value);
	lowerLeftRegion->setVisible(value);
	lowerLeftRegion->ToggleTouch(value);
	lowerRightRegion->setVisible(value);
	lowerRightRegion->ToggleTouch(value);

	return;
}

nrgDpad::~nrgDpad()
{
}
