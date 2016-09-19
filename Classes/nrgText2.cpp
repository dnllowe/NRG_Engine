#include "pch.h"
#include "nrgText.h"


nrgText::nrgText(std::string textInput, std::string fontFilepathInput, int fontSizeInput, int widthInput, cocos2d::Color4B color, cocos2d::TextHAlignment hAlignmentInput)
{
	//Set textString
	textString = textInput;
	fontFilepath = fontFilepathInput;
	fontSize = fontSizeInput;
	hAlignment = hAlignmentInput;
	textColor = color;
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

	//Create the cocos2d Label*
	label = cocos2d::Label::createWithTTF(textInput, fontFilepath, fontSize, cocos2d::Size::ZERO, hAlignment, cocos2d::TextVAlignment::TOP);

	//Create temporary label to get letter width
	cocos2d::Label* tempLabel = cocos2d::Label::createWithTTF("M", fontFilepath, fontSize, cocos2d::Size::ZERO, hAlignment, cocos2d::TextVAlignment::TOP);
	letterWidth = tempLabel->getContentSize().width * (1 / scale);
	//Get letter height
	letterHeight = tempLabel->getContentSize().height * (1 / scale);

	//Set max width of line (if not set, set to max screen width, minus two letters)
	if (widthInput == 0)
	{
		auto glview = cocos2d::Director::getInstance()->getOpenGLView();
		int screenWidth = glview->getDesignResolutionSize().width;
		
		screenWidth -= 2 * letterWidth * (1 / scale);
		maxWidth = screenWidth;
	}

	else
		maxWidth = widthInput;

	//Set label parameters
	label->setMaxLineWidth(scale * maxWidth); //Must take scale into account for line width
	numberOfLines = label->getStringNumLines();
	label->setTextColor(color);
	label->setBlendFunc(cocos2d::BlendFunc::ALPHA_NON_PREMULTIPLIED);

	realWidth = label->getContentSize().width;
	realHeight = label->getContentSize().height;
	scaledWidth = realWidth / scale;
	scaledHeight = realHeight / scale;

	//Add label to nrgText object
	addChild(label);

	//Set anchor point to top left so that scrolling text moves downwards
	setAnchorPoint(cocos2d::Vec2(0, 1));
	label->setAnchorPoint(cocos2d::Vec2(0, 1)); 

	return;
}

nrgText* nrgText::create(std::string textInput, std::string fontFilepath, int fontSize, int widthInput, int xCoord, int yCoord, cocos2d::Color4B color, cocos2d::TextHAlignment hAlignment)
{
	nrgText* text = new nrgText(textInput, fontFilepath, fontSize, widthInput, color, hAlignment);
	text->setPosition(xCoord, yCoord);
	text->autorelease();
	return text;
}

void nrgText::ShowAll()
{
	if (!showingAll)
	{
		crawlTimer.Stop(); //Stop crawl timer if it's running
		showingAll = true; //Let program know we are now showing all text
		setVisible(true); //Make sure visiblity is on
		label->setString(textString); //Show entire text string
	}

	return;
}

void nrgText::Crawl(int crawlIntervalInput)
{
	if (textString.size() == 0)
		return;

	//If we haven't rendered all letters yet
	if (!finishedCrawling)
	{
		crawlTimer.Start();

		//Set crawl speed and begin crawlTimer
		if (!crawlIntervalSet)
		{
			//Add events once text is active
			if(!eventsAdded)
				addEvents();
			crawlInterval = crawlIntervalInput;
			crawlIntervalSet = true;
			displayString.push_back(textString.at(currentLetter));
			currentLetter++;
			label->setString(displayString);
			setVisible(true);
		}

		//Once the appropriate amount of time has passed, render next letter from textString
		if (crawlTimer.GetElapsedTime() >= crawlInterval)
		{	
			displayString.push_back(textString.at(currentLetter));
			label->setString(displayString);
			currentLetter++;
			crawlTimer.Reset();
		}

		if (currentLetter == textString.size())
		{
			finishedCrawling = true;
			showingAll = true;
		}
	}

	return;
}

void nrgText::addEvents()
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
			TouchBegan();
			return true; // to indicate that we have consumed it.
	};

	//Key press event handling
	keyboardListener->onKeyPressed = [=](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		HandleKeyPress(keyCode, event);
	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(touchListener, 1);
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(keyboardListener, 1);
}

void nrgText::TouchBegan()
{
	//If not yet showing all text, show all text on first touch
	if (!showingAll)
		ShowAll();

	//If already showing all text, disable visiblity and input
	else if (showingAll)
	{
		setVisible(false);
		ToggleKeyboard(false);
		ToggleTouch(false);
		finishedReading = true;
	}
	return;
}

void nrgText::ToggleKeyboard(bool value)
{
	keyboardListener->setEnabled(value);
	return;
}

bool nrgText::IsFinishedReading()
{
	return finishedReading;
}

void nrgText::SetFinishedReading(bool value)
{
	finishedReading = value;
	return;
}

void nrgText::ToggleTouch(bool value)
{
	touchListener->setEnabled(value);
	return;
}

void nrgText::ToggleOn(bool value)
{
	setVisible(value);

	if (eventsAdded)
	{
		ToggleTouch(value);
		ToggleKeyboard(value);
	}

	return;
}

void nrgText::HandleKeyPress(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_ENTER:
		//If not yet showing all text, show all text on first touch
		if (!showingAll)
			ShowAll();

		//If already showing all text, disable visiblity and input
		else if (showingAll)
		{
			setVisible(false);
//			label->setVisible(false);
			ToggleKeyboard(false);
			ToggleTouch(false);
			finishedReading = true;
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
		//If not yet showing all text, show all text on first touch
		if (!showingAll)
			ShowAll();

		//If already showing all text, disable visiblity and input
		else if (showingAll)
		{
			setVisible(false);
//			label->setVisible(false);
			ToggleKeyboard(false);
			ToggleTouch(false);
			finishedReading = true;
		}
		break;
	}
	return;
}

void nrgText::HandleKeyRelease(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	return;
}

void nrgText::setPosition(float x, float y)
{
	Node::setPosition(x, y);
	return;
}

void nrgText::SetRightSide(int x)
{
	setPositionX(x - scaledWidth);
	return;
}

int nrgText::GetRightSide()
{
	return getPositionX() + scaledWidth;
}

void nrgText::SetBottom(int y)
{
	setPositionY(y + scaledHeight);
	return;
}

int nrgText::GetBottom()
{
	return getPositionY() - scaledHeight;
}

int nrgText::GetScaledWidth()
{
	return scaledWidth;
}

int nrgText::GetScaledHeight()
{
	return scaledHeight;
}

int nrgText::GetRealWidth()
{
	return realWidth;
}

int nrgText::GetRealHeight()
{
	return realHeight;
}

float nrgText::GetScale()
{
	return scale;
}

cocos2d::Color4B nrgText::GetTextColor()
{
	return textColor;
}

void nrgText::SetCenter(int x, int y)
{
	setPosition(x - scaledWidth / 2, y - scaledHeight / 2);
	return;
}

void nrgText::SetCenterX(int x)
{
	setPositionX(x - scaledWidth / 2);
	return;
}

void nrgText::SetCenterY(int y)
{
	setPositionY(y - scaledHeight / 2);
	return;
}

int nrgText::GetCenterX(int x)
{
	return getPositionX() + scaledWidth / 2;
}

int nrgText::GetCenterY(int y)
{
	return getPositionY() + scaledHeight / 2;
}

void nrgText::AddToScrollView(cocos2d::ui::ScrollView * scrollViewInput)
{
	scrollView = scrollViewInput;

	//Make sure object isn't already a child of another object
	if (getParent() == NULL)
		scrollView->addChild(this);

	//Set to true so touch events track touch correctly based  on container offset
	partOfScrollView = true;
	
	return;
}

//Center box on screen
void nrgText::Center(int offsetX, int offsetY)
{
	//Get screen width and height
	auto director = cocos2d::Director::getInstance();
	int width = director->getOpenGLView()->getDesignResolutionSize().width;
	int height = director->getOpenGLView()->getDesignResolutionSize().height;

	//Center the image
	Node::setPosition(cocos2d::Vec2(width / 2 - (1 / scale) * label->getContentSize().width / 2 + offsetX, height / 2 + (1 / scale) * label->getContentSize().height / 2 + offsetY));

	return;
}

void nrgText::setString(std::string string)
{
	//Get new string
	label->setString(string);
	textString = string;

	//Reset label parameters
	numberOfLines = label->getStringNumLines();
	realWidth = label->getContentSize().width;
	realHeight = label->getContentSize().height;
	scaledWidth = realWidth / scale;
	scaledHeight = realHeight / scale;

	return;
}

std::string nrgText::getString()
{
	return label->getString();
}

void nrgText::ChangeColor(cocos2d::Color4B color)
{
	label->setTextColor(color);
	return;
}

void nrgText::ChangeTextSize(int size)
{
	fontSize = size;
	removeChild(label);
	label = NULL;

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

	//Create the cocos2d Label*
	label = cocos2d::Label::createWithTTF(textString, fontFilepath, fontSize, cocos2d::Size::ZERO, hAlignment, cocos2d::TextVAlignment::TOP);
	label->disableEffect(cocos2d::LabelEffect::OUTLINE);

	//Create temporary label to get letter width
	cocos2d::Label* tempLabel = cocos2d::Label::createWithTTF("M", fontFilepath, fontSize, cocos2d::Size::ZERO, hAlignment, cocos2d::TextVAlignment::TOP);
	letterWidth = tempLabel->getContentSize().width * (1 / scale);
	//Get letter height
	letterHeight = tempLabel->getContentSize().height * (1 / scale);

	//Set label parameters
	label->setMaxLineWidth(scale * maxWidth); //Must take scale into account for line width
	numberOfLines = label->getStringNumLines();
	label->setTextColor(textColor);
	realWidth = label->getContentSize().width;
	realHeight = label->getContentSize().height;
	scaledWidth = realWidth / scale;
	scaledHeight = realHeight / scale;

	//Add label to nrgText object
	addChild(label);

	//Set anchor point to top left so that scrolling text moves downwards
	setAnchorPoint(cocos2d::Vec2(0, 1));
	label->setAnchorPoint(cocos2d::Vec2(0, 1));

	return;
}

cocos2d::Label * nrgText::GetLabel()
{
	return label;
}

void nrgText::FadeOut(float time)
{
	label->runAction(cocos2d::FadeOut::create(time));
	return;
}

void nrgText::onExit()
{
	cocos2d::Node::onExit();
	return;
}

nrgText::~nrgText()
{
	if (touchListener != NULL)
		cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(touchListener);
	if (keyboardListener != NULL)
		cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(keyboardListener);

	touchListener = NULL;
	keyboardListener = NULL;
}