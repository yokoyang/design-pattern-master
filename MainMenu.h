#pragma once
#pragma warning(disable:4996)
#include<cocos2d.h>
USING_NS_CC;

class MainMenu:public Menu
{
public:
	//Constructor and destructor
	MainMenu();
	~MainMenu();
	virtual bool init();
	CREATE_FUNC(MainMenu);
};

