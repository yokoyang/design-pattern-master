#pragma once
#include"cocos2d.h"
#include"player.h"
#include"bank.h"
#include<string>
USING_NS_CC;

class bank :public AbstractHouse
{
protected:
	float _wage;
public:
	bank();
	~bank();
	float getwage(){ return _wage; };
	virtual bool init();
	CREATE_FUNC(bank);
	void payMoney();
	void happenAccident();
};
