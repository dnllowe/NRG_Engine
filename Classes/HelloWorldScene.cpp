#pragma once
#include "HelloWorldScene.h"
#include "pch.h"
#include "AudioEngine.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

	auto director = cocos2d::Director::getInstance();
	auto glview = director->getOpenGLView();

	int width = glview->getDesignResolutionSize().width;
	int height = glview->getDesignResolutionSize().height;
	cocos2d::Vec2 center = cocos2d::Vec2(width / 2, height / 2);
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(width - closeItem->getContentSize().width, closeItem->getContentSize().height);
	

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

    // position the label on the center of the screen
    label->setPosition(Vec2(width/2, height - label->getContentSize().height));
	label->setLineBreakWithoutSpace(true);
	label->setMaxLineWidth(50);

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
	auto bg = Sprite::create("testImage.png");

	//Resize background for device
	nrgFunctions::ResizeForDevice(bg);
	
    // position the sprite on the center of the screen
    bg->setPosition(Vec2(width/2, height/2));

    // add the sprite as a child to this layer
    this->addChild(bg, 0);


	//Load sprite batch and cache
	cocos2d::SpriteBatchNode* batch = NULL;
	cocos2d::SpriteFrameCache* cache = cocos2d::SpriteFrameCache::getInstance();

	
	nrgFunctions::CreateSpriteBatch("Man_Red_Shirt", batch, cache);
	
	//Test nrgSprite from batch and physics
	nrgSprite* nSprite = nrgSprite::create(batch, "Man_Red_Shirt_1.png");
	nSprite->setPosition(300, 300);
	nSprite->setScale(5);
	nSprite->InitPhysics();
	
	nrgSprite* nSprite2 = nrgSprite::create(batch, "Man_Red_Shirt_2.png");
	nSprite2->InitPhysics();
	nSprite2->setPosition(150, 200);
	nSprite2->setScale(5);
	
	nrgSprite* nSprite4 = nrgSprite::create(batch, "Man_Red_Shirt_3.png");
	nSprite4->setPosition(250, 250);
	nSprite4->setScale(5);
	nSprite4->InitPhysics();
	
	nrgSprite* nSprite5 = nrgSprite::create(batch, "Man_Red_Shirt_4.png");
	nSprite5->setPosition(0, 150);
	nSprite5->setScale(5);
	nSprite5->InitPhysics();
	
	nrgSprite* nSprite3 = nrgSprite::create(batch, "Man_Red_Shirt_5.png");
	nSprite3->setPosition(200, 0);
	nSprite3->setScale(5);
	nSprite3->InitPhysics();

	this->addChild(batch);

	auto ground = cocos2d::Sprite::create("red_square.png");
	ground->setScaleX(100);
	auto groundWidth = ground->getContentSize().width;
	auto groundHeight = ground->getContentSize().height;
	
	auto groundBody = cocos2d::PhysicsBody::createBox(Size(groundWidth * ground->getScaleX(), groundHeight));
	groundBody->setDynamic(false);

	ground->setPhysicsBody(groundBody);
	
	this->addChild(ground);

	//Test nrgSprite from cache
	nrgSprite* blocky = nrgSprite::create(cache, "blocky_blue_4.png");
	blocky->setScale(4);
	blocky->InitPhysics();
	blocky->setPosition(200, 300);
	this->addChild(blocky);

	//Test nrgBox
	nrgBox* box = nrgBox::create(250, 100, 10, 0, 0, cocos2d::Color4F::BLACK, cocos2d::Color4F::WHITE);
	box->Center();
	//addChild(box);

	//Test nrgText
	text = nrgTextBox::create("Testing nrgText to make sure the line breaks work effectively", "fonts/Marker Felt.ttf", 24, 250);
	addChild(text, 1);
	text->Center();
	text->setPosition(200, 270);
	
	scheduleUpdate();

    return true;
}

void HelloWorld::update(float fl)
{
	text->Crawl(50);
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
