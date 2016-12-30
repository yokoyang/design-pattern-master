#pragma once
#include"cocos2d.h"
#include"Player.h"
#include"AbstractHouse.h"
#include<string>
USING_NS_CC;


//declare virtual methods in class ComHouse
class ComHouse :public AbstractHouse
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
	virtual void ChangeType(int type);
	virtual bool Init();
	CREATE_FUNC(ComHouse);
	
protected:

};