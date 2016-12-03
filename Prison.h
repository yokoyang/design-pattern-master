#pragma once
#include"cocos2d.h"
#include"Player.h"
#include"Prison.h"
#include<string>
USING_NS_CC;

class Prison :public AbstractHouse
{
protected:
	float _wage;
	bool _acceptPunishment;
	int _delayDay;
public:
	Prison();
	~Prison();
	float Get_wage(){ return _wage; };
	virtual bool Init();
	Create_FUNC(Prison);
	void PayMoney();
	void HappenAccident();

};
