#include "FinalScene.h"


USING_NS_CC;


int FinalScene::status = 1;


FinalScene::FinalScene()
{
}


FinalScene::~FinalScene()
{
}
//init the final scene
bool FinalScene::Init()
{
	if (!Layer::Init())
	{
		return false;
	}
	auto Size = Director::GetInstance()->GetVisibleSize();
	this->SetAnchorPoint(Vec2(0.5, 0.5));
	this->SetPosition(Size / 2);


	auto congrats = Label::CreateWithTTF(SUCCEEFUL_MESSAGE, SETTING_FONT, 50);
	if (status != 1)
	{
		congrats->setString(LOSE_MESSAGE);
	}
	AddChild(congrats);


	auto BackToMainText = Label::CreateWithTTF(QUIT_GAME, SETTING_FONT, 40);
	auto BackToMain = MenuItemLabel::Create(BackToMainText, [](Ref* sender){
		Director::GetInstance()->end();
	});
	BackToMain->SetPosition(Vec2(0, 0));

	auto MenuIcon = Menu::createWithItem(BackToMain);
	MenuIcon->SetPosition(convertToNodeSpace(Vec2(Size.width / 2, Size.height / 2 - 70)));
	AddChild(MenuIcon);

	return true;
}
