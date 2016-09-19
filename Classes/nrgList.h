#pragma once
#include "pch.h"
class nrgList : public cocos2d::Node
{
public:
	static nrgList* create(std::vector<std::string> listInput, std::string fontFile = NULL, int fontSizeInput = 10, int spacingInput = 0, cocos2d::Color3B textColorInput = cocos2d::Color3B::BLACK);
	static nrgList* create(std::string input = "", std::string fontFile = NULL, int fontSizeInput = 10, int spacingInput = 0, cocos2d::Color3B textColorInput = cocos2d::Color3B::BLACK);
	void ChangeList(std::vector<std::string> listInput);
	void ChangeList(std::string input = "");

	void addEvents(); //Add touch events
	void HandleKeyPress(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event); //Handle key presses for menu items

	void Center(float x = 0, float y = 0); //Centers menu items on screen
	void setPositionX(float x); //Set x position for all labels
	void setPositionY(float y); //Set y position for all labels
	void setPosition(float x, float y); //Set x and y position for all labels
	float getPositionX(); //Return proxy x coordinate
	float getPositionY(); //Return proxy y coordinate
	cocos2d::Vec2 getPosition(); //Return proxy x and y coordinates
	void CenterText(); //Align text labels left, centered, or right

	//Get the Cocos2D label from the vector of items
	cocos2d::Label* GetItem(int item);
	int GetNumberOfItems();

	//Sets right side of sprite to coordinate
	void SetRightSide(int x);

	//Return Right Side coordinate (x coordinate + width)
	int GetRightSide();

	//Sets top of sprite to coordinate
	void SetTop(int y);

	//Return Top coordinate (y coordinate - height)
	int GetTop();

	//Sets bottom of sprite to coordinate
	void SetBottom(int y);

	//Return Bottom coordinate (y coordinate - height)
	int GetBottom();

	//Return letter height
	int GetLetterHeight();

	//Get scaled width
	int GetScaledWidth();

	//Get scaled height
	int GetScaledHeight();

	//Get real width
	int GetRealWidth();

	//Get real height
	int GetRealHeight();

	//Return whether the list has been read
	bool IsRead();

	void ToggleOn(bool value); //Turn on/off menu and all labels
	void ToggleTouch(bool value); //Turn touch listener on/off
	void ToogleKeyboard(bool value); //Turn keyboard listener on/off

	void AddToScrollView(cocos2d::ui::ScrollView* scrollView); //Inserts object into scrollview. Necessary to get correct touch coordinates
	void onExit(); //Release touch and keyboard listener

	~nrgList();

protected:
	nrgList(std::vector<std::string> listInput, std::string fontFile = NULL, int fontSizeInput = 10, int spacingInput = 0, cocos2d::Color3B textColorInput = cocos2d::Color3B::BLACK);
	nrgList();

	cocos2d::EventListenerTouchOneByOne* touchListener = NULL; //Touch event listener
	cocos2d::EventListenerKeyboard* keyboardListener = NULL; //Keyboard event listener
	bool eventsAdded = false; //Whether event listeners were added or not

	cocos2d::Vec2 pos; //Proxy vector for position of menu items
	
	std::vector<cocos2d::Label*> labels;
	std::vector<std::string> strings; //Manages vector of string options
	std::string font; //Location of font file used to render text
	int fontSize = 0; //Size of font for labels
	float scale = 1; //Scales the text so that it appears correctly on different size screens
	int spacing = 0;
	int numberOfItems; //Total number of options in list
	bool textIsCentered = false; //Whether to center align text when rendering

	bool finishedReading = false; //Whether the player has provided input that they have finishd reading
	float letterWidth; //Width per character
	float letterHeight; //Her per character
	
	float scaledHeight;
	float scaledWidth;
	float realWidth;
	float realHeight;

	int longestLine; //Value of longest line in array
	cocos2d::Color3B textColor; //Color of non-selected text

	bool partOfScrollView = false; //Whether object is in scroll view container
	cocos2d::ui::ScrollView* scrollView = NULL;
};

