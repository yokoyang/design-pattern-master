#pragma once
#pragma warning(disable:4996)
#include<cocos2d.h>
#include"ui/CocosGUI.h"
#include"HelloWorldScene.h"
#include<SimpleAudioEngine.h>

USING_NS_CC;
using namespace ui;
class Settings:public Layer
{
public:
	Settings();
	~Settings();
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Settings);
	void sliderEvent(Ref*, Slider::EventType);
private:
	Label* percentage;
};

