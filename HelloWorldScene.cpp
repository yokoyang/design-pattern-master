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

    // add layer as a child to scene
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


	Sprite* background = Sprite::Create(START_PAGE);
	background->SetScale(visibleSize.width / background->GetContentSize().width, visibleSize.height / background->GetContentSize().height);
	background->SetAnchorPoint(Vec2(0.5, 0.5));
	background->SetPosition(visibleSize / 2);

	AddChild(background);

	auto mainmenu = MainMenu::Create();
	mainmenu->SetPosition(visibleSize / 2);
	AddChild(mainmenu);

	CocosDenshion::SimpleAudioEngine::GetInstance()->preloadBackgroundMusic(BACKGROUND_MUSIC);
	CocosDenshion::SimpleAudioEngine::GetInstance()->preloadEffect(GOD_BLESS_MUSIC);
	CocosDenshion::SimpleAudioEngine::GetInstance()->preloadEffect(UNINJECT_MUSIC);
	CocosDenshion::SimpleAudioEngine::GetInstance()->preloadEffect(REVENGE_MUSIC);
	CocosDenshion::SimpleAudioEngine::GetInstance()->preloadEffect(DONOT_BLAME_MUSIC);
	CocosDenshion::SimpleAudioEngine::GetInstance()->preloadEffect(UNBELIEVE_MUSIC);
	CocosDenshion::SimpleAudioEngine::GetInstance()->preloadEffect(BUY_MUSIC);
	CocosDenshion::SimpleAudioEngine::GetInstance()->preloadEffect(PAY_RENT_MUSIC);
	CocosDenshion::SimpleAudioEngine::GetInstance()->preloadEffect(HEPPY_MUSIC);
	CocosDenshion::SimpleAudioEngine::GetInstance()->preloadEffect(GIVE_MORE_MUSIC);
	CocosDenshion::SimpleAudioEngine::GetInstance()->preloadEffect(RELEX_MUSIC);
	CocosDenshion::SimpleAudioEngine::GetInstance()->preloadEffect(HEPPY_MUSIC2);
	CocosDenshion::SimpleAudioEngine::GetInstance()->preloadEffect(UNHEPPY_MUSIC);
	CocosDenshion::SimpleAudioEngine::GetInstance()->preloadEffect(UNHEPPY_MUSIC2);
	CocosDenshion::SimpleAudioEngine::GetInstance()->preloadEffect(UNHEPPY_MUSIC3);
	CocosDenshion::SimpleAudioEngine::GetInstance()->preloadEffect(TIGER_MUSIC);
	CocosDenshion::SimpleAudioEngine::GetInstance()->preloadEffect(UNHEPPY_MUSIC4);
	CocosDenshion::SimpleAudioEngine::GetInstance()->preloadEffect(THREATEN_MUSIC);
	CocosDenshion::SimpleAudioEngine::GetInstance()->preloadEffect(BEG_MUSIC);
	CocosDenshion::SimpleAudioEngine::GetInstance()->preloadEffect(RANDOM_MUSCI);

	CocosDenshion::SimpleAudioEngine::GetInstance()->playBackgroundMusic(BACKGROUND_MUSIC, true);
	CocosDenshion::SimpleAudioEngine::GetInstance()->setBackgroundMusicVolume(0.5);
	

	developer = Label::CreateWithTTF(DEVELOPER_MESSAGE, DEVELOPER_MESSAGE_FONT, 40);
	developer->SetAnchorPoint(Vec2(0, 0));
	developer->SetPosition(Vec2(20,20));
	
	AddChild(developer);
	schedule(schedule_selector(HelloWorld::TimerDeveloper), 3.0f);
	
	return true; 
}

void HelloWorld::TimerDeveloper(float dt)
{
	if (developer->getString() == DEVELOPER_MESSAGE)
	{
		developer->setString(DEVELOPER_DEPARTMENT_MESSAGE);

	}
	else
	{
		developer->setString(DEVELOPER_MESSAGE);
	}
}


void HelloWorld::MenuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::GetInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
