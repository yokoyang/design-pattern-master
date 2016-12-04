#include"Prison.h"

Prison::Prison()
{
	_wage = 1000;
	//初始化的时候是未缴纳罚金状态
	acceptPunishment = false;
	delayDay = 3;
}

//监狱可以交赎金
void PayMoney(){
	auto ps = player::getplayers();
	auto it = ps->begin();
	float moneyLeft;
	moneyLeft = (*it)->getproperty() - _wage;
	//能够支付得起赎金
	if(moneyLeft > 0){
		(*it)->setproperty(moneyLeft);
		acceptPunishment = true;
	}
	//没钱缴纳赎金
	else{
		acceptPunishment = false;
	}
	return;
}
//监狱触发坐牢事件
void HappenAccident(){
	//没交赎金，需要玩家坐牢
	if(acceptPunishment == false){
		auto ps = player::getplayers();
		auto it = ps->begin();
		(*it)->setPrison(delayDay);
	}
	else{
		return;
	}
}


Prison::~Prison()
{

}
