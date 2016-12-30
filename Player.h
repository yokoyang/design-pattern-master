#pragma once
#pragma warning(disable:4996)
#include"cocos2d.h"
#include"Ui.h"
#include "VirtualPlayer.h"
#include "Const.h"

USING_NS_CC;


//define four kinds of player
class PlayerA :public VirtualPlayer
{
private:

	float money = INIT_MONEY;

public:

	float GetMoney() {return money;}
	PlayerA();
	~PlayerA();
	bool PlayerA::Init();

	//Initiate the animation
	void PlayerA::InitAnimate();
	void PlayerA::SetAnimate();
};

class PlayerB :public VirtualPlayer
{
private:

	float money = INIT_MONEY;

public:

	float GetMoney() {return money;}
	PlayerB();
	~PlayerB();
	bool PlayerB::Init();
	
	//Initiate the animation
	void PlayerB::InitAnimate();
	void PlayerB::SetAnimate();
};

class PlayerC :public VirtualPlayer
{
private:

	float money = INIT_MONEY;

public:

	float GetMoney() {return money;}
	PlayerC();
	~PlayerC();
	bool PlayerC::Init();
	
	//Initiate the animation
	void PlayerC::InitAnimate();
	void PlayerC::SetAnimate();
};

class PlayerD :public VirtualPlayer
{
private:

	float money = INIT_MONEY;

public:

	float GetMoney() {return money;}
	PlayerD();
	~PlayerD();
	bool PlayerD::Init();
	
	//Initiate the animation
	void PlayerD::InitAnimate();
	void PlayerD::SetAnimate();
};
