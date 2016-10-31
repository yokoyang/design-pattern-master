#ifndef __GameScene_SCENE_H__
#define __GameScene_SCENE_H__
#pragma warning(disable:4996)
#include "cocos2d.h"
#include"player.h"
#include"route.h"
#include"control.h"
#include"Ui.h"
#include"PopupLayer.h"

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
   
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

	//Get the coordinate in the map where the character can move to
	void getwaygild();


	//Acquire iswalk
	bool** getiswalk();

	//Returns the container of step marker
	static Vector<Sprite*>* getstep_image(){ return step_image; };


	//Acquire a container of characters
	static Vector<player*>* getplayers(){ return players; };

	//Acquire the character number
	static int getplayernumber(){ return playernumber; };

	//Set the character number
	static void setplayernumber(int t){ playernumber = t; };
	
	//Set the map type
	static void set_maptype(int i){ map_type = i; };
	
	// True to indicate the place accessible,false otherwise
	static bool** iswalk;

	//Acquire the Layer"Land"
	static TMXLayer* getlandlayer(){ return land; };

	//Acquire the map
	static TMXTiledMap* getmap(){ return map; };

	//Display a dialog to ask whether to purchase estates
	static void show_buy_land_dialog(int);
	static float buy_land_x;
	static float buy_land_y;

	//Update the character's money 
	static void update_money(player*, int money);

	//Add all sorts of game resources
	void add_infor(float);

	//Acquire the rows and columns of the map
	static int getrow_count(){ return rowcount; };
	static int getcol_count(){ return colcount; };

	//Get the ID of the vacant land
	static int getland_id(){ return land_id; };

	//Acquire the go button
	static Sprite* get_go(){ return go; };

	//Aquire the ID where there are question marks
	static int get_wenhao_id(){ return wenhao_id; };

	//Acuire the container of location pictures
	static Vector<Sprite*>* get_location_image(){ return location_image; };

	//Acquire the dialog of lottery publishing 
	static PopupLayer* get_dialoglottery(){ return dialoglottery; };


	//Add progress timer
	void addProgressTimer();

	//Update the progress timer
	void update(float);


private:

	Sprite* progressbgSprite;
	ProgressTimer* progress1;
	Label* numsTTF;
	static int land_id;
	static int playernumber;
	static Vector<player*>*players;
	Size visibleSize;
	static TMXTiledMap* map;
	
	//The player
	player* player1;
	static Vector<Sprite*> * playerimg;
	
	//The width and height of a single tile
	float tilewidth;
	float tileheigh;
	std::vector<Vec2> point;

	static Vector<Sprite*>* step_image;

	static PopupLayer* dialog;
	static PopupLayer* dialoglottery;
	//Vacant land
	static TMXLayer* land;
	static TMXLayer* wenhao;
	static int wenhao_id;
	void reg_notification_Observe();

	void received_MSG(Object*);

	static Vector<Sprite*>area_land;

	static Layer* final_layer;
	
	static int rowcount;
	static int colcount;
	static Sprite* go;
	static Vector<Sprite*>* location_image;
	static int map_type;
	
	void addFinal_layer();
	void add_location_image();

	player* get_land_owner(int ID);
	int area_land_pay(float x, float y, player*, int id1, int id2, int id3);
	//Add map
	void addmap(int type);
	//Add players images
	void addplayerimg();
	//Add the info of the characters
	void addplayerinformation(int number);
	//Add players of number 'number'
	void addplayer(int number);
	//Add dice to Layer*
	void addshaizi(Layer*);

	
	void setiswalk();

	void addstep_image();

	void adddialog();
	void adddialoglottery();

	void buyland(Node*);
};

#endif // __GameScene_SCENE_H__
