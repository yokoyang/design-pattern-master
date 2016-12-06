#include"Bank.h"

Bank::Bank()
{
	_wage = 1000;
}

Bank::~Bank()
{

}

//银行存钱
void PayMoney(){
	auto ps = Player::GetPlayers();
	auto it = ps->Begin();
	(*it)->GetProperty() -= _wage;
	it->_saveMoney += _wage;
}

//下次来银行时，银行发红利
void HappenAccident(){
	auto it = ps->Begin();
	(*it)->GetProperty() += it->_saveMony * 0.2;
}