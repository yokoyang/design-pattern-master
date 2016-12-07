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

bool Settings::Init()
{
	if (!Layer::Init())
	{
		return false;
	}
	auto VisibleSize = Director::GetInstance()->GetVisibleSize();

	auto bk = Sprite::Create(SETTING_PAGE);
	bk->SetScale(VisibleSize.width / bk->GetContentSize().width, VisibleSize.height / bk->GetContentSize().height);
	bk->SetPosition(VisibleSize / 2);
	AddChild(bk);

	auto settings_Menu = Menu::Create();

	auto MusicText = Label::CreateWithTTF(MUSIC, SETTING_FONT, 40);
	MusicText->SetColor(Color3B::BLACK);
	auto MusicItem = MenuItemLabel::Create(MusicText);
	MusicItem->SetAnchorPoint(Vec2(0, 0));

	auto ModeText = Label::CreateWithTTF(MODE, SETTING_FONT, 40);
	ModeText->SetColor(Color3B::BLACK);
	auto ModeItem = MenuItemLabel::Create(ModeText, [](Ref* sender){
	});
	ModeItem->SetAnchorPoint(Vec2(0, 0));

	auto DifficultyText = Label::CreateWithTTF(DIFFICULTY, SETTING_FONT, 40);
	DifficultyText->SetColor(Color3B::BLACK);
	auto DifficultyItem = MenuItemLabel::Create(DifficultyText, [](Ref* sender){
	});
	DifficultyItem->SetAnchorPoint(Vec2(0, 0));


	auto BackText = Label::CreateWithTTF(BACK, SETTING_FONT, 40);
	BackText->SetColor(Color3B::BLACK);
	auto BackItem = MenuItemLabel::Create(BackText, [](Ref* sender){
		auto scene = HelloWorld::CreateScene();
		auto transitionscene = TransitionCrossFade::Create(2, scene);
		Director::GetInstance()->ReplaceScene(transitionscene);
	});
	BackItem->SetAnchorPoint(Vec2(0, 0));

	settings_Menu->AddChild(MusicItem); settings_Menu->AddChild(ModeItem);
	settings_Menu->AddChild(DifficultyItem); settings_Menu->AddChild(BackItem);
	settings_Menu->alignItemsVerticallyWithPadding(50);
	settings_Menu->SetAnchorPoint(Vec2(0, 0));
	settings_Menu->SetPosition(50, VisibleSize.height / 2);

	AddChild(settings_Menu);

	auto slider = Slider::Create();
	slider->loadBarTexture(SLIDER);
	slider->loadSlidBallTextures(SLIDER_BALL, SLIDER_BALL, "");
	//slider->loadProgressBarTexture();
	slider->SetAnchorPoint(Vec2(1, 0));
	slider->SetPosition(Vec2(VisibleSize.width - 50, MusicItem->GetPositionY() + settings_Menu->GetPositionY()));
	slider->setPercent(50);
	slider->addEventListener(CC_CALLBACK_2(Settings::SliderEvent, this));
	AddChild(slider);

	percentage = Label::CreateWithTTF("50%", SETTING_FONT, 40);
	percentage->SetColor(Color3B::BLACK);
	percentage->SetPosition(convertToWorldSpace(Vec2(slider->GetPosition().x-150,slider->GetPosition().y - 20)));
	AddChild(percentage);


	auto ModeSelection = Label::CreateWithTTF(NORMAL_MODE, SETTING_FONT, 40);
	ModeSelection->SetColor(Color3B::BLACK);
	ModeSelection->SetAnchorPoint(Vec2(1, 0));
	ModeSelection->SetPosition(Vec2(VisibleSize.width - 50, ModeItem->GetPositionY() + settings_Menu->GetPositionY()));
	AddChild(ModeSelection);

	auto DifficultySelection = Label::CreateWithTTF(EASY, SETTING_FONT, 40);
	DifficultySelection->SetColor(Color3B::BLACK);
	DifficultySelection->SetAnchorPoint(Vec2(1, 0));
	DifficultySelection->SetPosition(Vec2(VisibleSize.width - 50, DifficultyItem->GetPositionY() + settings_Menu->GetPositionY()));
	AddChild(DifficultySelection);

	auto listener = EventListenerTouchOneByOne::Create();
	listener->onTouchBegan = [ModeSelection](Touch* t, Event *e){
		if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation()))
		{
			if (ModeSelection->getString() == NORMAL_MODE)
			{
				ModeSelection->setString(DUAL_MODE);
				GameScene::SetPlayerNumber(2);
			}
			else if (ModeSelection->getString() == DUAL_MODE)
			{
				ModeSelection->setString(TRIPLE_MODE);
				GameScene::SetPlayerNumber(3);
			}
			else if (ModeSelection->getString() == TRIPLE_MODE)
			{
				ModeSelection->setString(NORMAL_MODE);
				GameScene::SetPlayerNumber(4);
			}
		}
		return true;
	};
	Director::GetInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, ModeSelection);



	auto listener1 = EventListenerTouchOneByOne::Create();
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
	Director::GetInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, DifficultySelection);



	return true;

}

Scene* Settings::CreateScene()
{
	auto scene = Scene::Create();
	auto layer = Settings::Create();
	scene->AddChild(layer);
	return scene;
}


void Settings::SliderEvent(Ref* pSender, Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(pSender);
		int Volumepercentage = slider->getPercent();
		CocosDenshion::SimpleAudioEngine::GetInstance()->setBackgroundMusicVolume(static_cast<float>(Volumepercentage) / 100);

		
		char a[4];
		sprintf(a, "%d", Volumepercentage);
		percentage->setString(std::string(a)+"%");
	}
}