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

bool MainMenu::init()
{
	if (!Menu::init())
	{
		return false;
	}
	//Start game button
	auto StartGameText = Sprite::create("Start Button.png");
	auto StartGameItem = MenuItemSprite::create(StartGameText, StartGameText, StartGameText,[this](Ref* sender){
		auto scene = GameScene::createScene();
		auto transitionscene = TransitionCrossFade::create(0.1f, scene);
		Director::getInstance()->replaceScene(transitionscene);
	});
	//End button
	auto EndGameText = Sprite::create("Quit Button.png");
	auto EndGameItem = MenuItemSprite::create(EndGameText, EndGameText, EndGameText,[](Ref* sender){
		Director::getInstance()->end();
	});

	//Enter settings
	auto SettingsText =Sprite::create("Settings Button.png");
	auto SettingsItem = MenuItemSprite::create(SettingsText, SettingsText, SettingsText,[](Ref* sender){
		auto scene = Settings::createScene();
		auto transitionscene = TransitionPageTurn::create(2, scene, false);
		Director::getInstance()->replaceScene(transitionscene);
	});

	addChild(StartGameItem); addChild(EndGameItem); addChild(SettingsItem);
	alignItemsVertically();
	return true;
}

