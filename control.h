#pragma once
#pragma warning(disable:4996)
#include"cocos2d.h"
#include"Player.h"

USING_NS_CC;

class Control :public Layer
{
public:
	//Constructor
	Control();

	//Destructor
	~Control();

	//Single Instance
	static Control* control_Instance;
	static Control* GetInstance();

	//The current character starts moving 
	//rowVector and colVector stores the path of the current character
	//Player points to the current character
	void StartGo(std::vector<int> rowVector, std::vector<int> colVector, Player* Player);

	//Move the character one step ahead
	void MoveOne(Player* richerPlayer);

	//Deal with the events when the character has finished moving and ended up in one specific tile
	void EndGo();
	void EndEvent();

	//Return an autoreleases control object
	CREATE_FUNC(Control);
	virtual bool Init();

	//Non-player characters Move
	void RobotWalk();

	//Add a registry in order to call some certain functions
	void Res_Notification_Observe();

	//Registry Callback
	void Receivemsg(Object*);

	//The remaining characters initiation
	void ResetPlayerGoTurn();

	//Lottery publish
	void Poplottery();

private:
	//Path
	std::vector<int> pathrow;
	std::vector<int> pathcol;
	float tilewidth = 32;
	float tileheigh = 32;

	//The coordinate from whcih the character come
	int comeX;
	int comeY;

	//Steps completed
	int step;

	//Total Steps
	int stepCount;
	int nowRow;
	int nowCol;
	//Coordinate of next step
	int row;
	int col;

	//Whether a entire round has reached an end
	bool oneRoundend;

	//Current character
	Player* Player;
	Sprite* image;

};


