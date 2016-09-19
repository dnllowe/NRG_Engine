#pragma once
class nrgGameData
{
public:
	nrgGameData();
	~nrgGameData();

protected:
	//Instance of Cocos2d UserDefault singleton
	static cocos2d::UserDefault* gameData;
	
};

