#pragma once
#pragma warning(disable:4996)
#include<cocos2d.h>
#include"Ui/CocosGUI.h"
#include"HelloWorldScene.h"
#include<SimpleAudioEngine.h>

USING_NS_CC;
using namespace ui;
class Settings:public Layer
{
public:
	Settings();
	~Settings();
	static Scene* CreateScene();
	virtual bool Init();
	Create_FUNC(Settings);
	void SliderEvent(Ref*, Slider::EventType);
private:
	Label* percentAge;
};

