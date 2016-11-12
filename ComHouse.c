#include "ComHouse.h"
ComHouse::ComHouse()
{
	//默认价格、租赁费、升级费用
   ComHouse(1500,300,500);
}

ComHouse::ComHouse(int buyPrice, int rentPrice, int promotePrice)
{
	_ini_pri = price;
	_now_pri = price;
	_rank = 1;
	_rent_money = rentPrice;
	_promote_money = promotePrice;
	_ismortgage = false;
	_owner = "";
}
ComHouse::~ComHouse()
{

}

void ComHouse::buy(std::string& name)
{
	//如果此房产没有被抵押没有
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
			_rent_money = rentPrice;
			(*it)->setproperty((*it)->getproperty() - _now_pri);
		}
		else
		{
			_owner = name;
			_rent_money = rentPrice;
			(*it)->setproperty((*it)->getproperty() - _now_pri - promotePrice);
		}
		_rank = 1;
	}
}

void ComHouse::rent()
{
	if (!_ismortgage)
	{
		auto ps = player::getplayers();
		for (auto it = ps->begin(); it != ps->end(); it++)
		{
			if ((*it)->getname() == _name)
			{
				(*it)->setproperty((*it)->getproperty() + _rent_money);
				break;
			}
		}
	}
}

void ComHouse::mortgage()
{
	_ismortgage = true;
	auto ps = player::getplayers();
	for (auto it = ps->begin(); it != ps->end(); it++)
	{
		if ((*it)->getname() == _name)
		{
			(*it)->setproperty((*it)->getproperty() + _now_pri / 2);
			break;
		}
	}
}

void ComHouse::ransom()
{
	auto ps = player::getplayers();
	for (auto it = ps->begin(); it != ps->end(); it++)
	{
		if ((*it)->getname() == _name)
		{
			_ismortgage = false;
			(*it)->setproperty((*it)->getproperty() - _now_pri * 0.6);
			break;
		}
	}
}

void ComHouse::promote()
{
	if (!_ismortgage)
	{
		if (_rank == 1)
		{
			_rank++;
			_now_pri += 500;
			_rent_money += 100;
		}
		else if (_rank == 2)
		{
			_rank++;
			_now_pri += 600;
			_rent_money += 200;
		}
	}
}

void ComHouse::changetype(int type)
{
	//TODO
}

void ComHouse::auction()
{
	if (!_ismortgage)
	{
		auto ps = player::getplayers();
		for (auto it = ps->begin(); it != ps->end(); it++)
		{
			if ((*it)->getname() == _name)
			{
				(*it)->setproperty((*it)->getproperty() + _now_pri);
				break;
			}
		}
		_ini_pri = 1500;
		_now_pri = 1500;
		_rank = 1;
		_rent_money = 0;
		_promote_money = 500;
		_ismortgage = false;
		_owner = "";
	}
}

bool ComHouse::init()
{
	if (!Sprite::init())
		return false;
	_ini_pri = 1500;
	_now_pri = 1500;
	_rank = 1;
	_rent_money = 0;
	_promote_money = 500;
	_ismortgage = false;
	_owner = "";
	return true;
}