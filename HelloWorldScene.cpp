#include "HelloWorldScene.h"
#include "MainMenu.h"
#include<SimpleAudioEngine.h>

USING_NS_CC;


Scene* HelloWorld::CreateScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::Create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::Create();

    // Add layer as a child to scene
    scene->AddChild(layer);
	
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::Init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::Init() )
    {
        return false;
    }
    
	Size visibleSize = Director::GetInstance()->GetvisibleSize();
	Vec2 origin = Director::GetInstance()->GetVisibleOrigin();


	Sprite* background = Sprite::Create("Shanghai.jpg");
	background->SetScale(visibleSize.width / background->GetContentSize().width, visibleSize.height / background->GetContentSize().height);
	background->setAnchorPoint(Vec2(0.5, 0.5));
	background->setPosition(visibleSize / 2);

	AddChild(background);

	auto mainmenu = MainMenu::Create();
	mainmenu->setPosition(visibleSize / 2);
	AddChild(mainmenu);

	CocosDenshion::SimpleAudioEngine::GetInstance()->PreloadBackgroundMusic("Flo Rida - Whistle.wav");
	//ศฅณýศ฿ำเด๚ย๋
	for (int i = 1; i < 20; i++)
	{
		CocosDenshion::SimpleAudioEngine::GetInstance()->PreloadEffect("Sounding/audio%02d.wav", i);

	}
	

	CocosDenshion::SimpleAudioEngine::GetInstance()->PlayBackgroundMusic("Flo Rida - Whistle.wav", true);
	CocosDenshion::SimpleAudioEngine::GetInstance()->SetBackgroundMusicVolume(0.5);
	

	developer = Label::CreateWithTTF("Rafael Marmalade, Yu Yifan, Yan Xiongbaixue", "fonts/Gothic Flames.ttf", 40);
	developer->setAnchorPoint(Vec2(0, 0));
	developer->setPosition(Vec2(20,20));
	
	AddChild(developer);
	Schedule(schedule_selector(HelloWorld::TimerDeveloper), 3.0f);
	
	return true; 
}

void HelloWorld::TimerDeveloper(float dt)
{
	if (developer->GetString() == "Rafael Marmalade, Yu Yifan, Yan Xiongbaixue")
	{
		developer->SetString("Software Engineering School");

	}
	else
	{
		developer->SetString( "Rafael Marmalade, Yu Yifan, Yan Xiongbaixue");
	}
}


void HelloWorld::MenuCloseCallback(Ref* pSender)
{
#if (CC_TARGet_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGet_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::GetInstance()->End();

#if (CC_TARGet_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
