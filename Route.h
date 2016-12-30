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
	void GetPath(Player* playername, bool** isWalk, int step, int colCount, int rowCount);

	//Decide which of the four directions are accessible
	bool IsCango(int x, int y, int dir, bool**);

	//Set the tile size
	void SetTileSize(float tileWidth, float tileHeigh);

	std::vector<int> GetPathrow(){ return pathRow; };
	std::vector<int> GetPathcol(){ return pathCol; };
private:
	static Route* route;
	std::vector<int> pathRow;
	std::vector<int> pathCol;

	//Coming direction, avoided 
	int comeX;
	int comeY;
	float tileWidth=32;
	float tileHeigh=32;
};
