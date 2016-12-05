#include "ComHouse.h"
ComHouse::ComHouse()
{
	//默认价格、租赁费、升级费用
   ComHouse(1500,300,500);
}

ComHouse::ComHouse(int buyPrice, int rentPrice, int promotePrice)
{
	_iniPri = price;
	_nowPri = price;
	_rank = 1;
	_rentMoney = rentPrice;
	_promoteMoney = promotePrice;
	_isMortgage = false;
	_owner = "";
}
ComHouse::~ComHouse()
{

}

void ComHouse::PayMoney()
{
	std::string name = Player::GetPlayers()->_name;
	//如果此房产没有被抵押没有
	if (!_isMortgage)
	{
		auto ps = Player::GetPlayers();
		auto it = ps->Begin();
		for (; it != ps->End(); it++)
		{
			if ((*it)->GetName() == _name)
			{
				break;
			}
		}
		if (_owner == "")
		{
			_owner = name;
			_rentMoney = rentPrice;
			(*it)->SetProperty((*it)->GetProperty() - _nowPri);
		}
		else
		{
			_owner = name;
			_rentMoney = rentPrice;
			(*it)->SetProperty((*it)->GetProperty() - _nowPri - _promotePrice);
		}
		_rank = 1;
	}
}



void ComHouse::Mortgage()
{
	_ismortgage = true;
	auto ps = Player::GetPlayers();
	for (auto it = ps->Begin(); it != ps->End(); it++)
	{
		if ((*it)->GetName() == _name)
		{
			(*it)->SetProperty((*it)->GetProperty() + _nowPri / 2);
			break;
		}
	}
}

void ComHouse::Ransom()
{
	auto ps = Player::GetPlayers();
	for (auto it = ps->Begin(); it != ps->End(); it++)
	{
		if ((*it)->GetName() == _name)
		{
			_ismortgage = false;
			(*it)->SetProperty((*it)->GetProperty() - _nowPri * 0.6);
			break;
		}
	}
}

void ComHouse::Promote()
{
	if (!_ismortgage)
	{
		if (_rank == 1)
		{
			_rank++;
			_nowPri += 500;
			_rentMoney += 100;
		}
		else if (_rank == 2)
		{
			_rank++;
			_nowPri += 600;
			_rentMoney += 200;
		}
	}
}

void ComHouse::ChangeType(int type)
{
	//TODO
}

void ComHouse::Auction()
{
	if (!_ismortgage)
	{
		auto ps = Player::GetPlayers();
		for (auto it = ps->Begin(); it != ps->End(); it++)
		{
			if ((*it)->GetName() == _name)
			{
				(*it)->SetProperty((*it)->GetProperty() + _nowPri);
				break;
			}
		}
		_iniPri = 1500;
		_nowPri = 1500;
		_rank = 1;
		_rentMoney = 0;
		_promoteMoney = 500;
		_isMortgage = false;
		_owner = "";
	}
}

bool ComHouse::Init()
{
	if (!Sprite::Init())
		return false;
	_iniPri = 1500;
	_nowPri = 1500;
	_rank = 1;
	_rentMoney = 0;
	_promoteMoney = 500;
	_isMortgage = false;
	_owner = "";
	return true;
}

void ComHouse::Rent()
{
	//未抵押的房产
	if (!_ismortgage)
	{
		auto ps = Player::GetPlayers();
		for (auto it = ps->Begin(); it != ps->End(); it++)
		{
			if ((*it)->GetName() == _name)
			{
				(*it)->SetProperty((*it)->GetProperty() + _rentMoney);
				break;
			}
		}
	}
}

void HappenAccident(){

}