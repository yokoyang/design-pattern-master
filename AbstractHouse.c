#include"AbstractHouse.h"

AbstractHouse::AbstractHouse()
{
	_ini_pri = 0;
	_now_pri = 0;
	_rank = 0;
	_rent_money = 0;
	_promote_money = 0;
	_ismortgage = false;
	_owner = "";
}

AbstractHouse::~AbstractHouse(){

}

// 模板方法，给出了逻辑的骨架，而逻辑的组成是一些相应的抽象操作，推迟到子类去实现
void TemplateChooseMethod(){
    payMoney();
    happenAccident();
    log("Done the template method!");
}

void AbstractHouse::buy(std::string& name)
{
	if (!_ismortgage)
	{
		auto ps = player::getplayers();
		auto it = ps->begin();
		for (; it != ps->end(); it++)
		{
			if ((*it)->getname() == _name)
			{
				break;
			}
		}
		if (_owner == "")
		{
			_owner = name;
			_rent_money = 300;
			(*it)->setproperty((*it)->getproperty() - _now_pri);
		}
		else
		{
			_owner = name;
			_rent_money = 300;
			(*it)->setproperty((*it)->getproperty() - _now_pri - 500);
		}
		_rank = 1;
	}
}

void AbstractHouse::rent()
{

}

void AbstractHouse::mortgage()
{

}

void AbstractHouse::ransom()
{

}

void AbstractHouse::auction()
{

}

void AbstractHouse::promote()
{

}

void AbstractHouse::changetype(int type)
{

}

bool AbstractHouse::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	_ini_pri = 0;
	_now_pri = 0;
	_rank = 0;
	_rent_money = 0;
	_promote_money = 0;
	_ismortgage = false;
	_owner = "";
	return true;
}

//普通房子实现交过路费，监狱可以交赎金，银行存钱
void payMoney(){

}
//普通住房可以选择购买房子、升级房子，银行可以触发取钱动作，监狱可能触发坐牢
void happenAccident(){

}