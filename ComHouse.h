#pragma once
#include"cocos2d.h"
#include"player.h"
#include<string>
USING_NS_CC;

class ComHouse :public house
{
public:
	ComHouse();
	ComHouse::ComHouse(int buyPrice, int rentPrice, int promotePrice)
	~ComHouse();
	virtual void rent();
	virtual void mortgage();
	virtual void ransom();
	virtual void auction();
	virtual void promote();
	virtual void payMoney();
	virtual void happenAccident();
	virtual void changetype(int type);
	virtual bool init();
	CREATE_FUNC(ComHouse);
protected:

};