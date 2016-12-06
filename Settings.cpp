#include "Settings.h"
#include<cocos2d.h>
#include<ui/CocosGUI.h>
#include "HelloWorldScene.h"
#include<SimpleAudioEngine.h>
#include<string.h>


using namespace ui;
USING_NS_CC;

Settings::Settings()
{
}


Settings::~Settings()
{
}

bool Settings::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto VisibleSize = Director::getInstance()->getVisibleSize();

	auto bk = Sprite::create(SETTING_PAGE);
	bk->setScale(VisibleSize.width / bk->getContentSize().width, VisibleSize.height / bk->getContentSize().height);
	bk->setPosition(VisibleSize / 2);
	addChild(bk);

	auto settings_Menu = Menu::create();

	auto MusicText = Label::createWithTTF(MUSIC, SETTING_FONT, 40);
	MusicText->setColor(Color3B::BLACK);
	auto MusicItem = MenuItemLabel::create(MusicText);
	MusicItem->setAnchorPoint(Vec2(0, 0));

	auto ModeText = Label::createWithTTF(MODE, SETTING_FONT, 40);
	ModeText->setColor(Color3B::BLACK);
	auto ModeItem = MenuItemLabel::create(ModeText, [](Ref* sender){
	});
	ModeItem->setAnchorPoint(Vec2(0, 0));

	auto DifficultyText = Label::createWithTTF(DIFFICULTY, SETTING_FONT, 40);
	DifficultyText->setColor(Color3B::BLACK);
	auto DifficultyItem = MenuItemLabel::create(DifficultyText, [](Ref* sender){
	});
	DifficultyItem->setAnchorPoint(Vec2(0, 0));


	auto BackText = Label::createWithTTF(BACK, SETTING_FONT, 40);
	BackText->setColor(Color3B::BLACK);
	auto BackItem = MenuItemLabel::create(BackText, [](Ref* sender){
		auto scene = HelloWorld::createScene();
		auto transitionscene = TransitionCrossFade::create(2, scene);
		Director::getInstance()->replaceScene(transitionscene);
	});
	BackItem->setAnchorPoint(Vec2(0, 0));

	settings_Menu->addChild(MusicItem); settings_Menu->addChild(ModeItem);
	settings_Menu->addChild(DifficultyItem); settings_Menu->addChild(BackItem);
	settings_Menu->alignItemsVerticallyWithPadding(50);
	settings_Menu->setAnchorPoint(Vec2(0, 0));
	settings_Menu->setPosition(50, VisibleSize.height / 2);

	addChild(settings_Menu);

	auto slider = Slider::create();
	slider->loadBarTexture(SLIDER);
	slider->loadSlidBallTextures(SLIDER_BALL, SLIDER_BALL, "");
	//slider->loadProgressBarTexture();
	slider->setAnchorPoint(Vec2(1, 0));
	slider->setPosition(Vec2(VisibleSize.width - 50, MusicItem->getPositionY() + settings_Menu->getPositionY()));
	slider->setPercent(50);
	slider->addEventListener(CC_CALLBACK_2(Settings::sliderEvent, this));
	addChild(slider);

	percentage = Label::createWithTTF("50%", SETTING_FONT, 40);
	percentage->setColor(Color3B::BLACK);
	percentage->setPosition(convertToWorldSpace(Vec2(slider->getPosition().x-150,slider->getPosition().y - 20)));
	addChild(percentage);


	auto ModeSelection = Label::createWithTTF(NORMAL_MODE, SETTING_FONT, 40);
	ModeSelection->setColor(Color3B::BLACK);
	ModeSelection->setAnchorPoint(Vec2(1, 0));
	ModeSelection->setPosition(Vec2(VisibleSize.width - 50, ModeItem->getPositionY() + settings_Menu->getPositionY()));
	addChild(ModeSelection);

	auto DifficultySelection = Label::createWithTTF(EASY, SETTING_FONT, 40);
	DifficultySelection->setColor(Color3B::BLACK);
	DifficultySelection->setAnchorPoint(Vec2(1, 0));
	DifficultySelection->setPosition(Vec2(VisibleSize.width - 50, DifficultyItem->getPositionY() + settings_Menu->getPositionY()));
	addChild(DifficultySelection);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [ModeSelection](Touch* t, Event *e){
		if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation()))
		{
			if (ModeSelection->getString() == NORMAL_MODE)
			{
				ModeSelection->setString(DUAL_MODE);
				GameScene::setplayernumber(2);
			}
			else if (ModeSelection->getString() == DUAL_MODE)
			{
				ModeSelection->setString(TRIPLE_MODE);
				GameScene::setplayernumber(3);
			}
			else if (ModeSelection->getString() == TRIPLE_MODE)
			{
				ModeSelection->setString(NORMAL_MODE);
				GameScene::setplayernumber(4);
			}
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, ModeSelection);



	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->onTouchBegan = [DifficultySelection](Touch* t, Event *e){
		if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation()))
		{
			if (DifficultySelection->getString() == EASY)
			{
				DifficultySelection->setString(MIDDLE);
				GameScene::set_maptype(2);
			}
			else if (DifficultySelection->getString() == MIDDLE)
			{
				DifficultySelection->setString(DIFFICULT);
				GameScene::set_maptype(3);
			}
			else if (DifficultySelection->getString() == DIFFICULT)
			{
				DifficultySelection->setString(EASY);
				GameScene::set_maptype(1);
			}
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, DifficultySelection);



	return true;

}

Scene* Settings::createScene()
{
	auto scene = Scene::create();
	auto layer = Settings::create();
	scene->addChild(layer);
	return scene;
}


void Settings::sliderEvent(Ref* pSender, Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(pSender);
		int Volumepercentage = slider->getPercent();
		CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(static_cast<float>(Volumepercentage) / 100);

		
		char a[4];
		sprintf(a, "%d", Volumepercentage);
		percentage->setString(std::string(a)+"%");
	}
}