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


	Sprite* background = Sprite::create("Shanghai.jpg");
	background->setScale(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
	background->setAnchorPoint(Vec2(0.5, 0.5));
	background->setPosition(visibleSize / 2);

	addChild(background);

	auto mainmenu = MainMenu::create();
	mainmenu->setPosition(visibleSize / 2);
	addChild(mainmenu);

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Flo Rida - Whistle.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounding/Godbless.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounding/Nodazhen.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounding/p2_baochou.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounding/p2_bieguaiwo.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounding/p2_buhuiba.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounding/p2_buyit.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounding/p2_buyongzhaole.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounding/p2_deyideyitian.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounding/p2_duogei.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounding/p2_duoxiuxi.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounding/p2_falvzhicai.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounding/p2_hairenjing.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounding/p2_qifurenjia.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounding/p2_qiangqiana.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounding/p2_tiger.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounding/p2_zhenmianmu.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounding/Taisuidongtu.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounding/Xiaobenjingying.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounding/Speaking_00458.wav");

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Flo Rida - Whistle.wav", true);
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
	

	developer = Label::createWithTTF("Rafael Marmalade, Yu Yifan, Yan Xiongbaixue", "fonts/Gothic Flames.ttf", 40);
	developer->setAnchorPoint(Vec2(0, 0));
	developer->setPosition(Vec2(20,20));
	
	addChild(developer);
	schedule(schedule_selector(HelloWorld::timerDeveloper), 3.0f);
	
	return true; 
}

void HelloWorld::timerDeveloper(float dt)
{
	if (developer->getString() == "Rafael Marmalade, Yu Yifan, Yan Xiongbaixue")
	{
		developer->setString("Software Engineering School");

	}
	else
	{
		developer->setString( "Rafael Marmalade, Yu Yifan, Yan Xiongbaixue");
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
