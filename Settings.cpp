#include "Settings.h"
#include<cocos2d.h>
#include"Ui/CocosGUI.h"
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

	auto bk = Sprite::Create("wenli.jpg");
	bk->SetScale(VisibleSize.width / bk->GetContentSize().width, VisibleSize.height / bk->GetContentSize().height);
	bk->SetPosition(VisibleSize / 2);
	AddChild(bk);

	auto Settings_Menu = Menu::Create();

	auto MusicText = Label::CreateWithTTF("Music", "fonts/Gazzarel.TTF",40);
	MusicText->SetColor(Color3B::BLACK);
	auto MusicItem = MenuItemLabel::Create(MusicText);
	MusicItem->SetAnchorPoint(Vec2(0, 0));

	auto ModeText = Label::CreateWithTTF("Mode", "fonts/Gazzarel.TTF", 40);
	ModeText->SetColor(Color3B::BLACK);
	auto ModeItem = MenuItemLabel::Create(ModeText, [](Ref* sender){
	});
	ModeItem->SetAnchorPoint(Vec2(0, 0));

	auto DifficultyText = Label::CreateWithTTF("Difficulty", "fonts/Gazzarel.TTF", 40);
	DifficultyText->SetColor(Color3B::BLACK);
	auto DifficultyItem = MenuItemLabel::Create(DifficultyText, [](Ref* sender){
	});
	DifficultyItem->SetAnchorPoint(Vec2(0, 0));


	auto BackText = Label::CreateWithTTF("Back to Main Menu", "fonts/Gazzarel.TTF", 40);
	BackText->SetColor(Color3B::BLACK);
	auto BackItem = MenuItemLabel::Create(BackText, [](Ref* sender){
		auto scene = HelloWorld::CreateScene();
		auto transitionScene = TransitionCrossFade::Create(2, scene);
		Director::GetInstance()->ReplaceScene(transitionScene);
	});
	BackItem->SetAnchorPoint(Vec2(0, 0));

	Settings_Menu->AddChild(MusicItem); Settings_Menu->AddChild(ModeItem);
	Settings_Menu->AddChild(DifficultyItem); Settings_Menu->AddChild(BackItem);
	Settings_Menu->AlignItemsVerticallyWithPAdding(50);
	Settings_Menu->SetAnchorPoint(Vec2(0, 0));
	Settings_Menu->SetPosition(50, VisibleSize.height / 2);

	AddChild(Settings_Menu);

	auto slider = Slider::Create();
	slider->loadBarTexture("slider.png");
	slider->loadSlidBallTextures("xiaoqiu.png", "xiaoqiu.png", "");
	//slider->loadProgressBarTexture();
	slider->SetAnchorPoint(Vec2(1, 0));
	slider->SetPosition(Vec2(VisibleSize.width - 50, MusicItem->GetPositionY() + Settings_Menu->GetPositionY()));
	slider->SetPercent(50);
	slider->AddEventListener(CC_CALLBACK_2(Settings::SliderEvent, this));
	AddChild(slider);

	percentage=Label::CreateWithTTF("50%", "fonts/Gazzarel.ttf", 40);
	percentage->SetColor(Color3B::BLACK);
	percentage->SetPosition(ConvertToWorldSpace(Vec2(slider->GetPosition().x-150,slider->GetPosition().y - 20)));
	AddChild(percentage);


	auto ModeSelection = Label::CreateWithTTF("Normal Mode", "fonts/Gazzarel.TTF", 40);
	ModeSelection->SetColor(Color3B::BLACK);
	ModeSelection->SetAnchorPoint(Vec2(1, 0));
	ModeSelection->SetPosition(Vec2(VisibleSize.width - 50, ModeItem->GetPositionY() + Settings_Menu->GetPositionY()));
	AddChild(ModeSelection);

	auto DifficultySelection = Label::CreateWithTTF("Easy", "fonts/Gazzarel.TTF", 40);
	DifficultySelection->SetColor(Color3B::BLACK);
	DifficultySelection->SetAnchorPoint(Vec2(1, 0));
	DifficultySelection->SetPosition(Vec2(VisibleSize.width - 50, DifficultyItem->GetPositionY() + Settings_Menu->GetPositionY()));
	AddChild(DifficultySelection);

	auto listener = EventListenerTouchOneByOne::Create();
	listener->onTouchBegan = [ModeSelection](Touch* t, Event *e){
		if (e->GetCurrentTarGet()->GetBoundingBox().ContainsPoint(t->GetLocation()))
		{
			if (ModeSelection->GetString() == "Normal Mode")
			{
				ModeSelection->SetString("Dual");
				GameScene::SetPlayerNumber(2);
			}
			else if (ModeSelection->GetString() == "Dual")
			{
				ModeSelection->SetString("Triple");
				GameScene::SetPlayerNumber(3);
			}
			else if (ModeSelection->GetString() == "Triple")
			{
				ModeSelection->SetString("Normal Mode");
				GameScene::SetPlayerNumber(4);
			}
		}
		return true;
	};
	Director::GetInstance()->GetEventDispatcher()->AddEventListenerWithSceneGraphPriority(listener, ModeSelection);



	auto listener1 = EventListenerTouchOneByOne::Create();
	listener1->onTouchBegan = [DifficultySelection](Touch* t, Event *e){
		if (e->GetCurrentTarGet()->GetBoundingBox().ContainsPoint(t->GetLocation()))
		{
			if (DifficultySelection->GetString() == "Easy")
			{
				DifficultySelection->SetString("Middle");
				GameScene::Set_maptype(2);
			}
			else if (DifficultySelection->GetString() == "Middle")
			{
				DifficultySelection->SetString("Difficult");
				GameScene::Set_maptype(3);
			}
			else if (DifficultySelection->GetString() == "Difficult")
			{
				DifficultySelection->SetString("Easy");
				GameScene::Set_maptype(1);
			}
		}
		return true;
	};
	Director::GetInstance()->GetEventDispatcher()->AddEventListenerWithSceneGraphPriority(listener1, DifficultySelection);



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
		int Volumepercentage = slider->GetPercent();
		CocosDenshion::SimpleAudioEngine::GetInstance()->SetBackgroundMusicVolume(static_cast<float>(Volumepercentage) / 100);

		
		char a[4];
		sprintf(a, "%d", Volumepercentage);
		percentage->SetString(std::string(a)+"%");
	}
}