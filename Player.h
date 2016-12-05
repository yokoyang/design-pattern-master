#pragma once
#pragma warning(disable:4996)
#include"cocos2d.h"
#include"Ui.h"

USING_NS_CC;

class Player :public Sprite
{
protected:
	//The player's name , shown on screen
	Label* _name;

	//The property
	float _money;
	float _saveMoney;
	//The path
	std::vector<int> _pathRow;
	std::vector<int> _pathCol;
	float _tilewidth=32;
	float _tileheigh=32;

	//Coming direction
	int _comeX;
	int _comeY;

	//Steps taken
	int _step;
	
	//Steps in total
	int _stepCount;

	//Current coordinate
	int _nowRow;
	int _nowCol;

	//The coordinate of next step
	int _row;
	int _col;

	//Rounds to stay 
	int _stayRounds;
	//Whether the player is able to move
	bool _turnMe;

	//Whether the round has ended
	bool _oneRoundend;

	//Get a string to show property
	Label* _moneyString;

	//Animation names
	char _leftAnimation[20];
	char _rightAnimation[20];
	char _downAnimation[20];
	char _upAnimation[20];

	//Animations
	Vector<SpriteFrame*> Left;
	Vector<SpriteFrame*> Right;
	Vector<SpriteFrame*> Down;
	Vector<SpriteFrame*> Up;

	//The ID of the character' estates of level 1,2,3
	std::vector<int>_id;

	//Initiate the animation
	void InitAnimate();
	void SetAnimate();
	
	//The number animation to show the steps to take
	void AddStep_image_running(std::vector<int>pathRow, std::vector<int>pathCol);
public:
	std::vector<int>vec;
	Animate* left;
	Animate* right;
	Animate* up;
	Animate* down;
	player();
	~player();

	//Deal with turnMe,whether the character can move
	void Set_turnMe(bool turn){ _turnMe = turn; };
	bool Get_turnMe(){ return _turnMe; };

	//Deal with the coming directon coordinate
	int Get_comeX(){ return _comeX; };
	int Get_comeY(){ return _comeY; };
	void Set_comeX(int _comeX){ this->_comeX = _comeX; };
	void Set_comeY(int comeY){ this->_comeY = comeY; };

	//Initaite the player info
	virtual bool Init();
	static Player* Createwith (char* name, int tag, SpriteFrame* imag, float& money);
	CREATE_FUNC(player);

	//Set pathRow and pathCol after the acquisition of the path
	void InitPathRowAndCol();
	void SettileSize(float tilewidth, float tileheigh);

	//Deal with the money
	void SetMoney(float money){ _money = money; };
	float GetMoney(){ return _money; };

	//Get personal info
	Label* GetName(){ return _name; };
	Label* Get_moneyString(){ return _moneyString; };
	int Get_stayRounds(){ return _stayRounds; };
	void Set_stayRounds(int i){ _stayRounds = i; };

	//Begin the player's motion
	void Go(std::vector<int>pathRow,std::vector<int>pathCol);

	//Set the ID of the estates of the player of level 1,2,3
	void Set_id(int id1, int id2, int id3){ _id.push_back(id1); _id.push_back(id2); _id.push_back(id3); };
	std::vector<int> Get_id(){ return _id; };

	//Acquire a lottery
	void GetLottery();

};