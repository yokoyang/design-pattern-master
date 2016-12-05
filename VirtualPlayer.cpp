#include"Player.h"
#include"control.h"
#include"GameSceneScene.h"
#include"route.h"
#include"toast.h"
#include"FinalScene.h"


Player::Player()
{
	comex = -1; comey = -1;
	_money = 0;
	saveMony = 0;
	_name = nullptr;
	money_string = Label::createWithTTF("","fonts/Gazzarel.TTF",20);
	turnme = false;
	oneroundend = true;
	stayRounds = 0;
}

Player::~Player()
{
}

bool Player::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}
//Initaite the Player info
Player* Player::createwith(char* name, int tag, SpriteFrame* imag, float& money)
{
	auto temp = create();
	temp->setTag(tag);
	temp->initAnimate();
	temp->setAnimate();
	temp->Sprite::initWithSpriteFrame(imag);
	temp->_name = Label::createWithTTF(name, "fonts/Gazzarel.TTF", 20);
	temp->_money = money;
	temp->turnme = false;
	memset(temp->right_animation, 0, 20);
	memset(temp->down_animation, 0, 20);
	memset(temp->up_animation, 0, 20);
	memset(temp->left_animation, 0, 20);
	return temp;
}




void Player::settilesize(float tilewidth, float tileheigh)
{
	this->tilewidth = tilewidth;
	this->tileheigh = tileheigh;
}

//Begin the Player's motion
void Player::go(std::vector<int>pathrowcopy,std::vector<int>pathcolcopy)
{
	if (this->getmoney() <= 0)
	{
		auto it = GameScene::getPlayers()->begin();
		for (; it != GameScene::getPlayers()->end(); it++)
		{
			if ((*it)->getmoney() > GameScene::getPlayers()->at(FinalScene::status - 1)->getmoney())
				FinalScene::status = (*it)->getTag();
		}
		auto layer = FinalScene::create();
		GameScene::getmap()->addChild(layer);
		layer->setPosition(Director::getInstance()->getVisibleSize() / 2);
		layer->setAnchorPoint(Vec2(0.5, 0.5));
	}
	else
	{
		FadeOut* fadeout = FadeOut::create(0.2f);
		FadeIn* fadein = FadeIn::create(0.2f);
		this->setturnme(false);
		this->runAction(Sequence::create(fadeout, fadein, CallFunc::create([pathrowcopy, pathcolcopy, this](){
			auto c = control::getInstance();
			if (stayRounds != 0)
			{
				std::vector<int>pathr;
				std::vector<int>pathc;
				pathr.push_back(pathrowcopy.at(0));
				pathc.push_back(pathcolcopy.at(0));
				this->addstep_image_running(pathr, pathc);
				stayRounds--;
				c->startgo(pathr, pathc, this);
			}
			else
			{
				this->addstep_image_running(pathrowcopy, pathcolcopy);
				c->startgo(pathrowcopy, pathcolcopy, this);
			}
		}
		), NULL));
	}
}

//The number animation to show the steps to take
void Player::addstep_image_running(std::vector<int>pathrow, std::vector<int>pathcol)
{
	for (int i = 1; i < pathrow.size(); i++)
	{
		Point p = Point(pathcol[i]*tilewidth, pathrow[i]*tileheigh);
		GameScene::getstep_image()->at(i - 1)->setPosition(p);
		GameScene::getstep_image()->at(i - 1)->setVisible(true);
		GameScene::getstep_image()->at(i - 1)->setAnchorPoint(Vec2(0, 0));
	}
}


void Player::initpathrowandcol()
{
	pathcol.clear();
	pathrow.clear();
	pathcol = route::getInstance()->getpathcol();
	pathrow = route::getInstance()->getpathrow();
}

//Acquire a lottery
void Player::getLottery()
{
	srand(clock());
	for (int i = 0; i < 1; i++)
	{
		vec.push_back(rand() % 30 + 1);
	}
	auto s = String::createWithFormat("You get a Lottery : %d", vec[0]);
	toast::addtoast(GameScene::getmap(), this->getPosition(), s->getCString() ,2);
}

//角色动画效果
virtual void AddPlayerAnimation(char* left_animation, char* right_animation,char* down_animation,char* up_animation){
	//如果之前没有的话
	if (!AnimationCache::getInstance()->getAnimation(left_animation))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(Left, 0.3f), left_animation);
	}

	if (!AnimationCache::getInstance()->getAnimation(right_animation))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(Right, 0.3f), right_animation);
	}

	if (!AnimationCache::getInstance()->getAnimation(down_animation))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(Down, 0.3f), down_animation);
	}
	
	if (!AnimationCache::getInstance()->getAnimation(up_animation))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(Up, 0.3f), up_animation);
	}
}