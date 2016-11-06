#pragma once
#pragma warning(disable:4996)
#include"cocos2d.h"

class house :public Sprite
{
public:
	house();
	~house();
        // 一些抽象行为，放到子类去实现
	virtual void buy(std::string& name);
	virtual void rent();
	virtual void mortgage();
	virtual void ransom();
	virtual void auction();
	virtual void promote();
	virtual void changetype(int type);
	virtual bool init();
	CREATE_FUNC(house);

    // 模板方法，给出了逻辑的骨架，而逻辑的组成是一些相应的抽象操作，推迟到子类去实现
    void TemplateMethod();

    
protected:
	float _ini_pri;
	float _now_pri;
	int _rank;
	float _rent_money;
	std::string _owner;
	bool _ismortgage;
	float _promote_money;

}
