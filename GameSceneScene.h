#ifndef __GameScene_SCENE_H__
#define __GameScene_SCENE_H__
#pragma warning(disable:4996)
#include "cocos2d.h"
#include"Player.h"
#include"Route.h"
#include"Control.h"
#include"Ui.h"
#include"PopupLayer.h"

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* CreateScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool Init();
    
   
    
    // implement the "static Create()" method manually
    Create_FUNC(GameScene);

	//Get the coordinate in the map where the character can move to
	void GetWayGild();


	//Acquire isWalk
	bool** isWalk();

	//Returns the container of step marker
	static Vector<Sprite*>* GetStep_image(){ return step_image; };


	//Acquire a container of characters
	static Vector<Player*>* GetPlayers(){ return players; };

	//Acquire the character number
	static int GetPlayerNumber(){ return playerNumber; };

	//Set the character number
	static void SetPlayerNumber(int t){ playerNumber = t; };
	
	//Set the map type
	static void SetMap_type(int i){ map_type = i; };
	
	// True to indicate the place accessible,false otherwise
	static bool** isWalk;

	//Acquire the Layer"Land"
	static TMXLayer* GetLandLayer(){ return land; };

	//Acquire the map
	static TMXTiledMap* Getmap(){ return map; };

	//Display a dialog to ask whether to purchase estates
	static void show_buy_land_dialog(int);
	static float buy_land_x;
	static float buy_land_y;

	//Update the character's money 
	static void UpdateMoney(Player*, int money);
	bool** GetIsWalk();

	//Add all sorts of game resources
	void AddInfor(float);

	//Acquire the rows and columns of the map
	static int GetRowCount(){ return rowCount; };
	static int GetColCount(){ return colCount; };

	//Get the ID of the vacant land
	static int GetLand_id(){ return land_id; };

	//Acquire the go button
	static Sprite* GetGo(){ return go; };

	//Aquire the ID where there are question marks
	static int GetQuesmark_id(){ return quesmark_id; };

	//Acuire the container of location pictures
	static Vector<Sprite*>* GetLocation_image(){ return location_image; };

	//Acquire the dialog of lottery publishing 
	static PopupLayer* GetDialogLottery(){ return dialogLottery; };


	//Add progress timer
	void AddProgressTimer();

	//Update the progress timer
	void Update(float);


private:

	Sprite* progressBgSprite;
	ProgressTimer* progress1;
	Label* numsTTF;
	static int land_id;
	static int playerNumber;
	static Vector<Player*>*players;
	Size visibleSize;
	static TMXTiledMap* map;
	
	//The player
	Player* player1;
	static Vector<Sprite*> * playerImg;
	
	//The width and height of a single tile
	float tilewidth;
	float tileheigh;
	std::vector<Vec2> point;

	static Vector<Sprite*>* step_image;

	static PopupLayer* dialog;
	static PopupLayer* dialogLottery;
	//Vacant land
	static TMXLayer* land;
	static TMXLayer* wenhao;
	static int quesmark_id;
	void reg_notification_Observe();

	void Received_MSG(Object*);

	static Vector<Sprite*>area_land;

	static Layer* final_layer;
	
	static int rowCount;
	static int colCount;
	static Sprite* go;
	static Vector<Sprite*>* location_image;
	static int map_type;
	
	void AddFinal_layer();
	void Add_location_image();

	Player* GetId(int ID);
	int AreaLand_pay(float x, float y, Player*, int id1, int id2, int id3);
	//Add map
	void AddMap(int type);
	//Add players images
	void AddPlayerImg();
	//Add the info of the characters
	void AddPlayerInformation(int number);
	//Add players of number 'number'
	void AddPlayer(int number);
	//Add dice to Layer*
	void AddShaiZi(Layer*);

	
	void SetIsWalk();

	void AddStep_image();

	void AddDialog();
	void AddDialogLottery();

	void BuyLand(Node*);
};

#endif // __GameScene_SCENE_H__
