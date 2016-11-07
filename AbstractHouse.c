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

AbstractHouse::~AbstractHouse()
{

}

// 模板方法，给出了逻辑的骨架，而逻辑的组成是一些相应的抽象操作，推迟到子类去实现
void TemplateBuyMethod(){
    PrimitiveOperation1();
    PrimitiveOperation2();
    log("Done the method.");
}

void AbstractHouse::buy(std::string& name)
{
	
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

