#pragma once
#pragma warning(disable:4996)
#include"cocos2d.h"
#include"Ui.h"

USING_NS_CC;

class player :public VirtualPlayer
{
	
private:
	player();
	~player();
	//Initaite the player info
	virtual bool init();
	CREATE_FUNC(player);
	void settilesize(float tilewidth, float tileheigh);
	//Set the ID of the estates of the player of level 1,2,3
	void set_id(int id1, int id2, int id3){ id.push_back(id1); id.push_back(id2); id.push_back(id3); };
	std::vector<int> get_id(){ return id; };

};