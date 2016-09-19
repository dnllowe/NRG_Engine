#pragma once
#include "pch.h"

//Forward declaration for nrgTimer
class nrgTimer;

class nrgMenu : public cocos2d::Node
{
public:
	static nrgMenu* create(std::vector<std::string> listInput, std::string fontFile = NULL, int limitInput = 0, int fontSizeInput = 10, int spacing = 0, cocos2d::Color3B textColor1Input = cocos2d::Color3B::BLACK, cocos2d::Color3B textColor2Input = cocos2d::Color3B::YELLOW, bool highlightFirstOption = true);
	static nrgMenu* create(std::string listInput = "", std::string fontFile = NULL, int limitInput = 0, int fontSizeInput = 10, int spacing = 0, cocos2d::Color3B textColor1Input = cocos2d::Color3B::BLACK, cocos2d::Color3B textColor2Input = cocos2d::Color3B::YELLOW, bool highlightFirstOption = true);
	void ChangeMenu(std::vector<std::string> listInput, int limitInput = 0, bool highlightFirstOption = true);
	void ChangeMenu(std::string input = "", int limitInput = 0, bool highlightFirstOption = true);

	void addEvents(); //Add touch events
	void HandleKeyPress(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event); //Handle key presses for menu items
	
	void Center(float x = 0, float y = 0); //Centers menu items on screen
	void setPositionX(float x); //Set x position for all labels
	void setPositionY(float y); //Set y position for all labels
	void setPosition(float x, float y); //Set x and y position for all labels
	float getPositionX(); //Return proxy x coordinate
	float getPositionY(); //Return proxy y coordinate
	cocos2d::Vec2 getPosition(); //Return proxy x and y coordinates

	//Sets right side of sprite to coordinate
	void SetRightSide(int x);

	//Return Right Side coordinate (x coordinate + width)
	int GetRightSide();

	//Sets Top of sprite to coordinate
	void SetTop(int y);

	//Return Top coordinate (y coordinate - height)
	int GetTop();

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

	void CenterText(); //Center align text labels
	
	void SelectionUp(); //Move selected option up
	void SelectionDown(); //Move selected option down
	bool IsSelectionMade(); //Whether selection has been made
	int GetConfirmedSelection(bool saveSelectioin = false); //Return confirmed selected option
	void SetSelection(int value); //Set a highlighted option
	void HighlightLastSelection(); //Keep the last selected item highlighted

	//Get the Cocos2D label from the vector of items
	cocos2d::Label* GetItem(int item);
	int GetNumberOfItems();

	virtual nrgMenu* GetPreviousMenu(); //Returns pointer to previous menu
	virtual void SetPreviousMenu(nrgMenu*& menu); //Sets previous menu	

	void ChangeTextColor1(cocos2d::Color3B, bool highlightOption = false);
	void ChangeTextColor2(cocos2d::Color3B, bool highlightOption = false);

	void ToggleOn(bool value); //Turn on/off menu and all labels
	void ToggleTouch(bool value); //Turn touch listener on/off
	void ToogleKeyboard(bool value); //Turn keyboard listener on/off

	void AddToScrollView(cocos2d::ui::ScrollView* scrollView); //Inserts object into scrollview. Necessary to get correct touch coordinates

	void onExit(); //Release touch and keyboard listener

	~nrgMenu();

protected:
	nrgMenu(std::vector<std::string> listInput, std::string fontFile = NULL, int limitInput = 0, int fontSizeInput = 10, int spacing = 0, cocos2d::Color3B textColor1Input = cocos2d::Color3B::BLACK, cocos2d::Color3B textColor2Input = cocos2d::Color3B::YELLOW, bool highlightFirstOption = true);
	cocos2d::EventListenerTouchOneByOne* touchListener = NULL; //Touch event listener
	cocos2d::EventListenerKeyboard* keyboardListener = NULL; //Keyboard event listener
	bool eventsAdded = false; //Whether event listeners were added or not
	bool itemPressed = false; //Determines whether menu consumed touch or not
	
	cocos2d::Vec2 pos; //Proxy vector for position of menu items
	std::vector<std::string> list; //Manages vector of string options
	std::string font; //Location of font file used to render text
	int fontSize = 0; //Size of font for labels
	int spacing = 0; //How much space between lines
	float scale = 1; //Scales the text so that it appears correctly on different size screens

	bool isDescending; //Sets direction for scrolling menu boxes
	int previousSelection; //Determines when to change limitLow and limitHigh range
	int limit; //Determines maximum amount of menu options to display (0 = all and is default)
	int limitLow; //If not descending (ascending), threshold for when to reset limitLow and limitHigh for menu
	int limitHigh; //If descending, threshold for when to reset limitLow and limitHigh for menu

	int numberOfOptions; //Total number of options in list
	int selection = -1; //Which option is currently highlighted
	int newSelection;
	bool isSelectionComplete = false; //Player has selected an option
	std::vector<cocos2d::Label*> option;

	float letterWidth; //Width per character
	float letterHeight; //Her per character
	float scaledHeight;
	float scaledWidth;
	float realWidth;
	float realHeight;

	int longestLine; //Value of longest line in array
	bool textIsCentered = false; //Whether to center align text when rendering

	cocos2d::Color3B textColor1; //Color of non-selected text
	cocos2d::Color3B textColor2; //Color of selected text

	bool partOfScrollView = false; //Whether object is in scroll view container
	cocos2d::ui::ScrollView* scrollView = NULL;

	nrgMenu* previousMenu = NULL; //Retains information on previous menu. Do not delete in destructor, as this menu will always be an existing menu that gets deleted elsewhere in the program
};

