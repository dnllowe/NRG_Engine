#include "pch.h"
#include "nrgList.h"

nrgList::nrgList()
{

}

nrgList* nrgList::create(std::vector<std::string> listInput, std::string fontFile, int fontSizeInput, int spacingInput, cocos2d::Color4B textColorInput)
{
	nrgList* menu = new nrgList(listInput, fontFile, fontSizeInput, spacingInput, textColorInput);
	menu->autorelease();
	return menu;
}

nrgList * nrgList::create(std::string listInput, std::string fontFile, int fontSizeInput, int spacingInput, cocos2d::Color4B textColorInput)
{
	std::vector<std::string> input{ listInput };
	nrgList* menu = new nrgList(input, fontFile, fontSizeInput, spacingInput, textColorInput);
	menu->autorelease();
	return menu;
}

nrgList::nrgList(std::vector<std::string> listInput, std::string fontFile, int fontSizeInput, int spacingInput, cocos2d::Color4B textColorInput)
{
	font = fontFile;
	fontSize = fontSizeInput;
	spacing = spacingInput;
	textColor = textColorInput;
	strings = listInput;
	setAnchorPoint(cocos2d::Vec2(0, 0));

	auto glview = cocos2d::Director::getInstance()->getOpenGLView();

	///Adjust font size for actual frame size
	float widthScale = glview->getFrameSize().width / glview->getDesignResolutionSize().width;
	float heightScale = glview->getFrameSize().height / glview->getDesignResolutionSize().height;

	if (widthScale > heightScale)
		scale = widthScale;
	else
		scale = heightScale;

	fontSize *= scale;
	//Shrink enlarged font so that it is the right size when auto-scaled
	setScale(1 / scale);

	//Count total number of options
	numberOfItems = strings.size();

	//Get dimensions

	//Create temporary label to get letter width
	cocos2d::Label* tempLabel = cocos2d::Label::createWithTTF("M", fontFile, fontSize, cocos2d::Size::ZERO, cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP);
	letterWidth = tempLabel->getContentSize().width * (1 / scale);
	letterHeight = tempLabel->getContentSize().height * (1 / scale);

	//Create surface for each remaining option
	for (int iii = 0; iii < numberOfItems; iii++)
	{
		labels.push_back(cocos2d::Label::createWithTTF(strings[iii], font, fontSize, cocos2d::Size::ZERO, cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP));
		labels.at(iii)->setTextColor(textColorInput);
		labels.at(iii)->setBlendFunc(cocos2d::BlendFunc::ALPHA_NON_PREMULTIPLIED);
		addChild(labels.at(iii));
		labels.at(iii)->setAnchorPoint(cocos2d::Vec2(0, 0));
		labels.at(iii)->setPosition(0, (-iii * scale * letterHeight) - iii * spacing);
	}

	float top = labels.at(0)->getPositionY();
	float bottom = labels.at(numberOfItems - 1)->getPositionY() - letterHeight;
	realHeight = top - bottom;

	//Find the longest line
	int currentLine = 0;
	longestLine = 0;
	int width1 = 0;
	int width2 = 0;

	for (; currentLine < numberOfItems; currentLine++)
	{
		width1 = labels.at(currentLine)->getContentSize().width;
		width2 = labels.at(longestLine)->getContentSize().width;

		if (width1 > width2)
			longestLine = currentLine;
	}

	realWidth = labels.at(longestLine)->getContentSize().width;
	scaledWidth = realWidth / scale;
	scaledHeight = realHeight / scale;

	pos.x = 0;
	pos.y = 0;
}

void nrgList::ChangeList(std::vector<std::string> listInput)
{
	//Clear/remove previous objects
	strings.clear();
	labels.clear();
	removeAllChildren();

	strings = listInput;

	//Count total number of options
	numberOfItems = listInput.size();

	//Create surface for each remaining option
	for (int iii = 0; iii < numberOfItems; iii++)
	{
		labels.push_back(cocos2d::Label::createWithTTF(strings[iii], font, fontSize, cocos2d::Size::ZERO, cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP));
		labels.at(iii)->setTextColor(textColor);
		labels.at(iii)->setBlendFunc(cocos2d::BlendFunc::ALPHA_NON_PREMULTIPLIED);
		addChild(labels.at(iii));
		labels.at(iii)->setAnchorPoint(cocos2d::Vec2(0, 0));
		labels.at(iii)->setPosition(0, (-iii * scale * letterHeight) - iii * spacing);
	}

	float top = labels.at(0)->getPositionY();
	float bottom = labels.at(numberOfItems - 1)->getPositionY() - letterHeight;
	realHeight = top - bottom;

	//Find the longest line
	int currentLine = 0;
	longestLine = 0;
	int width1 = 0;
	int width2 = 0;

	for (; currentLine < numberOfItems; currentLine++)
	{
		width1 = labels.at(currentLine)->getContentSize().width;
		width2 = labels.at(longestLine)->getContentSize().width;

		if (width1 > width2)
			longestLine = currentLine;
	}

	realWidth = labels.at(longestLine)->getContentSize().width;
	scaledWidth = realWidth / scale;
	scaledHeight = realHeight / scale;

	//Set to current location
	setPosition(pos.x, pos.y);

	if (textIsCentered)
		CenterText();

	return;
}

void nrgList::ChangeList(std::string input)
{
	std::vector<std::string> listInput{ input };
	
	//Clear/remove previous objects
	strings.clear();
	labels.clear();
	removeAllChildren();

	strings = listInput;

	//Count total number of options
	numberOfItems = listInput.size();

	//Create surface for each remaining option
	for (int iii = 0; iii < numberOfItems; iii++)
	{
		labels.push_back(cocos2d::Label::createWithTTF(strings[iii], font, fontSize, cocos2d::Size::ZERO, cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP));
		labels.at(iii)->setTextColor(textColor);
		addChild(labels.at(iii));
		labels.at(iii)->setAnchorPoint(cocos2d::Vec2(0, 0));
		labels.at(iii)->setPosition(0, (-iii * scale * letterHeight) - iii * spacing);
	}

	float top = labels.at(0)->getPositionY();
	float bottom = labels.at(numberOfItems - 1)->getPositionY() - letterHeight;
	realHeight = top - bottom;

	//Find the longest line
	int currentLine = 0;
	longestLine = 0;
	int width1 = 0;
	int width2 = 0;

	for (; currentLine < numberOfItems; currentLine++)
	{
		width1 = labels.at(currentLine)->getContentSize().width;
		width2 = labels.at(longestLine)->getContentSize().width;

		if (width1 > width2)
			longestLine = currentLine;
	}

	realWidth = labels.at(longestLine)->getContentSize().width;
	scaledWidth = realWidth / scale;
	scaledHeight = realHeight / scale;

	//Set to current location
	setPosition(pos.x, pos.y);

	if (textIsCentered)
		CenterText();

	return;
}

void nrgList::addEvents()
{
	//Set flag for events added
	eventsAdded = true;

	//Create listener for touch events
	touchListener = cocos2d::EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);

	//Create lister for keyboard events
	keyboardListener = cocos2d::EventListenerKeyboard::create();
	keyboardListener->setEnabled(true);

	//On touch, check to see if sprite was touched
	touchListener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		ToggleOn(false);
		finishedReading = true;
		return true;	
	};

	//Key press event handling
	keyboardListener->onKeyPressed = [=](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		HandleKeyPress(keyCode, event);
	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(touchListener, 1);
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(keyboardListener, 1);
}

void nrgList::HandleKeyPress(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
		case cocos2d::EventKeyboard::KeyCode::KEY_ENTER:
			ToggleOn(false);
			finishedReading = true;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
			ToggleOn(false);
			finishedReading = true;
			break;
	}
	return;
}

void nrgList::setPositionX(float x)
{
	//Set proxy location x coordinate
	pos.x = x * scale;

	//Set all labels to x coordinate
	for (int iii = 0; iii < numberOfItems; iii++)
		labels.at(iii)->setPositionX(pos.x);

	if (textIsCentered)
		CenterText();

	return;

}
void nrgList::setPositionY(float y)
{
	//Set proxy location y coordinate
	pos.y = y * scale;

	//Set all labels to x coordinate
	for (int iii = 0; iii < numberOfItems; iii++)
		labels.at(iii)->setPositionY(pos.y - (iii * scale * letterHeight) - iii * spacing);

	return;
}
void nrgList::setPosition(float x, float y)
{
	//Set proxy location x and y coordinates
	pos.x = x * scale;
	pos.y = y * scale;

	//Set all labels to x/y coordinate
	for (int iii = 0; iii < numberOfItems; iii++)
		labels.at(iii)->setPosition(pos.x, pos.y - (iii * scale * letterHeight) - iii * spacing);

	if (textIsCentered)
		CenterText();

	return;
}

float nrgList::getPositionX()
{
	return pos.x / scale;
}
float nrgList::getPositionY()
{
	return pos.y / scale;
}
cocos2d::Vec2 nrgList::getPosition()
{
	return pos;
}

void nrgList::Center(float x, float y)
{
	auto glview = cocos2d::Director::getInstance()->getOpenGLView();
	float screenWidth = scale * glview->getDesignResolutionSize().width;
	float screenHeight = scale * glview->getDesignResolutionSize().height;
	y *= scale;
	x *= scale;

	pos.y = (screenHeight / 2) + (realHeight / 2) + y;
	pos.x = (screenWidth / 2) - (realWidth / 2) + x;

	for (int iii = 0; iii < numberOfItems; iii++)
		labels[iii]->setPosition(pos.x, pos.y - (iii * scale * letterHeight) - iii * spacing);

	if (textIsCentered)
		CenterText();

	return;
}

void nrgList::SetRightSide(int x)
{
	pos.x = x * scale - realWidth;

	for (int iii = 0; iii < numberOfItems; iii++)
		labels.at(iii)->setPositionX(pos.x - getContentSize().width);

	if (textIsCentered)
		CenterText();

	return;
}

int nrgList::GetRightSide()
{
	return pos.x / scale + scaledWidth;
}

void nrgList::SetTop(int y)
{
	//Scale position
	pos.y = y * scale;

	//Set top for first label
	labels.at(0)->setPositionY(pos.y - labels.at(0)->getContentSize().height);

	//Set remaining labels accordingly
	for (int iii = 1; iii < numberOfItems; iii++)
		labels.at(iii)->setPositionY(labels.at(iii - 1)->getPositionY() - labels.at(iii)->getContentSize().height - spacing);

	return;
}

int nrgList::GetTop()
{
	return pos.y / scale + scaledHeight;
}

void nrgList::SetBottom(int y)
{
	//Scale position
	pos.y = y * scale;

	//Set last option
	labels.at(numberOfItems - 1)->setPositionY(pos.y);

	//Stack previous options on top of each other
	for (int iii = numberOfItems - 2; iii >= 0; iii--)
		labels.at(iii)->setPositionY(labels.at(iii + 1)->getPositionY() + labels.at(iii + 1)->getContentSize().height + spacing);
}

int nrgList::GetBottom()
{
	return pos.y / scale;
}

int nrgList::GetLetterHeight()
{
	return letterHeight;
}

int nrgList::GetScaledWidth()
{
	return scaledWidth;
}

int nrgList::GetScaledHeight()
{
	return scaledHeight;
}

int nrgList::GetRealWidth()
{
	return realWidth;
}

int nrgList::GetRealHeight()
{
	return realHeight;
}

//Return whether the list has been read
bool nrgList::IsRead()
{
	return finishedReading;
}

void nrgList::CenterText()
{
	for (int iii = 0; iii < numberOfItems; iii++)
		labels.at(iii)->setPositionX(pos.x + realWidth / 2 - labels.at(iii)->getContentSize().width / 2);

	textIsCentered = true;

	return;
}

cocos2d::Label * nrgList::GetItem(int item)
{
	return labels.at(item);
}

int nrgList::GetNumberOfItems()
{
	return numberOfItems;
}

void nrgList::ToggleOn(bool value)
{
	//Turn on/off touch and keyboard listeners
	if(touchListener)
		touchListener->setEnabled(value);
	if(keyboardListener)
		keyboardListener->setEnabled(value);

	//Turn on/off all label visibility
	setVisible(value);

	return;

}
void nrgList::ToggleTouch(bool value)
{
	if(touchListener)
		touchListener->setEnabled(value);
	return;
}
void nrgList::ToogleKeyboard(bool value)
{
	if(keyboardListener)
		keyboardListener->setEnabled(value);
	return;
}

void nrgList::AddToScrollView(cocos2d::ui::ScrollView * scrollViewInput)
{
	scrollView = scrollViewInput;

	//Make sure object isn't already a child of another object
	if (getParent() == NULL)
		scrollView->addChild(this);

	//Set to true so touch events track touch correctly based  on container offset
	partOfScrollView = true;
	
	return;
}

void nrgList::onExit()
{
	cocos2d::Node::onExit();
	return;
}

nrgList::~nrgList()
{

	if(touchListener)
		cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(touchListener);
	if(keyboardListener)
		cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(keyboardListener);

	touchListener = NULL;
	keyboardListener = NULL;
}
