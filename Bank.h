#pragma once
#include "cocos2d.h"
#include "Player.h"
#include "Bank.h"
#include <string>
USING_NS_CC;

class Bank :public AbstractHouse
{
protected:
	float _wage;
public:
	Bank();
	~Bank();
	float Getwage(){ return _wage; };
	virtual bool Init();
	Create_FUNC(CBank);
	void PayMoney();
	void HappenAccident();
};
