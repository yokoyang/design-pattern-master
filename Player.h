#pragma once
#pragma warning(disable:4996)
#include"cocos2d.h"
#include"Ui.h"

USING_NS_CC;

class PlayerA :public VirtualPlayer
{
private:

	float money = 10000;

public:

	float GetMoney() {return money;}
	PlayerA();
	~PlayerA();
	bool PlayerA::init();

	//Initiate the animation
	void PlayerA::initAnimate();
	void PlayerA::setAnimate();
};

class PlayerB :public VirtualPlayer
{
private:

	float money = 10000;

public:

	float GetMoney() {return money;}
	PlayerB();
	~PlayerB();
	bool PlayerB::init();
	
	//Initiate the animation
	void PlayerB::initAnimate();
	void PlayerB::setAnimate();
};

class PlayerC :public VirtualPlayer
{
private:

	float money = 10000;

public:

	float GetMoney() {return money;}
	PlayerC();
	~PlayerC();
	bool PlayerC::init();
	
	//Initiate the animation
	void PlayerC::initAnimate();
	void PlayerC::setAnimate();
};

class PlayerD :public VirtualPlayer
{
private:

	float money = 10000;

public:

	float GetMoney() {return money;}
	PlayerD();
	~PlayerD();
	bool PlayerD::init();
	
	//Initiate the animation
	void PlayerD::initAnimate();
	void PlayerD::setAnimate();
};
