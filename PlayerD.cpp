#include"Player.h"
#include"Control.h"
#include"GameSceneScene.h"
#include"Route.h"
#include"Toast.h"


PlayerD::PlayerD()
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

PlayerD::~PlayerD()
{
}

bool PlayerD::Init()
{
	if (!Sprite::Init())
	{
		return false;
	}
	return true;
}

//Initiate the animation
void PlayerD::InitAnimate()
{
	auto Player_spriteFrameCache = SpriteFrameCache::GetInstance();
	Player_spriteFrameCache->addSpriteFramesWithFile(PLAYER4_ANIM_PLIST, PLAYER4_ANIM_PNG);
	char name[20];
	memset(name, 0, 20);
	name = PLAYER4_ANIM_PNG_1;
	Left.PushBack(Player_spriteFrameCache->getSpriteFrameByName(name));
	Right.PushBack(Player_spriteFrameCache->getSpriteFrameByName(name));
	Down.PushBack(Player_spriteFrameCache->getSpriteFrameByName(name));
	Up.PushBack(Player_spriteFrameCache->getSpriteFrameByName(name));
}


void PlayerD::SetAnimate()
{
	left_animation = "left_animation_4";
	right_animation = "right_animation_4";
	down_animation = "down_animation_4";
	up_animation = "up_animation_4";
	//直接调用父类方法，添加Animation
	AddPlayerAnimation(left_animation, right_animation, down_animation, up_animation);
	left = Animate::Create(AnimationCache::GetInstance()->getAnimation(left_animation));
	right = Animate::Create(AnimationCache::GetInstance()->getAnimation(right_animation));
	down = Animate::Create(AnimationCache::GetInstance()->getAnimation(down_animation));
	up = Animate::Create(AnimationCache::GetInstance()->getAnimation(up_animation));
	left->retain();
	right->retain();
	down->retain();
	up->retain();
}

