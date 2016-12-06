#pragma once
#pragma warning(disable:4996)
#include"cocos2d.h"
#include"player.h"

USING_NS_CC;

class control :public Layer
{
public:
	//Constructor
	control();

	//Destructor
	~control();

	//Single Instance
	static control* control_Instance;
	static control* getInstance();

	//The current character starts moving 
	//rowVector and colVector stores the path of the current character
	//Player points to the current character
	void startgo(std::vector<int> rowVector, std::vector<int> colVector, player* Player);

	//Move the character one step ahead
	void moveone(player* richerPlayer);

	//Deal with the events when the character has finished moving and ended up in one specific tile
	void endGo();
	void endevent();

	//Return an autoreleases control object
	CREATE_FUNC(control);
	virtual bool init();

	//Non-player characters Move
	void robotwalk();

	//Add a registry in order to call some certain functions
	void res_notification_Observe();

	//Registry Callback
	void receivemsg(Object*);

	//The remaining characters initiation
	void resetPlayerGoTurn();

	//Lottery publish
	void poplottery();

private:
	//Path
	std::vector<int> pathrow;
	std::vector<int> pathcol;
	float tilewidth = 32;
	float tileheigh = 32;

	//The coordinate from whcih the character come
	int comex;
	int comey;

	//Steps completed
	int _step;

	//Total Steps
	int _stepcount;
	int nowrow;
	int nowcol;
	//Coordinate of next step
	int row;
	int col;

	//Whether a entire round has reached an end
	bool oneroundend;

	//Current character
	player* Player;
	Sprite* image;

};


