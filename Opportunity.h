#pragma once
#pragma warning(disable:4996)
#include<cocos2d.h>
#include<string>
#include<vector>
#include "Player.h"

USING_NS_CC;

class Opportunity :public Layer
{
public:
	//Constructor and Destructor
	Opportunity();
	~Opportunity();


	virtual bool Init();

	//Returns a layer showing the event
	Layer* GetShowOnScreen();

	//Adds particle system
	static void AddParticle();

	//Pure virtual function to be overrided, realize the event 
	virtual bool RunAction(Player*) = 0;

	std::string GetCauses(){ return _causes; };

	//Preload all the pictures needed to show on screen
	static void Load();
protected:
	//A string giving account of the event
	std::string _causes;
};

//Make the character move forward
class Forwards :public Opportunity
{
public:
	//Constructor and Destructor
	Forwards();
	~Forwards();

	virtual bool Init();
	CREATE_FUNC(Forwards);

	//Realize the event
	virtual bool RunAction(Player*) override;

	//Returns a pointer to a Forwards object ,causes for Opportunity::causes,steps for Forwards::steps
	static Forwards* CreateWithSteps(std::string, int);
	//Returns the single instance
	static std::vector<Forwards*>* GetInstance(){ return &_instances; };
protected:
	//Steps to take
	int _steps;
	//Single instance
	static std::vector <Forwards*> _instances;
};

class Delay :public Opportunity
{
public:
	//Constructors and destructors
	Delay();
	~Delay();


	virtual bool Init();
	CREATE_FUNC(Delay);

	//Realize the event
	virtual bool RunAction(Player*) override;

	//Create a Delay object,with Opportunity::causes, rounds, status
	static Delay* CreateWithRoundsAndStatus(std::string, int, int);
	//Return the single instance
	static std::vector<Delay*>* GetInstance(){ return &_instances; };
protected:
	int rounds;
	int status = 0;                              //0 stands for staying at the original place, 1 for going to hospital, 2 for going to jail
	static std::vector <Delay*> _instances;
};

class Wealth :public Opportunity
{
public:
	//Constructors and Destructors
	Wealth();
	~Wealth();

	virtual bool Init();
	CREATE_FUNC(Wealth);

	//Realize the event
	virtual bool RunAction(Player*) override;

	//Creates the Wealth Object
	static Wealth* CreateWithProfit(std::string, int);
	//Returns the single instance
	static std::vector<Wealth*>* GetInstance(){ return &_instances; };
protected:
	//The money the character will gain, below zero if the character will lose money
	int _profit;
	static std::vector <Wealth*> _instances;
};


class Lottery :public Sprite
{
public:
	//Constructor and destructor
	Lottery();
	~Lottery();

	//Adds a lottery publishing animation
	void AddAnimation();

	virtual bool Init();
	CREATE_FUNC(Lottery);
	CC_SYNTHESIZE(Animate*, normal_anmi, Normal_anmi);
private:
	SpriteFrameCache* spriteFrame;
	char* name;
	Vector<SpriteFrame*> animate;
	void SetItemAnimate();
};