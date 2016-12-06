#pragma once
#pragma warning(disable:4996)
#include"cocos2d.h"
#include"cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

//Adds a toast to remind players
class Toast:public LayerColor
{
public:
	//Add toast
	static void AddToast(Node*, Point, std::string, float);

	//Remove the toast
	void Removetoast(Node* node);
};