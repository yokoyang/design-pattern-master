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
    
	Size visibleSize = Director::GetInstance()->GetVisibleSize();
	Vec2 origin = Director::GetInstance()->GetVisibleOrigin();


	Sprite* background = Sprite::Create("Shanghai.jpg");
	background->SetScale(visibleSize.width / background->GetContentSize().width, visibleSize.height / background->GetContentSize().height);
	background->SetAnchorPoint(Vec2(0.5, 0.5));
	background->SetPosition(visibleSize / 2);

	AddChild(background);

	auto mainmenu = MainMenu::Create();
	mainmenu->SetPosition(visibleSize / 2);
	AddChild(mainmenu);

	CocosDenshion::SimpleAudioEngine::GetInstance()->PreloadBackgroundMusic("Flo Rida - Whistle.wav");
	CocosDenshion::SimpleAudioEngine::GetInstance()->PreloadEffect("Sounding/Godbless.wav");
	CocosDenshion::SimpleAudioEngine::GetInstance()->PreloadEffect("Sounding/Nodazhen.wav");
	CocosDenshion::SimpleAudioEngine::GetInstance()->PreloadEffect("Sounding/p2_baochou.wav");
	CocosDenshion::SimpleAudioEngine::GetInstance()->PreloadEffect("Sounding/p2_bieguaiwo.wav");
	CocosDenshion::SimpleAudioEngine::GetInstance()->PreloadEffect("Sounding/p2_buhuiba.wav");
	CocosDenshion::SimpleAudioEngine::GetInstance()->PreloadEffect("Sounding/p2_buyit.wav");
	CocosDenshion::SimpleAudioEngine::GetInstance()->PreloadEffect("Sounding/p2_buyongzhaole.wav");
	CocosDenshion::SimpleAudioEngine::GetInstance()->PreloadEffect("Sounding/p2_deyideyitian.wav");
	CocosDenshion::SimpleAudioEngine::GetInstance()->PreloadEffect("Sounding/p2_duogei.wav");
	CocosDenshion::SimpleAudioEngine::GetInstance()->PreloadEffect("Sounding/p2_duoxiuxi.wav");
	CocosDenshion::SimpleAudioEngine::GetInstance()->PreloadEffect("Sounding/p2_falvzhicai.wav");
	CocosDenshion::SimpleAudioEngine::GetInstance()->PreloadEffect("Sounding/p2_hairenjing.wav");
	CocosDenshion::SimpleAudioEngine::GetInstance()->PreloadEffect("Sounding/p2_qifurenjia.wav");
	CocosDenshion::SimpleAudioEngine::GetInstance()->PreloadEffect("Sounding/p2_qiangqiana.wav");
	CocosDenshion::SimpleAudioEngine::GetInstance()->PreloadEffect("Sounding/p2_tiger.wav");
	CocosDenshion::SimpleAudioEngine::GetInstance()->PreloadEffect("Sounding/p2_zhenmianmu.wav");
	CocosDenshion::SimpleAudioEngine::GetInstance()->PreloadEffect("Sounding/Taisuidongtu.wav");
	CocosDenshion::SimpleAudioEngine::GetInstance()->PreloadEffect("Sounding/Xiaobenjingying.wav");
	CocosDenshion::SimpleAudioEngine::GetInstance()->PreloadEffect("Sounding/Speaking_00458.wav");

	CocosDenshion::SimpleAudioEngine::GetInstance()->PlayBackgroundMusic("Flo Rida - Whistle.wav", true);
	CocosDenshion::SimpleAudioEngine::GetInstance()->SetBackgroundMusicVolume(0.5);
	

	developer = Label::CreateWithTTF("Rafael Marmalade, Yu Yifan, Yan Xiongbaixue", "fonts/Gothic Flames.ttf", 40);
	developer->SetAnchorPoint(Vec2(0, 0));
	developer->SetPosition(Vec2(20,20));
	
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
