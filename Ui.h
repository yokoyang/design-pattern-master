#pragma once
#pragma warning(disable:4996)
#include"cocos2d.h"

USING_NS_CC;

//Coordinate interchange and string dealing
class Ui
{
public:
	static Point chang_map_to_GL(Point& mappoint, TMXTiledMap* map);
	static Point chang_GL_to_map(Point& glpoint, TMXTiledMap* map);
	static Vector<String*> SplitString(const char* srcStr, const char* sSep);
private:
};