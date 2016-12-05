#include "FinalScene.h"


USING_NS_CC;


int FinalScene::status = 1;


FinalScene::FinalScene()
{
}


FinalScene::~FinalScene()
{
}

bool FinalScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto Size = Director::getInstance()->getVisibleSize();
	this->setAnchorPoint(Vec2(0.5, 0.5));
	this->setPosition(Size / 2);


	auto congrats = Label::createWithTTF(SUCCEEFUL_MESSAGE, SETTING_FONT, 50);
	if (status != 1)
	{
		congrats->setString(LOSE_MESSAGE);
	}
	addChild(congrats);


	auto BackToMainText = Label::createWithTTF(QUIT_GAME, SETTING_FONT, 40);
	auto BackToMain = MenuItemLabel::create(BackToMainText, [](Ref* sender){
		Director::getInstance()->end();
	});
	BackToMain->setPosition(Vec2(0, 0));

	auto MenuIcon = Menu::createWithItem(BackToMain);
	MenuIcon->setPosition(convertToNodeSpace(Vec2(Size.width / 2, Size.height / 2 - 70)));
	addChild(MenuIcon);

	return true;
}
