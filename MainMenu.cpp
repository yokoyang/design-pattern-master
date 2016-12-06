#include "MainMenu.h"
#include<cocos2d.h>
#include"GameSceneScene.h"
#include "Settings.h"

USING_NS_CC;


MainMenu::MainMenu()
{
}


MainMenu::~MainMenu()
{
}

bool MainMenu::Init()
{
	if (!Menu::Init())
	{
		return false;
	}
	//Start game button
	auto StartGameText = Sprite::Create("Start Button.png");
	auto StartGameItem = MenuItemSprite::Create(StartGameText, StartGameText, StartGameText,[this](Ref* sender){
		auto scene = GameScene::CreateScene();
		auto transitionScene = TransitionCrossFade::Create(0.1f, scene);
		Director::GetInstance()->ReplaceScene(transitionScene);
	});
	//End button
	auto EndGameText = Sprite::Create("Quit Button.png");
	auto EndGameItem = MenuItemSprite::Create(EndGameText, EndGameText, EndGameText,[](Ref* sender){
		Director::GetInstance()->End();
	});

	//Enter Settings
	auto SettingsText =Sprite::Create("Settings Button.png");
	auto SettingsItem = MenuItemSprite::Create(SettingsText, SettingsText, SettingsText,[](Ref* sender){
		auto scene = Settings::CreateScene();
		auto transitionScene = TransitionPaGeturn::Create(2, scene, false);
		Director::GetInstance()->ReplaceScene(transitionScene);
	});

	AddChild(StartGameItem); AddChild(EndGameItem); AddChild(SettingsItem);
	AlignItemsVertically();
	return true;
}

