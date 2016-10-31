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

comhouse1::comhouse1()
{
	_ini_pri = 1500;
	_now_pri = 1500;
	_rank = 1;
	_rent_money = 0;
	_promote_money = 500;
	_ismortgage = false;
	_owner = "";
}

comhouse1::~comhouse1()
{

}

void comhouse1::buy(std::string& name)
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

void comhouse1::rent()
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

void comhouse1::mortgage()
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

void comhouse1::ransom()
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

void comhouse1::promote()
{
	if (!_ismortgage)
	{
		if (_rank == 1)
		{
			_rank++;
			_now_pri = 2500;
			_rent_money = 400;
		}
		else if (_rank == 2)
		{
			_rank++;
			_now_pri = 3000;
			_rent_money = 500;
		}
	}
}

void comhouse1::changetype(int type)
{

}

void comhouse1::auction()
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

bool comhouse1::init()
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



comhouse2::comhouse2()
{
	_ini_pri = 2000;
	_now_pri = 2000;
	_rank = 1;
	_rent_money = 0;
	_promote_money = 500;
	_ismortgage = false;
	_owner = "";
}

comhouse2::~comhouse2()
{

}

void comhouse2::buy(std::string& name)
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
			_rent_money = 400;
			(*it)->setproperty((*it)->getproperty() - _now_pri);
		}
		else
		{
			_owner = name;
			_rent_money = 400;
			(*it)->setproperty((*it)->getproperty() - _now_pri - 500);
		}
		_rank = 1;
	}
}

void comhouse2::rent()
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

void comhouse2::mortgage()
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

void comhouse2::ransom()
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

void comhouse2::promote()
{
	if (!_ismortgage)
	{
		if (_rank == 1)
		{
			_rank++;
			_now_pri = 3000;
			_rent_money = 500;
		}
		else if (_rank == 2)
		{
			_rank++;
			_now_pri = 3500;
			_rent_money = 600;
		}
	}
}

void comhouse2::changetype(int type)
{

}

void comhouse2::auction()
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
		_ini_pri = 2000;
		_now_pri = 2000;
		_rank = 1;
		_rent_money = 0;
		_promote_money = 500;
		_ismortgage = false;
		_owner = "";
	}
}


bool comhouse2::init()
{
	if (!Sprite::init())
		return false;
	_ini_pri = 2000;
	_now_pri = 2000;
	_rank = 1;
	_rent_money = 0;
	_promote_money = 500;
	_ismortgage = false;
	_owner = "";
	return true;
}



comhouse3::comhouse3()
{
	_ini_pri = 2500;
	_now_pri = 2500;
	_rank = 1;
	_rent_money = 0;
	_promote_money = 500;
	_ismortgage = false;
	_owner = "";
}

comhouse3::~comhouse3()
{

}

void comhouse3::buy(std::string& name)
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
			_rent_money = 500;
			(*it)->setproperty((*it)->getproperty() - _now_pri);
		}
		else
		{
			_owner = name;
			_rent_money = 500;
			(*it)->setproperty((*it)->getproperty() - _now_pri - 500);
		}
		_rank = 1;
	}
}

void comhouse3::rent()
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

void comhouse3::mortgage()
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

void comhouse3::ransom()
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

void comhouse3::promote()
{
	if (!_ismortgage)
	{
		if (_rank == 1)
		{
			_rank++;
			_now_pri = 3500;
			_rent_money = 600;
		}
		else if (_rank == 2)
		{
			_rank++;
			_now_pri = 4000;
			_rent_money = 700;
		}
	}
}

void comhouse3::changetype(int type)
{

}

void comhouse3::auction()
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
		_ini_pri = 2500;
		_now_pri = 2500;
		_rank = 1;
		_rent_money = 0;
		_promote_money = 500;
		_ismortgage = false;
		_owner = "";
	}
}

bool comhouse3::init()
{
	if (!Sprite::init())
		return false;
	_ini_pri = 2500;
	_now_pri = 2500;
	_rank = 1;
	_rent_money = 0;
	_promote_money = 500;
	_ismortgage = false;
	_owner = "";
	return true;
}



comhouse4::comhouse4()
{
	_ini_pri = 3000;
	_now_pri = 3000;
	_rank = 1;
	_rent_money = 0;
	_promote_money = 1000;
	_ismortgage = false;
	_owner = "";
}

comhouse4::~comhouse4()
{

}

void comhouse4::buy(std::string& name)
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
			_rent_money = 600;
			(*it)->setproperty((*it)->getproperty() - _now_pri);
		}
		else
		{
			_owner = name;
			_rent_money = 600;
			(*it)->setproperty((*it)->getproperty() - _now_pri - 1000);
		}
		_rank = 1;
	}
}

void comhouse4::rent()
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

void comhouse4::mortgage()
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

void comhouse4::ransom()
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

void comhouse4::promote()
{
	if (!_ismortgage)
	{
		if (_rank == 1)
		{
			_rank++;
			_now_pri = 5000;
			_rent_money = 800;
		}
		else if (_rank == 2)
		{
			_rank++;
			_now_pri = 6000;
			_rent_money = 1000;
		}
	}
}

void comhouse4::changetype(int type)
{

}

void comhouse4::auction()
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
		_ini_pri = 3000;
		_now_pri = 3000;
		_rank = 1;
		_rent_money = 0;
		_promote_money = 1000;
		_ismortgage = false;
		_owner = "";
	}
}

bool comhouse4::init()
{
	if (!Sprite::init())
		return false;
	_ini_pri = 3000;
	_now_pri = 3000;
	_rank = 1;
	_rent_money = 0;
	_promote_money = 1000;
	_ismortgage = false;
	_owner = "";
	return true;
}


comhouse5::comhouse5()
{
	_ini_pri = 4000;
	_now_pri = 4000;
	_rank = 1;
	_rent_money = 0;
	_promote_money = 1000;
	_ismortgage = false;
	_owner = "";
}

comhouse5::~comhouse5()
{

}

void comhouse5::buy(std::string& name)
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
			_rent_money = 800;
			(*it)->setproperty((*it)->getproperty() - _now_pri);
		}
		else
		{
			_owner = name;
			_rent_money = 800;
			(*it)->setproperty((*it)->getproperty() - _now_pri - 1000);
		}
		_rank = 1;
	}
}

void comhouse5::rent()
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

void comhouse5::mortgage()
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

void comhouse5::ransom()
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

void comhouse5::promote()
{
	if (!_ismortgage)
	{
		if (_rank == 1)
		{
			_rank++;
			_now_pri = 6000;
			_rent_money = 1000;
		}
		else if (_rank == 2)
		{
			_rank++;
			_now_pri = 7000;
			_rent_money = 1200;
		}
	}
}

void comhouse5::changetype(int type)
{

}

void comhouse5::auction()
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
		_ini_pri = 4000;
		_now_pri = 4000;
		_rank = 1;
		_rent_money = 0;
		_promote_money = 1000;
		_ismortgage = false;
		_owner = "";
	}
}

bool comhouse5::init()
{
	if (!Sprite::init())
		return false;
	_ini_pri = 4000;
	_now_pri = 4000;
	_rank = 1;
	_rent_money = 0;
	_promote_money = 1000;
	_ismortgage = false;
	_owner = "";
	return true;
}



comhouse6::comhouse6()
{
	_ini_pri = 5000;
	_now_pri = 5000;
	_rank = 1;
	_rent_money = 0;
	_promote_money = 1000;
	_ismortgage = false;
	_owner = "";
}

comhouse6::~comhouse6()
{

}

void comhouse6::buy(std::string& name)
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
			_rent_money = 1000;
			(*it)->setproperty((*it)->getproperty() - _now_pri);
		}
		else
		{
			_owner = name;
			_rent_money = 1000;
			(*it)->setproperty((*it)->getproperty() - _now_pri - 1000);
		}
		_rank = 1;
	}
}

void comhouse6::rent()
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

void comhouse6::mortgage()
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

void comhouse6::ransom()
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

void comhouse6::promote()
{
	if (!_ismortgage)
	{
		if (_rank == 1)
		{
			_rank++;
			_now_pri = 7000;
			_rent_money = 1200;
		}
		else if (_rank == 2)
		{
			_rank++;
			_now_pri = 8000;
			_rent_money = 1500;
		}
	}
}

void comhouse6::changetype(int type)
{

}

void comhouse6::auction()
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
		_ini_pri = 5000;
		_now_pri = 5000;
		_rank = 1;
		_rent_money = 0;
		_promote_money = 1000;
		_ismortgage = false;
		_owner = "";
	}
}

bool comhouse6::init()
{
	if (!Sprite::init())
		return false;
	_ini_pri = 5000;
	_now_pri = 5000;
	_rank = 1;
	_rent_money = 0;
	_promote_money = 1000;
	_ismortgage = false;
	_owner = "";
	return true;
}



comhouse7::comhouse7()
{
	_ini_pri = 6000;
	_now_pri = 6000;
	_rank = 1;
	_rent_money = 0;
	_promote_money = 2000;
	_ismortgage = false;
	_owner = "";
}

comhouse7::~comhouse7()
{

}

void comhouse7::buy(std::string& name)
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
			_rent_money = 1200;
			(*it)->setproperty((*it)->getproperty() - _now_pri);
		}
		else
		{
			_owner = name;
			_rent_money = 1200;
			(*it)->setproperty((*it)->getproperty() - _now_pri - 2000);
		}
		_rank = 1;
	}
}

void comhouse7::rent()
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

void comhouse7::mortgage()
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

void comhouse7::ransom()
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

void comhouse7::promote()
{
	if (!_ismortgage)
	{
		if (_rank == 1)
		{
			_rank++;
			_now_pri = 10000;
			_rent_money = 1500;
		}
		else if (_rank == 2)
		{
			_rank++;
			_now_pri = 12000;
			_rent_money = 2000;
		}
	}
}

void comhouse7::changetype(int type)
{

}

void comhouse7::auction()
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
		_ini_pri = 6000;
		_now_pri = 6000;
		_rank = 1;
		_rent_money = 0;
		_promote_money = 2000;
		_ismortgage = false;
		_owner = "";
	}
}

bool comhouse7::init()
{
	if (!Sprite::init())
		return false;
	_ini_pri = 6000;
	_now_pri = 6000;
	_rank = 1;
	_rent_money = 0;
	_promote_money = 2000;
	_ismortgage = false;
	_owner = "";
	return true;
}



comhouse8::comhouse8()
{
	_ini_pri = 7000;
	_now_pri = 7000;
	_rank = 1;
	_rent_money = 0;
	_promote_money = 2000;
	_ismortgage = false;
	_owner = "";
}

comhouse8::~comhouse8()
{

}

void comhouse8::buy(std::string& name)
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
			_rent_money = 1400;
			(*it)->setproperty((*it)->getproperty() - _now_pri);
		}
		else
		{
			_owner = name;
			_rent_money = 1400;
			(*it)->setproperty((*it)->getproperty() - _now_pri - 2000);
		}
		_rank = 1;
	}
}

void comhouse8::rent()
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

void comhouse8::mortgage()
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

void comhouse8::ransom()
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

void comhouse8::promote()
{
	if (!_ismortgage)
	{
		if (_rank == 1)
		{
			_rank++;
			_now_pri = 12000;
			_rent_money = 2000;
		}
		else if (_rank == 2)
		{
			_rank++;
			_now_pri = 14000;
			_rent_money = 2500;
		}
	}
}

void comhouse8::changetype(int type)
{

}

void comhouse8::auction()
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
		_ini_pri = 7000;
		_now_pri = 7000;
		_rank = 1;
		_rent_money = 0;
		_promote_money = 2000;
		_ismortgage = false;
		_owner = "";
	}
}

bool comhouse8::init()
{
	if (!Sprite::init())
		return false;
	_ini_pri = 7000;
	_now_pri = 7000;
	_rank = 1;
	_rent_money = 0;
	_promote_money = 2000;
	_ismortgage = false;
	_owner = "";
	return true;
}


comhouse9::comhouse9()
{
	_ini_pri = 8000;
	_now_pri = 8000;
	_rank = 1;
	_rent_money = 0;
	_promote_money = 2000;
	_ismortgage = false;
	_owner = "";
}

comhouse9::~comhouse9()
{

}

void comhouse9::buy(std::string& name)
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
			_rent_money = 1600;
			(*it)->setproperty((*it)->getproperty() - _now_pri);
		}
		else
		{
			_owner = name;
			_rent_money = 1600;
			(*it)->setproperty((*it)->getproperty() - _now_pri - 2000);
		}
		_rank = 1;
	}
}

void comhouse9::rent()
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

void comhouse9::mortgage()
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

void comhouse9::ransom()
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

void comhouse9::promote()
{
	if (!_ismortgage)
	{
		if (_rank == 1)
		{
			_rank++;
			_now_pri = 14000;
			_rent_money = 3000;
		}
		else if (_rank == 2)
		{
			_rank++;
			_now_pri = 16000;
			_rent_money = 3000;
		}
	}
}

void comhouse9::changetype(int type)
{

}

void comhouse9::auction()
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
		_ini_pri = 8000;
		_now_pri = 8000;
		_rank = 1;
		_rent_money = 0;
		_promote_money = 2000;
		_ismortgage = false;
		_owner = "";
	}
}

bool comhouse9::init()
{
	if (!Sprite::init())
		return false;
	_ini_pri = 8000;
	_now_pri = 8000;
	_rank = 1;
	_rent_money = 0;
	_promote_money = 2000;
	_ismortgage = false;
	_owner = "";
	return true;
}



bank::bank()
{
	_wage = 1000;
}

bank::~bank()
{

}

bool bank::init()
{
	if (Sprite::init())
	{
		return false;
	}
	_wage = 1000;
	return true;
}

bool prison::init()
{
	if (Sprite::init())
		return false;
	return true;
}
