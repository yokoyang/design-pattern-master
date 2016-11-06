#include"house.h"

house::house()
{
	_ini_pri = 0;
	_now_pri = 0;
	_rank = 0;
	_rent_money = 0;
	_promote_money = 0;
	_ismortgage = false;
	_owner = "";
}

house::~house()
{

}

// 模板方法，给出了逻辑的骨架，而逻辑的组成是一些相应的抽象操作，推迟到子类去实现
void TemplateMethod(){
    PrimitiveOperation1();
    PrimitiveOperation2();
    log("Done the method.");
}

void house::buy(std::string& name)
{
	
}

void house::rent()
{

}

void house::mortgage()
{

}

void house::ransom()
{

}

void house::auction()
{

}

void house::promote()
{

}

void house::changetype(int type)
{

}

bool house::init()
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

