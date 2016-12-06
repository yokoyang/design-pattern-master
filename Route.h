#pragma once
#pragma warning(disable:4996)
#include"cocos2d.h"
#include"Player.h"


USING_NS_CC;

class Route
{
public:
	Route();
	~Route();

	//Returns the single instance
	static Route* GetInstance();

	//Acquire the path the players are to take 
	void GetPath(Player* playername, bool** iswalk, int step, int colcount, int rowcount);

	//Decide which of the four directions are accessible
	bool IsCango(int x, int y, int dir, bool**);

	//Set the tile size
	void SetTilesize(float tilewidth, float tileheigh);

	std::vector<int> GetPathrow(){ return pathrow; };
	std::vector<int> GetPathcol(){ return pathcol; };
private:
	static Route* route;
	std::vector<int> pathrow;
	std::vector<int> pathcol;

	//Coming direction, avoided 
	int comeX;
	int comeY;
	float tilewidth=32;
	float tileheigh=32;
};
