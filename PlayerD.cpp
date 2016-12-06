#include"Player.h"
#include"Control.h"
#include"GameSceneScene.h"
#include"Route.h"
#include"Toast.h"


PlayerD::PlayerD()
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

PlayerD::~PlayerD()
{
}

bool PlayerD::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}

//Initiate the animation
void PlayerD::initAnimate()
{
	auto Player_spriteFrameCache = SpriteFrameCache::getInstance();
	Player_spriteFrameCache->addSpriteFramesWithFile("Player4_anim.plist", "Player4_anim.png");
	char name[20];
	memset(name, 0, 20);
	name = "Player4_anim_04.png";
	Left.pushBack(Player_spriteFrameCache->getSpriteFrameByName(name));
	Right.pushBack(Player_spriteFrameCache->getSpriteFrameByName(name));
	Down.pushBack(Player_spriteFrameCache->getSpriteFrameByName(name));
	Up.pushBack(Player_spriteFrameCache->getSpriteFrameByName(name));
}


void PlayerD::setAnimate()
{
	left_animation = "left_animation_4";
	right_animation = "right_animation_4";
	down_animation = "down_animation_4";
	up_animation = "up_animation_4";
	//直接调用父类方法，添加Animation
	AddPlayerAnimation(left_animation, right_animation, down_animation, up_animation);
	left = Animate::create(AnimationCache::getInstance()->getAnimation(left_animation));
	right = Animate::create(AnimationCache::getInstance()->getAnimation(right_animation));
	down = Animate::create(AnimationCache::getInstance()->getAnimation(down_animation));
	up = Animate::create(AnimationCache::getInstance()->getAnimation(up_animation));
	left->retain();
	right->retain();
	down->retain();
	up->retain();
}

