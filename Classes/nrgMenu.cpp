#include "pch.h"
#include "nrgMenu.h"

nrgMenu * nrgMenu::create(std::vector<std::string> listInput, std::string fontFile, int limitInput, int fontSizeInput, int spacingInput, cocos2d::Color3B textColor1Input, cocos2d::Color3B textColor2Input, bool highlightFirstOption)
{
	nrgMenu* menu = new nrgMenu(listInput, fontFile, limitInput, fontSizeInput, spacingInput, textColor1Input, textColor2Input, highlightFirstOption);
	menu->autorelease();
	return menu;
}

nrgMenu * nrgMenu::create(std::string listInput, std::string fontFile, int limitInput, int fontSizeInput, int spacingInput, cocos2d::Color3B textColor1Input, cocos2d::Color3B textColor2Input, bool highlightFirstOption)
{
	std::vector<std::string> input{ listInput };
	nrgMenu* menu = new nrgMenu(input, fontFile, limitInput, fontSizeInput, spacingInput, textColor1Input, textColor2Input, highlightFirstOption);
	menu->autorelease();
	return menu;
}

nrgMenu::nrgMenu(std::vector<std::string> listInput, std::string fontFile, int limitInput, int fontSizeInput, int spacingInput, cocos2d::Color3B textColor1Input, cocos2d::Color3B textColor2Input, bool highlightFirstOption)
{
	font = fontFile;
	fontSize = fontSizeInput;
	spacing = spacingInput;
	selection = 0;
	newSelection = 0;
	textColor1 = textColor1Input;
	textColor2 = textColor2Input;
	list = listInput;
	limit = limitInput - 1; //Subtract one to make array code cleaner
	setAnchorPoint(cocos2d::Vec2(0, 0));

	auto glview = cocos2d::Director::getInstance()->getOpenGLView();

	//Adjust font size for actual frame size
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
	numberOfOptions = list.size();

	//Get dimensions

	//Create temporary label to get letter width
	cocos2d::Label* tempLabel = cocos2d::Label::createWithTTF("M", fontFile, fontSize, cocos2d::Size::ZERO, cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP);
	letterWidth = tempLabel->getContentSize().width * (1 / scale);
	letterHeight = tempLabel->getContentSize().height * (1 / scale);

	//Make first option highlighted by default
    option.push_back(cocos2d::Label::createWithTTF(list[0], font, fontSize, cocos2d::Size::ZERO, cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP));
	if(highlightFirstOption)
		option[0]->setColor(textColor2Input);
	else
		option[0]->setColor(textColor1Input);

	addChild(option[0]);
	option[0]->setAnchorPoint(cocos2d::Vec2(0, 0));
	option[0]->setPosition(0, 0);

	//Create surface for each remaining option
	for (int iii = 1; iii < numberOfOptions; iii++)
	{
		option.push_back(cocos2d::Label::createWithTTF(list[iii], font, fontSize, cocos2d::Size::ZERO, cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP));
		option[iii]->setColor(textColor1Input);
		addChild(option[iii]);
		option[iii]->setAnchorPoint(cocos2d::Vec2(0, 0));
		option[iii]->setPosition(0, (-iii * scale * letterHeight) - iii * spacing);
	}

	float top = option[0]->getPositionY();
	float bottom = option[numberOfOptions - 1]->getPositionY() - letterHeight;
	realHeight = top - bottom;

	//Find the longest line
	int currentLine = 0;
	longestLine = 0;
	int width1 = 0;
	int width2 = 0;

    for (; currentLine < numberOfOptions; currentLine++)
	{
		width1 = option[currentLine]->getContentSize().width; 
		width2 = option[longestLine]->getContentSize().width;

		if (width1 > width2)
			longestLine = currentLine;
	}

	realWidth = option[longestLine]->getContentSize().width;
	scaledWidth = realWidth / scale;
	scaledHeight = realHeight / scale;

	pos.x = 0;
	pos.y = 0;

	//Create touch and keyboard listeners
	addEvents();
}

void nrgMenu::ChangeMenu(std::vector<std::string> listInput, int limitInput, bool highlightFirstOption)
{
	//Clear/remove previous objects
	list.clear();
	option.clear();
	removeAllChildren();

	list = listInput;
	limit = limitInput - 1; //Subtract one to make array code cleaner

	//Count total number of options
	numberOfOptions = list.size();

	//Make first option highlighted by default
	option.push_back(cocos2d::Label::createWithTTF(list[0], font, fontSize, cocos2d::Size::ZERO, cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP));
	if (highlightFirstOption)
		option[0]->setColor(textColor2);
	else
		option[0]->setColor(textColor1);

	addChild(option[0]);
	option[0]->setAnchorPoint(cocos2d::Vec2(0, 0));
	option[0]->setPosition(0, 0);

	//Create surface for each remaining option
	for (int iii = 1; iii < numberOfOptions; iii++)
	{
		option.push_back(cocos2d::Label::createWithTTF(list[iii], font, fontSize, cocos2d::Size::ZERO, cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP));
		option[iii]->setColor(textColor1);
		addChild(option[iii]);
		option[iii]->setAnchorPoint(cocos2d::Vec2(0, 0));
		option[iii]->setPosition(0, (-iii * scale * letterHeight) - iii * spacing);
	}

	float top = option[0]->getPositionY();
	float bottom = option[numberOfOptions - 1]->getPositionY() - letterHeight;
	realHeight = top - bottom;

	//Find the longest line
	int currentLine = 0;
	longestLine = 0;
	int width1 = 0;
	int width2 = 0;

	for (; currentLine < numberOfOptions; currentLine++)
	{
		width1 = option[currentLine]->getContentSize().width;
		width2 = option[longestLine]->getContentSize().width;

		if (width1 > width2)
			longestLine = currentLine;
	}

	realWidth = option.at(longestLine)->getContentSize().width;
	scaledWidth = realWidth / scale;
	scaledHeight = realHeight / scale;

	//Set to current position
	setPosition(pos.x, pos.y);

	if (textIsCentered)
		CenterText();

	return;
}

void nrgMenu::ChangeMenu(std::string input, int limitInput, bool highlightFirstOption)
{
	std::vector<std::string> listInput{ input };

	//Clear/remove previous objects
	list.clear();
	option.clear();
	removeAllChildren();

	list = listInput;
	limit = limitInput - 1; //Subtract one to make array code cleaner

	//Count total number of options
	numberOfOptions = list.size();

	//Make first option highlighted by default
	option.push_back(cocos2d::Label::createWithTTF(list[0], font, fontSize, cocos2d::Size::ZERO, cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP));
	if (highlightFirstOption)
		option[0]->setColor(textColor2);
	else
		option[0]->setColor(textColor1);

	addChild(option[0]);
	option[0]->setAnchorPoint(cocos2d::Vec2(0, 0));
	option[0]->setPosition(0, 0);

	//Create surface for each remaining option
	for (int iii = 1; iii < numberOfOptions; iii++)
	{
		option.push_back(cocos2d::Label::createWithTTF(list[iii], font, fontSize, cocos2d::Size::ZERO, cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP));
		option[iii]->setColor(textColor1);
		addChild(option[iii]);
		option[iii]->setAnchorPoint(cocos2d::Vec2(0, 0));
		option[iii]->setPosition(0, (-iii * scale * letterHeight) - iii * spacing);
	}

	float top = option[0]->getPositionY();
	float bottom = option[numberOfOptions - 1]->getPositionY() - letterHeight;
	realHeight = top - bottom;

	//Find the longest line
	int currentLine = 0;
	longestLine = 0;
	int width1 = 0;
	int width2 = 0;

	for (; currentLine < numberOfOptions; currentLine++)
	{
		width1 = option[currentLine]->getContentSize().width;
		width2 = option[longestLine]->getContentSize().width;

		if (width1 > width2)
			longestLine = currentLine;
	}

	realWidth = option.at(longestLine)->getContentSize().width;
	scaledWidth = realWidth / scale;
	scaledHeight = realHeight / scale;

	//Set to current position
	setPosition(pos.x, pos.y);

	if (textIsCentered)
		CenterText();

	return;
}

void nrgMenu::addEvents()
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
		//Record touch location
		cocos2d::Vec2 touchLocation = touch->getLocation();

		//Scale touch so that it accurately recognizes scaled menu text items
		touchLocation.x *= scale;
		touchLocation.y *= scale;

		if (partOfScrollView)
		{
			touchLocation.y += scrollView->getInnerContainerPosition().y;
			touchLocation.x += scrollView->getInnerContainerPosition().x;
		}

		//Check every label to see if it was touched
		for (int iii = 0; iii < numberOfOptions; iii++)
		{
			//If label was touched, make it the current selection and change to selection color
			cocos2d::Rect rect;

			rect.setRect(option[iii]->getPositionX(), option[iii]->getPositionY(), option[iii]->getContentSize().width, option[iii]->getContentSize().height);
			if (rect.containsPoint(touchLocation))
			{
				option[iii]->setColor(textColor2);
				selection = iii;
				itemPressed = true;
			}
			else
				option.at(iii)->setColor(textColor1); //If not selected, set text to default color
		}

		if (itemPressed)
		{
			itemPressed = false;
			return true; // to indicate that we have consumed it.
		}
		else
			return false;
	};

	//Code for what to do when touch is released
	touchListener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{	
		//Check to see if touch ended on selected item, if not--ignore and don't select anything
		cocos2d::Rect rect;
		rect.setRect(option.at(selection)->getPositionX(), option.at(selection)->getPositionY(), option.at(selection)->getContentSize().width, option.at(selection)->getContentSize().height);
		cocos2d::Vec2 touchReleaseLocation = touch->getLocation();
		//Scale touch so that it accurately recognizes scaled menu text items
		touchReleaseLocation.x *= scale;
		touchReleaseLocation.y *= scale;
		cocos2d::Vec2 touchStartLocation = touch->getStartLocation();
		//Scale touch so that it accurately recognizes scaled menu text items
		touchStartLocation.x *= scale;
		touchStartLocation.y *= scale;

		if (partOfScrollView)
		{
			touchStartLocation.y -= scrollView->getInnerContainerPosition().y;
			touchStartLocation.x -= scrollView->getInnerContainerPosition().x;
			touchReleaseLocation.y -= scrollView->getInnerContainerPosition().y;
			touchReleaseLocation.x -= scrollView->getInnerContainerPosition().x;
		}

		if (rect.containsPoint(touchReleaseLocation) && rect.containsPoint(touchStartLocation))
			isSelectionComplete = true;
		option.at(selection)->setColor(textColor1);
	};

	//Key press event handling
	keyboardListener->onKeyPressed = [=](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		HandleKeyPress(keyCode, event);
	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(touchListener, 1);
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(keyboardListener, 1);
}

void nrgMenu::HandleKeyPress(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	return;
}

void nrgMenu::setPositionX(float x)
{
	//Set proxy location x coordinate
	pos.x = x * scale;

	//Set all labels to x coordinate
	for (int iii = 0; iii < numberOfOptions; iii++)
		option.at(iii)->setPositionX(pos.x);
	
	if (textIsCentered)
		CenterText();

	return;

}
void nrgMenu::setPositionY(float y)
{
	//Set proxy location y coordinate
	pos.y = y * scale;

	//Set all labels to x coordinate
	for (int iii = 0; iii < numberOfOptions; iii++)
		option.at(iii)->setPositionY(pos.y - (iii * scale * letterHeight) - iii * spacing);

	return;
}
void nrgMenu::setPosition(float x, float y)
{
	//Set proxy location x and y coordinates
	pos.x = x * scale;
	pos.y = y * scale;

	//Set all labels to x/y coordinate
	for (int iii = 0; iii < numberOfOptions; iii++)
		option.at(iii)->setPosition(pos.x, pos.y - (iii * scale * letterHeight) - iii * spacing);

	if (textIsCentered)
		CenterText();

	return;
}

float nrgMenu::getPositionX()
{
	return pos.x / scale;
}
float nrgMenu::getPositionY()
{
	return pos.y / scale;
}
cocos2d::Vec2 nrgMenu::getPosition()
{
	return pos;
}

void nrgMenu::Center(float x, float y)
{
	auto glview = cocos2d::Director::getInstance()->getOpenGLView();
	float screenWidth = scale * glview->getDesignResolutionSize().width;
	float screenHeight = scale * glview->getDesignResolutionSize().height;
	y *= scale;
	x *= scale;

	pos.y = (screenHeight / 2) + (realHeight / 2) + y;
	pos.x = (screenWidth / 2) - (realWidth / 2) + x;

	for (int iii = 0; iii < numberOfOptions; iii++)
		option[iii]->setPosition(pos.x, pos.y - (iii * scale * letterHeight) - iii * spacing);

	if (textIsCentered)
		CenterText();

	return;
}

void nrgMenu::SetRightSide(int x)
{
	pos.x = x * scale - realWidth;

	for (int iii = 0; iii < numberOfOptions; iii++)
		option.at(iii)->setPositionX(pos.x - getContentSize().width);

	if (textIsCentered)
		CenterText();

	return;
}

int nrgMenu::GetRightSide()
{
	return pos.x / scale +scaledWidth;
}

void nrgMenu::SetTop(int y)
{
	//Scale position
	pos.y = y * scale;

	//Set top for first label
	option.at(0)->setPositionY(pos.y - option.at(0)->getContentSize().height);

	//Set remaining labels accordingly
	for (int iii = 1; iii < numberOfOptions; iii++)
		option.at(iii)->setPositionY(option.at(iii - 1)->getPositionY() - option.at(iii)->getContentSize().height - spacing);

	return;
}

int nrgMenu::GetTop()
{
	return pos.y / scale + scaledHeight;
}

void nrgMenu::SetBottom(int y)
{
	//Scale position
	pos.y = y * scale;

	//Set last option
	option.at(numberOfOptions - 1)->setPositionY(pos.y);

	//Stack previous options on top of each other
	for (int iii = numberOfOptions - 2; iii >= 0; iii--)
		option.at(iii)->setPositionY(option.at(iii + 1)->getPositionY() + option.at(iii + 1)->getContentSize().height + spacing);
}

int nrgMenu::GetBottom()
{
	return pos.y / scale;
}

int nrgMenu::GetScaledWidth()
{
	return scaledWidth;
}

int nrgMenu::GetScaledHeight()
{
	return scaledHeight;
}

int nrgMenu::GetRealWidth()
{
	return realWidth;
}

int nrgMenu::GetRealHeight()
{
	return realHeight;
}

void nrgMenu::CenterText()
{
	for (int iii = 0; iii < numberOfOptions; iii++)
		option[iii]->setPositionX(pos.x + realWidth / 2 - option[iii]->getContentSize().width / 2);

	textIsCentered = true;

	return;
}
void nrgMenu::SelectionUp()
{
	if (newSelection > 0)
		newSelection--;
	else if (newSelection == 0)
		newSelection = numberOfOptions - 1;

	return;
}

void nrgMenu::SelectionDown()
{
	if (newSelection < numberOfOptions - 1)
		newSelection++;
	else if (selection == numberOfOptions - 1)
		newSelection = 0;
	return;
}

bool nrgMenu::IsSelectionMade()
{
	return isSelectionComplete;
}

int nrgMenu::GetConfirmedSelection(bool saveSelection)
{
	if (isSelectionComplete)
	{
		isSelectionComplete = saveSelection; //reset selection status to nothing chosen
		return selection;
	}

	else
		return -1;
}

void nrgMenu::SetSelection(int value)
{
	option[value]->setColor(textColor2);
	selection = value;
	return;
}

void nrgMenu::HighlightLastSelection()
{
	option[selection]->setColor(textColor2);
	return;
}

cocos2d::Label * nrgMenu::GetItem(int item)
{
	return option.at(item);
}

int nrgMenu::GetNumberOfItems()
{
	return numberOfOptions;
}

nrgMenu* nrgMenu::GetPreviousMenu()
{
	return previousMenu;
}

void nrgMenu::SetPreviousMenu(nrgMenu*& menu)
{
	previousMenu = menu;
	return;
}

void nrgMenu::ChangeTextColor1(cocos2d::Color3B color, bool highlightOption)
{
	textColor1 = color;
	for (int iii = 0; iii < option.size(); iii++)
		option[iii]->setColor(textColor1);

	if (highlightOption)
		option[selection]->setColor(textColor2);

	return;
}

void nrgMenu::ChangeTextColor2(cocos2d::Color3B color, bool highlightOption)
{
	textColor2 = color;

	if(highlightOption)
		option[selection]->setColor(textColor2);

	return;
}

void nrgMenu::ToggleOn(bool value)
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
void nrgMenu::ToggleTouch(bool value)
{
	if(touchListener)
		touchListener->setEnabled(value);
	return;
}
void nrgMenu::ToogleKeyboard(bool value)
{
	if(keyboardListener)
		keyboardListener->setEnabled(value);
	return;
}

void nrgMenu::AddToScrollView(cocos2d::ui::ScrollView * scrollViewInput)
{
	scrollView = scrollViewInput;

	//Make sure object isn't already a child of another object
	if (getParent() == NULL)
		scrollView->addChild(this);

	//Set to true so touch events track touch correctly based  on container offset
	partOfScrollView = true;

	return;
}

void nrgMenu::onExit()
{
	cocos2d::Node::onExit();
	return;
}
nrgMenu::~nrgMenu()
{
	if(touchListener)
		cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(touchListener);
	if(keyboardListener)
		cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(keyboardListener);

	touchListener = NULL;
	keyboardListener = NULL;
}
