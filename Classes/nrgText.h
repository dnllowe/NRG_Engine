#pragma once
#include "pch.h"

//Forward declaration for nrgTimer
class nrgTimer;

class nrgText : public cocos2d::Node
{
public:
	//Create nrgText. NOTE: anchor point for nrgText is TOP LEFT
	static nrgText* create(const std::string textInput, const std::string fontFilepath, int fontSize = 12, int width = 240, int xCoord = 0, int yCoord = 0, cocos2d::Color3B color = cocos2d::Color3B::BLACK, cocos2d::TextHAlignment hAlignment = cocos2d::TextHAlignment::LEFT);
	~nrgText();

	//Change label string
	void setString(std::string string);

	//Get label string
	std::string getString();

	//Change text color
	void ChangeColor(cocos2d::Color3B color);

	//Recreate text at different size
	void ChangeTextSize(int size);

	//Return pointer to label
	cocos2d::Label* GetLabel();

	//Override FadeOut function so that it calls on label and not node
	void FadeOut(float time);
	
	//Center text on screen with offset x and y
	void Center(int offsetX = 0, int offsetY = 0);

	//Render all text at once
	void ShowAll();

	//Crawl text instead of rendering all at once
	void Crawl(int crawlIntervalInput);

	//Allow text to be controlled by enabling eventListener for touch/keyboard/mouse events
	virtual void addEvents();

	//What to do on first touch
	virtual void TouchBegan();

	//Enables/disables keyboard input for sprite (DISABLED by default)
	void ToggleKeyboard(bool);

	//Check whether input indicates all text read
	bool IsFinishedReading();

	//Set status of finished reading
	void SetFinishedReading(bool);

	//Enables/disables touch input for sprite (ENABLED by default)
	void ToggleTouch(bool);

	//Enables/disables listeners and visibility
	void ToggleOn(bool);

	//Handle key press events
	void HandleKeyPress(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	//Handle key release events
	void HandleKeyRelease(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void setPosition(float x, float y);

	//Sets right side of sprite to coordinate
	void SetRightSide(int x);

	//Return Right Side coordinate (x coordinate + width)
	int GetRightSide();

	//Sets bottom of sprite to coordinate
	void SetBottom(int y);

	//Return Bottom coordinate (y coordinate - height)
	int GetBottom();

	//Get scaled width
	int GetScaledWidth();

	//Get scaled height
	int GetScaledHeight();

	//Get real width
	int GetRealWidth();

	//Get real height
	int GetRealHeight();

	//Get custom scale factor
	float GetScale();
	
	//Return text color
	cocos2d::Color3B GetTextColor();

	//Set center x coordinate at x
	void SetCenter(int x = 0, int y = 0);

	//Set center x coordinate at x
	void SetCenterX(int x = 0);

	//Set center y coordinate at y
	void SetCenterY(int y = 0);

	//Set center x coordinate at x
	int GetCenterX(int x = 0);

	//Set center y coordinate at y
	int GetCenterY(int y = 0);

	//Inserts object into scrollview. Necessary to get correct touch coordinates
	void AddToScrollView(cocos2d::ui::ScrollView* scrollView);

	//Turns off touch and keyboard listeners
	virtual void onExit();

protected:
	nrgText(std::string textInput, std::string fontFilepathInput, int fontSizeInput, int widthInput = 0, cocos2d::Color3B colorInput = cocos2d::Color3B::BLACK, cocos2d::TextHAlignment hAlignmentInput = cocos2d::TextHAlignment::LEFT); //Default constructor is protected. USE create
	cocos2d::Label* label = NULL;
	cocos2d::Color3B textColor; //Color of text
	std::string fontFilepath;
	int fontSize;
	cocos2d::TextHAlignment hAlignment;
	std::string textString; //String for text
	std::string displayString; //Which letters of string to currently display
	int currentLetter = 0; //Current position of displayString letter from textString
	float scale; //How much to scale up font size to account for auto-scaling design resolution size
	float maxWidth; //Max width before text line breaks to new line
	float letterWidth; //Width of average letter
	float letterHeight; //Height of average letter
	int numberOfLines; //Number of text lines
	float scaledHeight;
	float scaledWidth;
	float realWidth;
	float realHeight;

	bool finishedReading = false; //Whether user has provided input that they are done reading the text
	bool showingAll = false; //Whether all letters have been displayed yet
	bool finishedCrawling = false; //Whether text has finished crawling and full string is displaying
	int crawlInterval; //How often to crawl text (in ms)
	bool crawlIntervalSet = false; //Whether crawl speed needs to be set
	nrgTimer crawlTimer; //Controls speed of crawling text

	cocos2d::EventListenerTouchOneByOne* touchListener = NULL; //Touch event listener
	cocos2d::EventListenerKeyboard* keyboardListener = NULL; //Keyboard event listener
	bool eventsAdded = false; //Whether events were added to the sprite object
	bool partOfScrollView = false; //Whether object is in scroll view container
	cocos2d::ui::ScrollView* scrollView = NULL;
};

