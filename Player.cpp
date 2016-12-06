#include"Player.h"
#include"Control.h"
#include"GameSceneScene.h"
#include"Route.h"
#include"Toast.h"
#include"FinalScene.h"
#include <String>


Player::Player()
{
	_comeX = -1; _comeY = -1;
	_money = 0;
	_saveMoney = 0;
	_name = nullptr;
	_moneyString = Label::CreateWithTTF("","fonts/Gazzarel.TTF",20);
	_turnMe = false;
	_oneRoundend = true;
	_stayRounds = 0;
}

Player::~Player()
{
}

bool Player::Init()
{
	if (!Sprite::Init())
	{
		return false;
	}
	return true;
}
//Initaite the player info
Player* Player::Createwith(char* name, int tag, SpriteFrame* imag, float& money)
{
	auto temp = Create();
	temp->SetTag(tag);
	temp->InitAnimate();
	temp->SetAnimate();
	temp->Sprite::InitWithSpriteFrame(imag);
	temp->_name = Label::CreateWithTTF(name, "fonts/Gazzarel.TTF", 20);
	temp->_money = money;
	temp->_turnMe = false;
	MemSet(temp->_rightAnimation, 0, 20);
	MemSet(temp->_downAnimation, 0, 20);
	MemSet(temp->_upAnimation, 0, 20);
	MemSet(temp->_leftAnimation, 0, 20);
	return temp;
}




void Player::SettileSize(float tilewidth, float tileheigh)
{
	this->tilewidth = tilewidth;
	this->tileheigh = tileheigh;
}

//Begin the player's motion
void Player::Go(std::vector<int>pathrowcopy,std::vector<int>pathcolcopy)
{
	if (this->GetMoney() <= 0)
	{
		auto it = GameScene::GetPlayers()->Begin();
		for (; it != GameScene::GetPlayers()->End(); it++)
		{
			if ((*it)->GetMoney() > GameScene::GetPlayers()->at(FinalScene::status - 1)->GetMoney())
				FinalScene::status = (*it)->GetTag();
		}
		auto layer = FinalScene::Create();
		GameScene::Getmap()->AddChild(layer);
		layer->setPosition(Director::GetInstance()->GetvisibleSize() / 2);
		layer->setAnchorPoint(Vec2(0.5, 0.5));
	}
	else
	{
		FadeOut* fadeout = FadeOut::Create(0.2f);
		FadeIn* fadein = FadeIn::Create(0.2f);
		this->Set_turnMe(false);
		this->RunAction(Sequence::Create(fadeout, fadein, CallFunc::Create([pathrowcopy, pathcolcopy, this](){
			auto c = Control::GetInstance();
			if (_stayRounds != 0)
			{
				std::vector<int>pathr;
				std::vector<int>pathc;
				pathr.push_back(pathrowcopy.at(0));
				pathc.push_back(pathcolcopy.at(0));
				this->AddStep_image_running(pathr, pathc);
				_stayRounds--;
				c->StartGo(pathr, pathc, this);
			}
			else
			{
				this->AddStep_image_running(pathrowcopy, pathcolcopy);
				c->StartGo(pathrowcopy, pathcolcopy, this);
			}
		}
		), NULL));
	}
}

//The number animation to show the steps to take
void Player::AddStep_image_running(std::vector<int>pathRow, std::vector<int>pathCol)
{
	for (int i = 1; i < pathRow.size(); i++)
	{
		Point p = Point(pathCol[i]*tilewidth, pathRow[i]*tileheigh);
		GameScene::GetStep_image()->at(i - 1)->setPosition(p);
		GameScene::GetStep_image()->at(i - 1)->setVisible(true);
		GameScene::GetStep_image()->at(i - 1)->setAnchorPoint(Vec2(0, 0));
	}
}


void Player::InitPathRowAndCol()
{
	pathCol.Clear();
	pathRow.Clear();
	pathCol = Route::GetInstance()->GetPathCol();
	pathRow = Route::GetInstance()->GetPathRow();
}


//Initiate the animation
void Player::InitAnimate()
{
	auto player_spriteFrameCache = SpriteFrameCache::GetInstance();

	int tag = GetTag();
	switch (tag)
	{
	case 1:
	{
			  player_spriteFrameCache->AddSpriteFramesWithFile("player1_anim.plist", "player1_anim.png");
			  break;
	}
	case 2:
	{
			  player_spriteFrameCache->AddSpriteFramesWithFile("player2_anim.plist", "player2_anim.png");
			  break;
	}
	case 3:
	{
			  player_spriteFrameCache->AddSpriteFramesWithFile("player3_anim.plist", "player3_anim.png");
			  break;
	}
	case 4:
	{
			  player_spriteFrameCache->AddSpriteFramesWithFile("player4_anim.plist", "player4_anim.png");
			  break;
	}
	}

	
	char name[20];
	MemSet(name, 0, 20);
	
	for (int i = 1; i <= 4; i++)
	{
		
		sprintf(name, "player%d_anim_0%d.png", tag, i);
		Left.PushBack(player_spriteFrameCache->GetSpriteFrameByName(name));

	}
	for (int i = 5; i <= 8; i++)
	{
		
		sprintf(name, "player%d_anim_0%d.png", tag, i);
		Right.PushBack(player_spriteFrameCache->GetSpriteFrameByName(name));


	}
	for (int i = 9; i <= 12; i++)
	{
		if (i == 9)
		{
			sprintf(name, "player%d_anim_0%d.png", tag, i);
		}
		else
		{
			sprintf(name, "player%d_anim_%d.png", tag, i);
		}
		Down.PushBack(player_spriteFrameCache->GetSpriteFrameByName(name));

	}
	for (int i = 13; i <= 16; i++)
	{
		
		sprintf(name, "player%d_anim_%d.png", tag, i);
		Up.PushBack(player_spriteFrameCache->GetSpriteFrameByName(name));

	}

}


void Player::SetAnimate()
{
	int tag = GetTag();
	sprintf(_leftAnimation, "left_animation_%d", tag);


	sprintf(_rightAnimation, "right_animation_%d", tag);


	sprintf(_downAnimation, "down_animation_%d", tag);

	sprintf(_upAnimation, "up_animation_%d", tag);

	if (!AnimationCache::GetInstance()->GetAnimation(_leftAnimation))
	{
		AnimationCache::GetInstance()->AddAnimation(Animation::CreateWithSpriteFrames(Left, 0.3f), _leftAnimation);
	}
	if (!AnimationCache::GetInstance()->GetAnimation(_rightAnimation))
	{
		AnimationCache::GetInstance()->AddAnimation(Animation::CreateWithSpriteFrames(Right, 0.3f), _rightAnimation);
	}
	if (!AnimationCache::GetInstance()->GetAnimation(_downAnimation))
	{
		AnimationCache::GetInstance()->AddAnimation(Animation::CreateWithSpriteFrames(Down, 0.3f), _downAnimation);
	}
	if (!AnimationCache::GetInstance()->GetAnimation(_upAnimation))
	{
		AnimationCache::GetInstance()->AddAnimation(Animation::CreateWithSpriteFrames(Up, 0.3f), _upAnimation);
	}

	left = Animate::Create(AnimationCache::GetInstance()->GetAnimation(_leftAnimation));
	right = Animate::Create(AnimationCache::GetInstance()->GetAnimation(_rightAnimation));
	down = Animate::Create(AnimationCache::GetInstance()->GetAnimation(_downAnimation));
	up = Animate::Create(AnimationCache::GetInstance()->GetAnimation(_upAnimation));
	left->Retain();
	right->Retain();
	down->Retain();
	up->Retain();
}


//Acquire a lottery
void Player::GetLottery()
{
	srand(clock());
	for (int i = 0; i < 1; i++)
	{
		vec.push_back(rand() % 30 + 1);
	}
	auto s = String::CreateWithFormat("You Get a Lottery : %d", vec[0]);
	Toast::AddToast(GameScene::Getmap(), this->GetPosition(), s->GetCString() ,2);
}