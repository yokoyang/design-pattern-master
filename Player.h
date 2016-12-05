#pragma once
#pragma warning(disable:4996)
#include"cocos2d.h"
#include"Ui.h"

USING_NS_CC;

class Player :public Sprite
class player :public VirtualPlayer
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
	Vector<SpriteFrame*> _Left;
	Vector<SpriteFrame*> _Right;
	Vector<SpriteFrame*> _Down;
	Vector<SpriteFrame*> _Up;

	//The ID of the character' estates of level 1,2,3
	std::vector<int>_id;

	//Initiate the animation
	void _InitAnimate();
	void _SetAnimate();
	
	//The number animation to show the steps to take
	void _AddStep_image_running(std::vector<int>pathrow, std::vector<int>pathcol);
public:
	std::vector<int>vec;
	Animate* left;
	Animate* right;
	Animate* up;
	Animate* down;
	Player();
	~Player();

	//Deal with turnme,whether the character can move
	void Set_turnMe(bool turn){ _turnMe = turn; };
	bool get_turnMe(){ return _turnMe; };

	//Deal with the coming directon coordinate
	int Get_comeX(){ return _comeX; };
	int Get_comeY(){ return _comeY; };
	void Set_comeX(int comex){ this->_comeX = comex; };
	void Set_comeY(int comey){ this->_comeY = comey; };

	//Initaite the player info
	virtual bool Init();
	static Player* createwith (char* name, int tag, SpriteFrame* imag, float& money);
	CREATE_FUNC(Player);

	//Set pathrow and pathcol after the acquisition of the path
	void InitPathRowAndCol();
	void SetTileSize(float tilewidth, float tileheigh);

	//Deal with the money
	void SetMoney(float money){ _money = money; };
	float GetMoney(){ return _money; };

	//Get personal info
	Label* Get_name(){ return _name; };
	Label* Get_moneyString(){ return _moneyString; };
	int Get_stayRounds(){ return _stayRounds; };
	void Set_stayRounds(int i){ _stayRounds = i; };

	//Begin the player's motion
	void Go(std::vector<int>pathrow,std::vector<int>pathcol);

	//Set the ID of the estates of the player of level 1,2,3
	void Set_id(int id1, int id2, int id3){ _id.push_back(id1); _id.push_back(id2); _id.push_back(id3); };
	std::vector<int> Get_id(){ return _id; };

	//Acquire a lottery
	void GetLottery();

};