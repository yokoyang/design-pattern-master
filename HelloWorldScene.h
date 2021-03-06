#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#pragma warning(disable:4996)
#include "cocos2d.h"
#include"GameSceneScene.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
private:
	Label* developer = Label::createWithSystemFont(DEVELOPER_MESSAGE, DEVELOPER_MESSAGE_FONT, DEVELOPER_MESSAGE_FONT_SIZE);
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* CreateScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool Init();
    
    // a selector callback
    void MenuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static Create()" method manually
    CREATE_FUNC(HelloWorld);

	void TimerDeveloper(float dt);
	
};

#endif // __HELLOWORLD_SCENE_H__
