#pragma once
#pragma warning(disable:4996)
#include"cocos2d.h"
#include"Ui.h"

USING_NS_CC;

class VirtualPlayer :public Sprite
{
protected:
	//The player's name , shown on screen
	Label* _name;
	//The property
	float _money;
	float saveMony;
	//The path
	std::vector<int> pathrow;
	std::vector<int> pathcol;
	float tilewidth=32;
	float tileheigh=32;
	//Coming direction
	int comex;
	int comey;
	//Steps taken
	int _step;
	//Steps in total
	int _stepcount;
	//Current coordinate
	int nowrow;
	int nowcol;
	//The coordinate of next step
	int row;
	int col;
	//Rounds to stay 
	int stayRounds;
	//Whether the player is able to move
	bool turnme;
	//Whether the round has ended
	bool oneroundend;
	//Get a string to show property
	Label* money_string;
	//Animation names
	char left_animation[20];
	char right_animation[20];
	char down_animation[20];
	char up_animation[20];
	//Animations
	Vector<SpriteFrame*>Left;
	Vector<SpriteFrame*>Right;
	Vector<SpriteFrame*>Down;
	Vector<SpriteFrame*>Up;
	//The ID of the character' estates of level 1,2,3
	std::vector<int>id;
	//Initiate the animation
	void initAnimate();
	void setAnimate();
	//The number animation to show the steps to take
	void addstep_image_running(std::vector<int>pathrow, std::vector<int>pathcol);
public:
	std::vector<int>vec;
	Animate* left;
	Animate* right;
	Animate* up;
	Animate* down;
	player();
	~player();
	//Deal with turnme,whether the character can move
	void setturnme(bool turn){ turnme = turn; };
	bool getturnme(){ return turnme; };
	//Deal with the coming directon coordinate
	int getcomex(){ return comex; };
	int getcomey(){ return comey; };
	void setcomex(int comex){ this->comex = comex; };
	void setcomey(int comey){ this->comey = comey; };
	static player* createwith (char* name, int tag, SpriteFrame* imag, float& money);
	CREATE_FUNC(player);
	//Set pathrow and pathcol after the acquisition of the path
	void initpathrowandcol();
	int get_stayRounds(){ return stayRounds; };
	void set_stayRounds(int i){ stayRounds = i; };
	//Begin the player's motion
	void go(std::vector<int>pathrow,std::vector<int>pathcol);
	//Acquire a lottery
	void getLottery();
	//Set the ID of the estates of the player of level 1,2,3
	virtual void set_id(int id1, int id2, int id3){ id.push_back(id1); id.push_back(id2); id.push_back(id3); };
	virtual std::vector<int> get_id(){ return id; };
	//Get personal info
	virtual Label* get_name(){ return _name; };
	virtual Label* getmoney_string(){ return money_string; };
	virtual void settilesize(float tilewidth, float tileheigh);
	//Deal with the money
	virtual void setmoney(float money){ _money = money; };
	virtual float getmoney(){ return _money; };
	//Initaite the player info
	virtual bool init();
};