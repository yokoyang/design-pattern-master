#include"AbstractHouse.h"

AbstractHouse::AbstractHouse()
{

	_iniPri = 0;
	_nowPri = 0;
	_rank = 0;
	_rentMoney = 0;
	_owner = "";
	_isMortgage = false;
	_promoteMoney = 0;
}

AbstractHouse::~AbstractHouse(){

}

// 模板方法
//定义一个操作的算法的框架 给出了逻辑的骨架，而逻辑的组成是一些相应的抽象操作，推迟到子类去实现
void TemplateChooseMethod(){
    PayMoney();
    HappenAccident();
    log("Done the template method!");
}
//define method to buy a house
void AbstractHouse::Buy(std::string& name)
{
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
			_rentMoney = 300;
			(*it)->SetProperty((*it)->GetProperty() - _nowPri);
		}
		else
		{
			_owner = name;
			_rentMoney = 300;
			(*it)->SetProperty((*it)->GetProperty() - _nowPri - 500);
		}
		_rank = 1;
	}
}

void AbstractHouse::Rent()
{

}

void AbstractHouse::Mortgage()
{

}

void AbstractHouse::Ransom()
{

}

void AbstractHouse::Auction()
{

}

void AbstractHouse::Promote()
{

}

void AbstractHouse::ChangeType(int type)
{

}

bool AbstractHouse::IsInit()
{
	if (!Sprite::Init())
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
void PayMoney(){
	//推迟到子类实现
    log("Abstract payMoney method!");
}
//普通住房可以选择购买房子、升级房子，银行可以触发拿到红利动作，监狱可能触发坐牢
void HappenAccident(){
	//推迟到子类实现
    log("Abstract happenAccident method!");
}