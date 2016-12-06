#include"player.h"
#include"control.h"
#include"GameSceneScene.h"
#include"route.h"
#include"toast.h"
#include"FinalScene.h"


player::player()
{
	comex = -1; comey = -1;
	_money = 0;
	saveMony = 0;
	_name = nullptr;
	money_string = Label::createWithTTF("", SETTING_FONT, 20);
	turnme = false;
	oneroundend = true;
	stayRounds = 0;
}

player::~player()
{
}

bool player::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}
//Initaite the player info
player* player::createwith(char* name, int tag, SpriteFrame* imag, float& money)
{
	auto temp = create();
	temp->setTag(tag);
	temp->initAnimate();
	temp->setAnimate();
	temp->Sprite::initWithSpriteFrame(imag);
	temp->_name = Label::createWithTTF(name, SETTING_FONT, 20);
	temp->_money = money;
	temp->turnme = false;
	memset(temp->right_animation, 0, 20);
	memset(temp->down_animation, 0, 20);
	memset(temp->up_animation, 0, 20);
	memset(temp->left_animation, 0, 20);
	return temp;
}




void player::settilesize(float tilewidth, float tileheigh)
{
	this->tilewidth = tilewidth;
	this->tileheigh = tileheigh;
}

//Begin the player's motion
void player::go(std::vector<int>pathrowcopy,std::vector<int>pathcolcopy)
{
	if (this->getmoney() <= 0)
	{
		auto it = GameScene::getplayers()->begin();
		for (; it != GameScene::getplayers()->end(); it++)
		{
			if ((*it)->getmoney() > GameScene::getplayers()->at(FinalScene::status - 1)->getmoney())
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
void player::addstep_image_running(std::vector<int>pathrow, std::vector<int>pathcol)
{
	for (int i = 1; i < pathrow.size(); i++)
	{
		Point p = Point(pathcol[i]*tilewidth, pathrow[i]*tileheigh);
		GameScene::getstep_image()->at(i - 1)->setPosition(p);
		GameScene::getstep_image()->at(i - 1)->setVisible(true);
		GameScene::getstep_image()->at(i - 1)->setAnchorPoint(Vec2(0, 0));
	}
}


void player::initpathrowandcol()
{
	pathcol.clear();
	pathrow.clear();
	pathcol = route::getInstance()->getpathcol();
	pathrow = route::getInstance()->getpathrow();
}


//Initiate the animation
void player::initAnimate()
{
	auto player_spriteFrameCache = SpriteFrameCache::getInstance();

	int tag = getTag();
	switch (tag)
	{
	case 1:
	{
		player_spriteFrameCache->addSpriteFramesWithFile(PLAYER1_ANIM_PLIST, PLAYER1_ANIM_PNG);
			  break;
	}
	case 2:
	{
		player_spriteFrameCache->addSpriteFramesWithFile(PLAYER2_ANIM_PLIST, PLAYER2_ANIM_PNG);
			  break;
	}
	case 3:
	{
		player_spriteFrameCache->addSpriteFramesWithFile(PLAYER3_ANIM_PLIST, PLAYER3_ANIM_PNG);
			  break;
	}
	case 4:
	{
		player_spriteFrameCache->addSpriteFramesWithFile(PLAYER4_ANIM_PLIST, PLAYER4_ANIM_PNG);
			  break;
	}
	}

	
	char name[20];
	memset(name, 0, 20);
	
	for (int i = 1; i <= 4; i++)
	{
		
		sprintf(name, "player%d_anim_0%d.png", tag, i);
		Left.pushBack(player_spriteFrameCache->getSpriteFrameByName(name));

	}
	for (int i = 5; i <= 8; i++)
	{
		
		sprintf(name, "player%d_anim_0%d.png", tag, i);
		Right.pushBack(player_spriteFrameCache->getSpriteFrameByName(name));


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
		Down.pushBack(player_spriteFrameCache->getSpriteFrameByName(name));

	}
	for (int i = 13; i <= 16; i++)
	{
		
		sprintf(name, "player%d_anim_%d.png", tag, i);
		Up.pushBack(player_spriteFrameCache->getSpriteFrameByName(name));

	}

}


void player::setAnimate()
{
	int tag = getTag();
	sprintf(left_animation, "left_animation_%d", tag);


	sprintf(right_animation, "right_animation_%d", tag);


	sprintf(down_animation, "down_animation_%d", tag);

	sprintf(up_animation, "up_animation_%d", tag);

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

	left = Animate::create(AnimationCache::getInstance()->getAnimation(left_animation));
	right = Animate::create(AnimationCache::getInstance()->getAnimation(right_animation));
	down = Animate::create(AnimationCache::getInstance()->getAnimation(down_animation));
	up = Animate::create(AnimationCache::getInstance()->getAnimation(up_animation));
	left->retain();
	right->retain();
	down->retain();
	up->retain();
}


//Acquire a lottery
void player::getLottery()
{
	srand(clock());
	for (int i = 0; i < 1; i++)
	{
		vec.push_back(rand() % 30 + 1);
	}
	auto s = String::createWithFormat("You get a Lottery : %d", vec[0]);
	toast::addtoast(GameScene::getmap(), this->getPosition(), s->getCString() ,2);
}
