#pragma once
#pragma warning(disable:4996)
#include<cocos2d.h>
#include<string>
#include<vector>
#include<player.h>

USING_NS_CC;

class Opportunity :public Layer
{
public:
	//Constructor and Destructor
	Opportunity();
	~Opportunity();


	virtual bool init();

	//Returns a layer showing the event
	Layer* getShowOnScreen();

	//Adds particle system
	static void addparticle();

	//Pure virtual function to be overrided, realize the event 
	virtual bool RunAction(player*) = 0;

	std::string getCauses(){ return Causes; };

	//Preload all the pictures needed to show on screen
	static void Load();
protected:
	//A string giving account of the event
	std::string Causes;
};

//Make the character move forward
class Forwards :public Opportunity
{
public:
	//Constructor and Destructor
	Forwards();
	~Forwards();

	virtual bool init();
	CREATE_FUNC(Forwards);

	//Realize the event
	virtual bool RunAction(player*) override;

	//Returns a pointer to a Forwards object ,causes for Opportunity::causes,steps for Forwards::steps
	static Forwards* createWithSteps(std::string, int);
	//Returns the single instance
	static std::vector<Forwards*>* getInstance(){ return &Instances; };
protected:
	//Steps to take
	int Steps;
	//Single instance
	static std::vector <Forwards*> Instances;
};

class Delay :public Opportunity
{
public:
	//Constructors and destructors
	Delay();
	~Delay();


	virtual bool init();
	CREATE_FUNC(Delay);

	//Realize the event
	virtual bool RunAction(player*) override;

	//Create a Delay object,with Opportunity::causes, rounds, status
	static Delay* createWithRoundsAndStatus(std::string, int, int);
	//Return the single instance
	static std::vector<Delay*>* getInstance(){ return &Instances; };
protected:
	int Rounds;
	int Status = 0;                              //0 stands for staying at the original place, 1 for going to hospital, 2 for going to jail
	static std::vector <Delay*> Instances;
};

class Wealth :public Opportunity
{
public:
	//Constructors and Destructors
	Wealth();
	~Wealth();

	virtual bool init();
	CREATE_FUNC(Wealth);

	//Realize the event
	virtual bool RunAction(player*) override;

	//Creates the Wealth Object
	static Wealth* createWithProfit(std::string, int);
	//Returns the single instance
	static std::vector<Wealth*>* getInstance(){ return &Instances; };
protected:
	//The money the character will gain, below zero if the character will lose money
	int Profit;
	static std::vector <Wealth*> Instances;
};


class Lottery :public Sprite
{
public:
	//Constructor and destructor
	Lottery();
	~Lottery();

	//Adds a lottery publishing animation
	void addAnimation();

	virtual bool init();
	CREATE_FUNC(Lottery);
	CC_SYNTHESIZE(Animate*, normal_anmi, Normal_anmi);
private:
	SpriteFrameCache* Sprite_Frame;
	char* name;
	Vector<SpriteFrame*> animate;
	void setItemAnimate();
};