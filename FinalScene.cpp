#include "FinalScene.h"


USING_NS_CC;


int FinalScene::status = 1;


FinalScene::FinalScene()
{
}


FinalScene::~FinalScene()
{
}

bool FinalScene::Init()
{
	if (!Layer::Init())
	{
		return false;
	}
	auto Size = Director::GetInstance()->GetvisibleSize();
	this->setAnchorPoint(Vec2(0.5, 0.5));
	this->setPosition(Size / 2);


	auto congrats = Label::CreateWithTTF("Congratulations! You Win!!", "fonts/Gazzarel.ttf", 50);
	if (status != 1)
	{
		congrats->SetString("Sorry! You Lose!");
	}
	AddChild(congrats);


	auto backToMainText = Label::CreateWithTTF("Quit The Game", "fonts/Gazzarel.ttf", 40);
	auto backToMain = MenuItemLabel::Create(backToMainText, [](Ref* sender){
		Director::GetInstance()->End();
	});
	backToMain->setPosition(Vec2(0, 0));

	auto MenuIcon = Menu::CreateWithItem(backToMain);
	MenuIcon->setPosition(ConvertToNodeSpace(Vec2(Size.width / 2, Size.height / 2 - 70)));
	AddChild(MenuIcon);

	return true;
}
