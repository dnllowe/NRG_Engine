#ifndef  _NRG_SPRITE_H_
#define  _NRG_SPRITE_H_

#pragma once
#include "pch.h"

class nrgTimer;

class nrgSprite : public cocos2d::Sprite
{
public:
	
	~nrgSprite();

	//Initialize Sprite from batch using spriteframes in batch (png) using cache (plist) and initial frame (filename)
	static nrgSprite* create(cocos2d::SpriteBatchNode* batch, std::string frameFile, bool alias = true);

	//Initialize Sprite using filename
	static nrgSprite* create(std::string frameFile, bool alias = true);

	//Get filename for default frame
	virtual std::string GetDefaultFrame();

	//Sets currentAnimation for nrgSprite
	virtual void SetCurrentAnimation(cocos2d::Animation* animation);

	//Enable eventListener for touch/keyboard/mouse events
	virtual void addEvents();

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

	//Enables/disables keyboard input for sprite (DISABLED by default)
	virtual void ToggleKeyboard(bool);

	//Enables/disables touch input for sprite (ENABLED by default)
	virtual void ToggleTouch(bool);

	//Enable/disable visibility and event listeners
	virtual void ToggleEnabled(bool);
	
	//Check if sprite was touched
	virtual bool WasTouched(bool resetTouch = true);

	//Check if touch is enabled
	virtual bool IsTouchEnabled();

	//Get last touch location
	virtual  cocos2d::Vec2 GetLastTouchLocation();

	//Handle key press events
	virtual void HandleKeyPress(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	//Handle key release events
	virtual void HandleKeyRelease(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	//Change fixed priority of keyboard listener
	virtual void ChangeKeyboardListenerPriority(int);

	//Change fixed priority of touch listener
	virtual void ChangeTouchListenerPriority(int);

	//Stops all current actions/animations and animates current animation action during scene. Repeats forever by default
	virtual void Animate(bool repeatForever = true);

	//Initialize properties of physicsBody
	virtual void InitPhysics();

	//Set physics body material (density, friction, restitution)
	virtual void SetPhysicsMaterial(float density, float friction, float restitution);

	//Set physics-based velocity
	virtual void SetPhysicsVelocity(float velocityX = 0, float velocityY = 0);

	//Sets right side of sprite to coordinate
	virtual void SetRightSide(int x);

	//Return Right Side coordinate (x coordinate + width)
	virtual int GetRightSide(); 

	//Sets top of sprite to coordinate
	virtual void SetTop(int y);

	//Return Top coordinate (y coordinate + height)
	virtual int GetTop(); 

	//Centers sprite on screen with x and y offset
	virtual void Center(int offsetX = 0, int offsetY = 0);

	//Get width of sprite (scaled)
	virtual int GetWidth();

	//Get height of sprite (scaled)
	virtual int GetHeight();

	//Set center x coordinate at x
	virtual void SetCenter(int x = 0, int y = 0);

	//Set center x coordinate at x
	virtual void SetCenterX(int x = 0);

	//Set center y coordinate at y
	virtual void SetCenterY(int y = 0);

	//Set center x coordinate at x
	virtual int GetCenterX(int x = 0);

	//Set center y coordinate at y
	virtual int GetCenterY(int y = 0);

	//Move from current position by xValue and yValue
	virtual void Move(float xValue = 0, float yValue = 0);

	//Fade sprite layers in over specified amount of time
	virtual void FadeIn(float value);

	//Fade sprite layers out over specified amount of time. Set visibility after fade out to true or false
	virtual void FadeOut(float value);

	//Return whether sprite is already fading in or out
	virtual bool IsFading();

	//Set opacity of all sprite layers
	virtual void setOpacity(float value);

	//Get opacity for sprite layers
	virtual GLubyte getOpacity();

	//Inserts object into scrollview. Necessary to get correct touch coordinates
	void AddToScrollView(cocos2d::ui::ScrollView* scrollView); 

	//Turns off touch and keyboard listeners
	virtual void onExit();

	nrgTimer sTimer;

protected:
	nrgSprite(); //Default Constructor is protected. USE create

	std::string defaultFrame;

	//The current animation sequence to run
	cocos2d::Animation* currentAnimation = NULL;

	//Touch event listener
	cocos2d::EventListenerTouchOneByOne* touchListener = NULL;

	//Keyboard event listener
	cocos2d::EventListenerKeyboard* keyboardListener = NULL;

	int state = 0; //Determines state of object for animation, actions, and game logic
	int speedX = 0; 
	int speedY = 0;
	bool eventsAdded = false; //Whether events were added to the sprite object
	bool physicsAdded = false; //Whether physics body was added
	bool isFading = false; //Whether sprite is in process of fading in or out
	bool touchEnabled = false; //Whether touch is enabled
	bool wasTouched = false; //Whether sprite was touched
	bool partOfScrollView = false; //Whether object is in scroll view container
	cocos2d::ui::ScrollView* scrollView = NULL;
	cocos2d::Vec2 touchLocation; //Keeps track of touch coordinates
};

#endif
