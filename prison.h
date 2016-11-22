#pragma once
#include"cocos2d.h"
#include"player.h"
#include"prison.h"
#include<string>
USING_NS_CC;

class prison :public AbstractHouse
{
protected:
	float _wage;
	bool acceptPunishment;
	int delayDay;
public:
	prison();
	~prison();
	float getwage(){ return _wage; };
	virtual bool init();
	CREATE_FUNC(prison);
	void payMoney();
	void happenAccident();

};
