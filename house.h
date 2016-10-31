#pragma once
#include"cocos2d.h"
#include"player.h"
#include<string>
USING_NS_CC;

class house :public Sprite
{
public:
	house();
	~house();
	virtual void buy(std::string& name);
	virtual void rent();
	virtual void mortgage();
	virtual void ransom();
	virtual void auction();
	virtual void promote();
	virtual void changetype(int type);
	virtual bool init();
	CREATE_FUNC(house);
protected:
	float _ini_pri;
	float _now_pri;
	int _rank;
	float _rent_money;
	std::string _owner;
	bool _ismortgage;
	float _promote_money;
};


class comhouse1 :public house
{
public:
	comhouse1();
	~comhouse1();
	virtual void buy(std::string& name);
	virtual void rent();
	virtual void mortgage();
	virtual void ransom();
	virtual void auction();
	virtual void promote();
	virtual void changetype(int type);
	virtual bool init();
	CREATE_FUNC(comhouse1);
protected:

};



class comhouse2 :public house
{
public:
	comhouse2();
	~comhouse2();
	virtual void buy(std::string& name);
	virtual void rent();
	virtual void mortgage();
	virtual void ransom();
	virtual void auction();
	virtual void promote();
	virtual void changetype(int type);
	virtual bool init();
	CREATE_FUNC(comhouse2);
protected:
};



class comhouse3 :public house
{
public:
	comhouse3();
	~comhouse3();
	virtual void buy(std::string& name);
	virtual void rent();
	virtual void mortgage();
	virtual void ransom();
	virtual void auction();
	virtual void promote();
	virtual void changetype(int type);
	virtual bool init();
	CREATE_FUNC(comhouse3);
protected:
};


class comhouse4 :public house
{
public:
	comhouse4();
	~comhouse4();
	virtual void buy(std::string& name);
	virtual void rent();
	virtual void mortgage();
	virtual void ransom();
	virtual void auction();
	virtual void promote();
	virtual void changetype(int type);
	virtual bool init();
	CREATE_FUNC(comhouse4);
protected:
};


class comhouse5 :public house
{
public:
	comhouse5();
	~comhouse5();
	virtual void buy(std::string& name);
	virtual void rent();
	virtual void mortgage();
	virtual void ransom();
	virtual void auction();
	virtual void promote();
	virtual void changetype(int type);
	virtual bool init();
	CREATE_FUNC(comhouse5);
protected:
};


class comhouse6 :public house
{
public:
	comhouse6();
	~comhouse6();
	virtual void buy(std::string& name);
	virtual void rent();
	virtual void mortgage();
	virtual void ransom();
	virtual void auction();
	virtual void promote();
	virtual void changetype(int type);
	virtual bool init();
	CREATE_FUNC(comhouse6);
protected:
};


class comhouse7 :public house
{
public:
	comhouse7();
	~comhouse7();
	virtual void buy(std::string& name);
	virtual void rent();
	virtual void mortgage();
	virtual void ransom();
	virtual void auction();
	virtual void promote();
	virtual void changetype(int type);
	virtual bool init();
	CREATE_FUNC(comhouse7);
protected:
};


class comhouse8 :public house
{
public:
	comhouse8();
	~comhouse8();
	virtual void buy(std::string& name);
	virtual void rent();
	virtual void mortgage();
	virtual void ransom();
	virtual void auction();
	virtual void promote();
	virtual void changetype(int type);
	virtual bool init();
	CREATE_FUNC(comhouse8);
protected:
};


class comhouse9 :public house
{
public:
	comhouse9();
	~comhouse9();
	virtual void buy(std::string& name);
	virtual void rent();
	virtual void mortgage();
	virtual void ransom();
	virtual void auction();
	virtual void promote();
	virtual void changetype(int type);
	virtual bool init();
	CREATE_FUNC(comhouse9);
protected:
};


class bank :public house
{
protected:
	float _wage;
public:
	bank();
	~bank();
	float getwage(){ return _wage; };
	virtual bool init();
	CREATE_FUNC(bank);
};


class prison :public house
{
protected:
	virtual bool init();
	CREATE_FUNC(prison);
private:
};
