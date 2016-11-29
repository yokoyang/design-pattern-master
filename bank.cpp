#include"bank.h"

bank::bank()
{
	_wage = 1000;
}

bank::~bank()
{

}

//银行存钱
void payMoney(){
	auto ps = player::getplayers();
	auto it = ps->begin();
	(*it)->getproperty() -= _wage;
	it->saveMony += _wage;
}

//下次来银行时，银行发红利
void happenAccident(){
	auto it = ps->begin();
	(*it)->getproperty() += it->saveMony * 0.2;
}