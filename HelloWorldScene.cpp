#include "HelloWorldScene.h"
#include "MainMenu.h"
#include<SimpleAudioEngine.h>

USING_NS_CC;


Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);
	
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	Sprite* background = Sprite::create(START_PAGE);
	background->setScale(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
	background->setAnchorPoint(Vec2(0.5, 0.5));
	background->setPosition(visibleSize / 2);

	addChild(background);

	auto mainmenu = MainMenu::create();
	mainmenu->setPosition(visibleSize / 2);
	addChild(mainmenu);

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BACKGROUND_MUSIC);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(GOD_BLESS_MUSIC);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(UNINJECT_MUSIC);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(REVENGE_MUSIC);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(DONOT_BLAME_MUSIC);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(UNBELIEVE_MUSIC);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(BUY_MUSIC);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(PAY_RENT_MUSIC);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(HEPPY_MUSIC);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(GIVE_MORE_MUSIC);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(RELEX_MUSIC);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(HEPPY_MUSIC2);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(UNHEPPY_MUSIC);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(UNHEPPY_MUSIC2);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(UNHEPPY_MUSIC3);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(TIGER_MUSIC);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(UNHEPPY_MUSIC4);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(THREATEN_MUSIC);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(BEG_MUSIC);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(RANDOM_MUSCI);

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BACKGROUND_MUSIC, true);
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
	

	developer = Label::createWithTTF(DEVELOPER_MESSAGE, DEVELOPER_MESSAGE_FONT, 40);
	developer->setAnchorPoint(Vec2(0, 0));
	developer->setPosition(Vec2(20,20));
	
	addChild(developer);
	schedule(schedule_selector(HelloWorld::timerDeveloper), 3.0f);
	
	return true; 
}

void HelloWorld::timerDeveloper(float dt)
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


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
