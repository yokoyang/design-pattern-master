#include"Player.h"
#include"Control.h"
#include"GameSceneScene.h"
#include"Route.h"
#include"Toast.h"


PlayerA::PlayerA()
{
	comex = -1; comey = -1;
	_money = 0;
	saveMony = 0;
	_name = nullptr;
	money_string = Label::createWithTTF("",SETTING_FONT,20);
	turnme = false;
	oneroundend = true;
	stayRounds = 0;
}

PlayerA::~PlayerA()
{
}

bool PlayerA::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}

//Initiate the SpriteFrame
void PlayerA::initAnimate()
{
	auto Player_spriteFrameCache = SpriteFrameCache::getInstance();
	Player_spriteFrameCache->addSpriteFramesWithFile(PLAYER1_ANIM_PLIST, PLAYER1_ANIM_PNG);
	char name[20];
	memset(name, 0, 20);
	name = PLAYER1_ANIM_PNG_1;
	Left.pushBack(Player_spriteFrameCache->getSpriteFrameByName(name));
	Right.pushBack(Player_spriteFrameCache->getSpriteFrameByName(name));
	Down.pushBack(Player_spriteFrameCache->getSpriteFrameByName(name));
	Up.pushBack(Player_spriteFrameCache->getSpriteFrameByName(name));
}


void PlayerA::setAnimate()
{
	left_animation = "left_animation_1";
	right_animation = "right_animation_1";
	down_animation = "down_animation_1";
	up_animation = "up_animation_1";
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

