#pragma once
#pragma warning(disable:4996)
#include"cocos2d.h"

class AbstractHouse :public Sprite
{
public:
	AbstractHouse();
	~AbstractHouse();
    // 一些抽象行为，放到子类去实现
	virtual void Buy(std::string& name);
	virtual void Rent();
	virtual void Mortgage();
	virtual void Ransom();
	virtual void Auction();
	virtual void Promote();
	virtual void ChangeType(int type);
	virtual bool IsInit();
	CREATE_FUNC(AbstractHouse);

    // 模板方法，给出了逻辑的骨架，而逻辑的组成是一些相应的抽象操作，推迟到子类去实现
    void TemplateChooseMethod();

    
protected:
	float _iniPri;
	float _nowPri;
	int _rank;
	float _rentMoney;
	std::string _owner;
	bool _isMortgage;
	float _promoteMoney;
    virtual void PayMoney()
    {

        cout<<"Default payMoney Operation"<<endl;
    }
    virtual void HappenAccident()
    {
        cout<<"Default happenAccident Operation1"<<endl;
    }
}
