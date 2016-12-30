#include "MainMenu.h"
#include<cocos2d.h>
#include"GameSceneScene.h"
#include<Settings.h>

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
	auto StartGameText = Sprite::Create(START_BUTTON);
	auto StartGameItem = MenuItemSprite::Create(StartGameText, StartGameText, StartGameText,[this](Ref* sender){
		auto scene = GameScene::CreateScene();
		auto transitionscene = TransitionCrossFade::Create(0.1f, scene);
		Director::GetInstance()->ReplaceScene(transitionscene);
	});
	//End button
	auto EndGameText = Sprite::Create(QUIT_BUTTON);
	auto EndGameItem = MenuItemSprite::Create(EndGameText, EndGameText, EndGameText,[](Ref* sender){
		Director::GetInstance()->end();
	});

	//Enter settings
	auto SettingsText =Sprite::Create(SETTING_BUTTON);
	auto SettingsItem = MenuItemSprite::Create(SettingsText, SettingsText, SettingsText,[](Ref* sender){
		auto scene = Settings::CreateScene();
		auto transitionscene = TransitionPageTurn::Create(2, scene, false);
		Director::GetInstance()->ReplaceScene(transitionscene);
	});

	AddChild(StartGameItem); AddChild(EndGameItem); AddChild(SettingsItem);
	AlignItemsVertically();
	return true;
}

