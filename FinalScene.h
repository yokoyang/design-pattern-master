#pragma once
#include<cocos2d.h>
#include"HelloWorldScene.h"
USING_NS_CC;

// End the game
class FinalScene:public Layer
{
public:

	//Constructor and destructor
	FinalScene();
	~FinalScene();
	virtual bool Init();
	Create_FUNC(FinalScene);

	//Final status to show whether the player has won or lost
	static int status;
};

