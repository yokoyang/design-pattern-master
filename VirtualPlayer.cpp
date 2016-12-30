#include "VirtualPlayer.h"
#include "Control.h"
#include "GameSceneScene.h"
#include "Route.h"
#include "Toast.h"
#include "FinalScene.h"
#include "VirtualPlayer.h"

VirtualPlayer::VirtualPlayer()
{
	comeX = -1; comeY = -1;
	_money = 0;
	saveMony = 0;
	_name = nullptr;
	money_string = Label::CreateWithTTF("",SETTING_FONT,20);
	turnMe = false;
	oneRoundend = true;
	stayRounds = 0;
}

VirtualPlayer::~VirtualPlayer()
{
}

bool VirtualPlayer::Init()
{
	if (!Sprite::Init())
	{
		return false;
	}
	return true;
}
//Initaite the VirtualPlayer info
VirtualPlayer* VirtualPlayer::CreateWith(char* name, int tag, SpriteFrame* imag, float& money)
{
	auto temp = Create();
	temp->SetTag(tag);
	temp->InitAnimate();
	temp->SetAnimate();
	temp->Sprite::initWithSpriteFrame(imag);
	temp->_name = Label::CreateWithTTF(name, SETTING_FONT, 20);
	temp->_money = money;
	temp->turnMe = false;
	memset(temp->right_animation, 0, 20);
	memset(temp->down_animation, 0, 20);
	memset(temp->up_animation, 0, 20);
	memset(temp->left_animation, 0, 20);
	return temp;
}




void VirtualPlayer::SetTileSize(float tileWidth, float tileHeigh)
{
	this->tileWidth = tileWidth;
	this->tileHeigh = tileHeigh;
}

//Begin the VirtualPlayer's motion
void VirtualPlayer::Go(std::vector<int>pathrowcopy,std::vector<int>pathcolcopy)
{
	if (this->GetMoney() <= 0)
	{
		auto it = GameScene::GetPlayers()->begin();
		for (; it != GameScene::GetPlayers()->end(); it++)
		{
			if ((*it)->GetMoney() > GameScene::GetPlayers()->at(FinalScene::status - 1)->GetMoney())
				FinalScene::status = (*it)->getTag();
		}
		auto layer = FinalScene::Create();
		GameScene::GetMap()->AddChild(layer);
		layer->SetPosition(Director::GetInstance()->GetVisibleSize() / 2);
		layer->SetAnchorPoint(Vec2(0.5, 0.5));
	}
	else
	{
		FadeOut* fadeout = FadeOut::Create(0.2f);
		FadeIn* fadein = FadeIn::Create(0.2f);
		this->setturnme(false);
		this->RunAction(Sequence::Create(fadeout, fadein, CallFunc::Create([pathrowcopy, pathcolcopy, this](){
			auto c = Control::GetInstance();
			if (stayRounds != 0)
			{
				std::vector<int>pathr;
				std::vector<int>pathc;
				pathr.push_back(pathrowcopy.at(0));
				pathc.push_back(pathcolcopy.at(0));
				this->Addstep_image_running(pathr, pathc);
				stayRounds--;
				c->StartGo(pathr, pathc, this);
			}
			else
			{
				this->Addstep_image_running(pathrowcopy, pathcolcopy);
				c->StartGo(pathrowcopy, pathcolcopy, this);
			}
		}
		), NULL));
	}
}

//The number animation to show the steps to take
void VirtualPlayer::Addstep_image_running(std::vector<int>pathRow, std::vector<int>pathCol)
{
	for (int i = 1; i < pathRow.size(); i++)
	{
		Point p = Point(pathCol[i]*tileWidth, pathRow[i]*tileHeigh);
		GameScene::GetStepImage()->at(i - 1)->SetPosition(p);
		GameScene::GetStepImage()->at(i - 1)->SetVisible(true);
		GameScene::GetStepImage()->at(i - 1)->SetAnchorPoint(Vec2(0, 0));
	}
}


void VirtualPlayer::Initpathrowandcol()
{
	pathCol.clear();
	pathRow.clear();
	pathCol = Route::GetInstance()->GetPathCol();
	pathRow = Route::GetInstance()->GetPathRow();
}

//Acquire a lottery
void VirtualPlayer::GetLottery()
{
	srand(clock());
	for (int i = 0; i < 1; i++)
	{
		vec.push_back(rand() % 30 + 1);
	}
	auto s = String::createWithFormat("You get a Lottery : %d", vec[0]);
	toast::addtoast(GameScene::GetMap(), this->GetPosition(), s->getCString() ,2);
}

//角色动画效果
void VirtualPlayer::AddPlayerAnimation(char* left_animation, char* right_animation,char* down_animation,char* up_animation){
	//如果之前没有的话
	if (!AnimationCache::GetInstance()->getAnimation(left_animation))
	{
		AnimationCache::GetInstance()->AddAnimation(Animation::createWithSpriteFrames(Left, 0.3f), left_animation);
	}

	if (!AnimationCache::GetInstance()->getAnimation(right_animation))
	{
		AnimationCache::GetInstance()->AddAnimation(Animation::createWithSpriteFrames(Right, 0.3f), right_animation);
	}

	if (!AnimationCache::GetInstance()->getAnimation(down_animation))
	{
		AnimationCache::GetInstance()->AddAnimation(Animation::createWithSpriteFrames(Down, 0.3f), down_animation);
	}

	if (!AnimationCache::GetInstance()->getAnimation(up_animation))
	{
		AnimationCache::GetInstance()->AddAnimation(Animation::createWithSpriteFrames(Up, 0.3f), up_animation);
	}
}