#pragma once
#include "pch.h"

class nrgAudio;
//class nrgFileManager;
class nrgMenu;

class nrgScene : public cocos2d::Layer
{
public:
	
	//Allow nrgFunctions access to nrgScene members
	friend class nrgFunctions;
	friend class AppDelegate;

	//ADD TO ALL DERIVED SCENES
	//CREATE_FUNC(nrgScene);

	//Creates scene and initializes necessary variables using Init()
	static cocos2d::Scene* CreateScene();
	
	//Initializes members for scene (runs from CreateScene on instance)
	virtual void Init();

	//Function that runs game loop using CREATE_FUNC from Cocos2dx
	virtual bool init();

	//Creates the "create" function
	CREATE_FUNC(nrgScene);

	//Sets background image of scene to file
	void SetBG(std::string file);

	//Checks whether the game is paused or playing
	bool Paused();

	//Sets paused to true
	void Pause();

	//Sets pause to false
	void Unpause();

	//Returns Vec2 for center of visible screen
	cocos2d::Vec2 GetCenter();

	//Checks whether scene has been initialized
	bool IsInit();

	//Sets initialized to true or false
	void SetInit(bool);

	//Enable eventListener for touch / keyboard / mouse events
	virtual void addEvents();

	//Initialize properties of physicsBody
	virtual void InitPhysics();

	virtual void SetPhysicsVelcoity(float velocityX, float velocityY);

	//Checks for touch events
	virtual void touchEvent(cocos2d::Touch* touch, cocos2d::Vec2 _p);

	//What to do on first touch
	virtual void TouchBegan();

	//What to do when touch ends
	virtual void TouchEnd();

	//What to do if user holds down touch for specified amount of time
	virtual void TouchHold(float time);

	//What to do if user drags touch across screen
	virtual void TouchMove(cocos2d::Touch* touch);

	//Enables/disables keyboard input for scene (DISABLED by default)
	virtual void ToggleKeyboard(bool);

	//Enables/disables touch input for scene (ENABLED by default)
	virtual void ToggleTouch(bool);
    
    //Check if sprite was touched
    virtual bool WasTouched(bool resetTouch = true);
    
    //Check if touch is enabled
    virtual bool IsTouchEnabled();
    
    //Change fixed priority of keyboard listener
    virtual void ChangeKeyboardListenerPriority(int);
    
    //Change fixed priority of touch listener
    virtual void ChangeTouchListenerPriority(int);
    
    //Gets last touch location
	virtual cocos2d::Vec2 GetLastTouchLocation();

	//Sets last touch location (use to pass last touch location from object or sprite to scene)
	virtual void SetLastTouchLocation(cocos2d::Vec2 vec);

	//Handle key press events
	virtual void HandleKeyPress(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	//Handle key release events
	virtual void HandleKeyRelease(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	virtual void onExit();

	~nrgScene();
	
protected:
	cocos2d::Director* director = cocos2d::Director::getInstance(); //Director for game
	cocos2d::GLView* glview = director->getOpenGLView(); //Open GL View
	static cocos2d::UserDefault* gameData; //Saves and loads persistent game data
	nrgAudio* audio = nrgAudio::getInstance(); //Audio player with custom Android audio engine, iOS, and Windows
	CocosDenshion::SimpleAudioEngine* simpleAudio = CocosDenshion::SimpleAudioEngine::getInstance(); //Simple audio engine for all platforms
	cocos2d::FileUtils* fileUtility = cocos2d::FileUtils::getInstance(); //Global Cocos2D file utility for scenes
	//nrgFileManager* fm = nrgFileManager::getInstance(); //Global file manager for scenes
	
    bool testing = false; //Use to turn on other testing variables. If false, no other debug code will activate
    
	cocos2d::Sprite* bg = cocos2d::Sprite::create(); //Sprite for background image
	float SCREEN_WIDTH; //Width of device screen
	float SCREEN_HEIGHT; //Height of device screen
	int Y_ORIGIN; //Bottom of screen (takes any letter bars or other changes into consideration)
	int X_ORIGIN; //Left of screen (takes any letter bars or other changes into consideration) 
	cocos2d::Sprite* LETTERBOX_TOP = NULL; //Image for top letterbox
	cocos2d::Sprite* LETTERBOX_BOTTOM = NULL; //Image for bottom letterbox
	cocos2d::Sprite* LETTERBOX_LEFT = NULL; //Image for left letterbox
	cocos2d::Sprite* LETTERBOX_RIGHT = NULL; //Image for right letterbox
	float HORIZONTAL_LETTERBOX_HEIGHT = 0;
	float HORIZONTAL_LETTERBOX_WIDTH = 0;
	float VERTICAL_LETTERBOX_WIDTH = 0;
	float VERTICAL_LETTERBOX_HEIGHT = 0;

	cocos2d::Vec2 lastTouchLocation;

	float fade = 1; //Used to fade scene clear color in and out (0 = black, 1 = white)

	bool paused = false; //Sets whether scene is paused or playing
	cocos2d::Vec2 center; //Vec2 for center of visible screen
	bool initialized = false; //Checks whether Init() funtion has run or not--can be used to reinitialize variables based on new events

	//Touch event listener
	cocos2d::EventListenerTouchOneByOne* touchListener = NULL;

	//Keyboard event listener
	cocos2d::EventListenerKeyboard* keyboardListener = NULL;

	cocos2d::Vec2 touchLocation; //Keeps track of touch coordinates
	bool physicsAdded = false; //Whether physics body was added
    
    
	int state = 0; //Determines state of object for animation, actions, and game logic
	bool eventsAdded = false; //Whether events were added to the sprite object
    bool touchEnabled = false;
    bool wasTouched = false;
    
	char sz[256]; //Char array for using sprintf

	cocos2d::ui::ScrollView* scrollView = cocos2d::ui::ScrollView::create(); //Controls Native UI scrolling/sliding/inertia effect for scene layer

	nrgTimer sceneTimer; //General timer for scenes
	static std::vector<nrgTimer*> timers; //Vector of timers. Use to pause timers in AppDelegate. Add all timers to be controlled to vector.
	
};

