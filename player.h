#pragma once
#pragma warning(disable:4996)
#include"cocos2d.h"
#include"Ui.h"

USING_NS_CC;

class player :public VirtualPlayer
{

private:
	
	//The ID of the character' estates of level 1,2,3
	int _id;
	
public:
	Player();
	~Player();

	//Deal with the coming directon coordinate
	int Get_comeX(){ return _comeX; };
	int Get_comeY(){ return _comeY; };
	void Set_comeX(int comex){ this->_comeX = comex; };
	void Set_comeY(int comey){ this->_comeY = comey; };

	//Initaite the player info
	virtual bool Init();


	//Get personal info
	Label* Get_name(){ return _name; };
	Label* Get_moneyString(){ return _moneyString; };
	int Get_stayRounds(){ return _stayRounds; };



	//Set the ID of the estates of the player of level 1,2,3
	void Set_id(int id){
		_id = id;
	};
	std::vector<int> Get_id(){ return _id; };

};