#pragma once
#include"cocos2d.h"
#include"Player.h"
#include<string>
USING_NS_CC;

class ComHouse :public house
{
public:
	ComHouse();
	ComHouse::ComHouse(int buyPrice, int rentPrice, int promotePrice)
	~ComHouse();
	virtual void Rent();
	virtual void Mortgage();
	virtual void Ransom();
	virtual void Auction();
	virtual void Promote();
	virtual void PayMoney();
	virtual void HappenAccident();
	virtual void ChanGetype(int type);
	virtual bool Init();
	Create_FUNC(ComHouse);
protected:

};