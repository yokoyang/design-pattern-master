#pragma once
#pragma warning(disable:4996)
#include"cocos2d.h"
#include"player.h"


USING_NS_CC;

class route
{
public:
	route();
	~route();

	//Returns the single instance
	static route* getInstance();

	//Acquire the path the players are to take 
	void getpath(player* playername, bool** iswalk, int step, int colcount, int rowcount);

	//Decide which of the four directions are accessible
	bool iscango(int x, int y, int dir, bool**);

	//Set the tile size
	void settilesize(float tilewidth, float tileheigh);

	std::vector<int> getpathrow(){ return pathrow; };
	std::vector<int> getpathcol(){ return pathcol; };
private:
	static route* Route;
	std::vector<int> pathrow;
	std::vector<int> pathcol;

	//Coming direction, avoided 
	int comex;
	int comey;
	float tilewidth=32;
	float tileheigh=32;
};