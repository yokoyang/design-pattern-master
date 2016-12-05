#include "GameSceneScene.h"
#include"toast.h"
#include"FinalScene.h"
#include<string>
#include<Opportunity.h>
#include<SimpleAudioEngine.h>

USING_NS_CC;

//全局变量 global
Vector<Sprite*>* GameScene::playerimg = new Vector<Sprite*>();

Vector<player*>* GameScene::players = new Vector<player*>();
Vector<Sprite*>* GameScene::step_image = new Vector<Sprite*>();
Vector<Sprite*> GameScene::area_land;
Vector<Sprite*> * GameScene::location_image = new Vector<Sprite*>();
int GameScene::playernumber = 4;
int GameScene::map_type = 1;
bool** GameScene::iswalk = NULL;
TMXLayer* GameScene::land = NULL;
TMXLayer* GameScene::wenhao = NULL;
TMXTiledMap* GameScene::map = NULL;
PopupLayer* GameScene::dialog = NULL;
PopupLayer* GameScene::dialoglottery = NULL;
float GameScene::buy_land_x = 0;
float GameScene::buy_land_y = 0;
Layer* GameScene::final_layer = NULL;
int GameScene::rowcount = 0;
int GameScene::wenhao_id = 0;
int GameScene::colcount = 0;
int GameScene::land_id = 0;
Sprite* GameScene::go = NULL;



Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("world.jpg");
	background->setPosition(visibleSize / 2);
	background->setAnchorPoint(Vec2(0.5, 0.5));
	background->setScale(1.5);
	addChild(background);
	addProgressTimer();
	scheduleOnce(schedule_selector(GameScene::add_infor), 1.60f);

    return true;
}

//Add all sorts of game resources
void GameScene::add_infor(float t)
{
	auto Size = Director::getInstance()->getVisibleSize();
	auto layer = Layer::create();
	addmap(map_type);
	addplayerimg();
	addplayerinformation(playernumber);
	setiswalk();
	getwaygild();
	addstep_image();
	addplayer(playernumber);
	addshaizi(layer);
	reg_notification_Observe();
	addChild(layer);
	adddialog();
	adddialoglottery();
	addFinal_layer();
	Opportunity::Load();
	add_location_image();
	auto back=Sprite::create("Quit Button.png");
	back->setPosition(150, 50);
	back->setScale(0.5);
	addChild(back);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [back](Touch* t, Event* e){
		if (back->getBoundingBox().containsPoint(t->getLocation()))
		{
			Director::getInstance()->end();
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, back);
}

//Add progress timer
void GameScene::addProgressTimer()
{
	auto Size = Director::getInstance()->getVisibleSize();
	progressbgSprite = Sprite::create("slider.png");
	progressbgSprite->setPosition(Size/2);
	addChild(progressbgSprite);
	auto progressSprite1 = Sprite::create("slider.png");
	progress1 = ProgressTimer::create(progressSprite1);
	progress1->setType(kCCProgressTimerTypeBar);
	progress1->setPosition(Size/2);
	progress1->setMidpoint(Vec2(0, 0));
	progress1->setBarChangeRate(Vec2(1, 0));
	progress1->setPercentage(0);
	addChild(progress1);
	numsTTF = Label::createWithTTF("0", "fonts/Gazzarel.TTF", 18);
	numsTTF->setPosition(Vec2(300, 300));
	addChild(numsTTF, 1);
	scheduleUpdate();
}
//Update the progress timer
void GameScene::update(float t)
{
	float cu = progress1->getPercentage();
	cu = cu + 1.0f;
	if (cu >= 100)
	{
		cu = 100;
	}
	progress1->setPercentage(cu);
	String *str = String::createWithFormat("%.0f%%", cu);
	numsTTF->setString(str->getCString());
	if (cu >= 100)
	{
		numsTTF->setVisible(false);
		progress1->setVisible(false);
		progressbgSprite->setVisible(false);
	}
}

void GameScene::addFinal_layer()
{
	final_layer = FinalScene::create();
	addChild(final_layer);
	final_layer->setPosition(visibleSize / 2);
	final_layer->setVisible(false);
}

void GameScene::addmap(int type)
{
	if (type == 1)
	{
		map = TMXTiledMap::create("map1.tmx");
		auto background = Sprite::create("Sea.jpg");
		background->setAnchorPoint(Vec2(0.5, 0.5));
		background->setPosition(visibleSize / 2);
		background->setScale(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
		addChild(background);
	}
	else if (type == 2)
	{
		map = TMXTiledMap::create("map2.tmx");
		auto background = Sprite::create("Sea.jpg");
		background->setAnchorPoint(Vec2(0.5, 0.5));
		background->setPosition(visibleSize / 2);
		background->setScale(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
		addChild(background);
	}
	else if (type == 3)
	{
		map = TMXTiledMap::create("map3.tmx");
		auto background = Sprite::create("Sea.jpg");
		background->setAnchorPoint(Vec2(0.5, 0.5));
		background->setPosition(visibleSize / 2);
		background->setScale(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
		addChild(background);
	}
	addChild(map);
	map->setAnchorPoint(Point(0.5, 0.5));
	map->setPosition(visibleSize.width / 2 - 100, visibleSize.height / 2);
	Size tile = map->getTileSize();
	tilewidth = tile.width;
	tileheigh = tile.height;
	land = map->layerNamed("land");
	rowcount = map->getContentSize().height/tileheigh;
	colcount = map->getContentSize().width/tilewidth;
	wenhao = map->layerNamed("wenhao");
	if (type == 2 || type == 3)
	{
		wenhao_id = 469;
		land_id = 273;
	}
	else if (type == 1)
	{
		land_id = 870;
		wenhao_id = 1048;
	}
}



void GameScene::addplayerinformation(int number)
{
	auto it = playerimg->begin();
	for (int i = 0; i < number; i++, it++)
	{
		auto player = Sprite::create();
		player = *it;
		addChild(player);
		player->setAnchorPoint(Point(0.5,0.5));
		player->setPosition(Vec2(visibleSize.width / 24 * 19, visibleSize.height / number / 2 + (number - 1 - i) * visibleSize.height / number));
	}
}


void GameScene::addplayerimg()
{
	playerimg->clear();
	auto player1 = Sprite::create("player1.jpg");
	auto player2 = Sprite::create("player2.png");
	auto player3 = Sprite::create("player3.png");
	auto player4 = Sprite::create("player4.png");
	playerimg->pushBack(player1);
	playerimg->pushBack(player2);
	playerimg->pushBack(player3);
	playerimg->pushBack(player4);
}

void GameScene::add_location_image()
{
	if (!location_image->empty())
	{
		return;
	}

    char*picName = new char[20];
    memset(picName, 0, 20);

    for (int i = 1; i <= 40; i++)
    {
        sprintf(picName, "Location%02d.jpg", i);
        auto temp = Sprite::create(picName);
        location_image->pushBack(temp);
        addChild(temp);
        temp->setVisible(false);
        temp->setAnchorPoint(Vec2(0.5, 0.5));
        temp->setPosition(visibleSize / 2);
    }
}

void GameScene::addplayer(int number)
{
	playernumber = number;
	float money = 10000;
	auto framecache = SpriteFrameCache::getInstance();
	framecache->addSpriteFramesWithFile("player1_anim.plist", "player1_anim.png");
	auto s1 = framecache->getSpriteFrameByName("player1_anim_01.png");
	player1 = player::createwith("player1", 1, s1, money);
	player1->settilesize(tilewidth, tileheigh);
	player1->setAnchorPoint(Point(0, 0.5));
	Point q = point[0];
	q.y = tileheigh + q.y;
	map->addChild(player1);
	player1->setPosition(q);
	player1->setturnme(true);
	player1->set_id(3, 6, 9);
	framecache->addSpriteFramesWithFile("player2_anim.plist", "player2_anim.png");
	auto s2 = framecache->getSpriteFrameByName("player2_anim_01.png");
	auto player2 = player::createwith("player2", 2, s2, money);
	player2->settilesize(tilewidth, tileheigh);
	Point q1 = point[39];
	q1.y = tileheigh + q1.y;
	map->addChild(player2);
	player2->setPosition(q1);
	player2->setAnchorPoint(Point(0, 0.5));
	player2->setturnme(true);
	player2->set_id(1, 4, 7);
	framecache->addSpriteFramesWithFile("player3_anim.plist", "player3_anim.png");
	auto s3 = framecache->getSpriteFrameByName("player3_anim_01.png");
	auto player3 = player::createwith("player3", 3, s3, money);
	player3->settilesize(tilewidth, tileheigh);
	Point q2 = point[10];
	q2.y = tileheigh + q2.y;
	map->addChild(player3);
	player3->setPosition(q2);
	player3->setAnchorPoint(Point(0, 0.5));
	player3->setturnme(true);
	player3->set_id(2, 5, 8);
	framecache->addSpriteFramesWithFile("player4_anim.plist", "player4_anim.png");
	auto s4 = framecache->getSpriteFrameByName("player4_anim_01.png");
	auto player4 = player::createwith("player4", 4, s4, money);
	player4->settilesize(tilewidth, tileheigh);
	Point q3 = point[29];
	q3.y = tileheigh + q3.y;
	map->addChild(player4);
	player4->setPosition(q3);
	player4->setAnchorPoint(Point(0, 0.5));
	player4->setturnme(true);
	player4->set_id(10, 11, 12);
	players->clear();
	if (number == 4)
	{
		players->pushBack(player1);
		players->pushBack(player2);
		players->pushBack(player3);
		players->pushBack(player4);
	}
	else if (number == 3)
	{
		players->pushBack(player1);
		players->pushBack(player2);
		players->pushBack(player3);
		player4->setVisible(false);
	}
	else if (number == 2)
	{
		players->pushBack(player1);
		players->pushBack(player2);
		player3->setVisible(false);
		player4->setVisible(false);
	}
	auto it = players->begin();
	int j = 0;
	for (; it != players->end(); it++)
	{
		j++;
		char a[20] = { 0 };
		sprintf(a, "%c%d", '$', (int)(*it)->getmoney());
		(*it)->getmoney_string()->setString(a);
		(*it)->get_name()->setColor(Color3B::BLACK);
		(*it)->get_name()->setScale(1.5);
		(*it)->getmoney_string()->setPosition(visibleSize.width / 12 * 11, (number - j + 1) * visibleSize.height / number - visibleSize.height / number / 2 - 30);
		(*it)->get_name()->setPosition(visibleSize.width / 12 * 11, (number - j + 1) * visibleSize.height / number - visibleSize.height / number / 2 + 40);
		(*it)->getmoney_string()->setColor(Color3B::BLACK);
		(*it)->getmoney_string()->setScale(1.5);
		addChild((*it)->getmoney_string());
		addChild((*it)->get_name());
	}
}


//Get the coordinate in the map where the character can move to
void GameScene::getwaygild()
{
	point.clear();
	auto way = map->layerNamed("way");
	Size waysize = way->getLayerSize();
	for (int i = 0; i < waysize.width; i++)
	{
		for (int j = 1; j < waysize.height; j++)
		{
			auto p = way->tileAt(Point(i, j));
			if (p)
			{
				Vec2 P = p->getPosition();
				point.push_back(P);
				float x = p->getPositionX();
				float y = p->getPositionY();
				iswalk[(int)(y/tileheigh)][(int)(x/tilewidth)] = true;
			}
		}
	}
}

void GameScene::addshaizi(Layer* layer)
{
	srand(clock());
	int i = 0;
	go = Sprite::create("Start Button.png");
	go->setScale(0.5);
	layer->addChild(go);
	go->setAnchorPoint(Point(0,1));
	go->setPosition(Vec2(280, 80));
	auto touch = EventListenerTouchOneByOne::create();
	bool** iswalkcopy = iswalk;
	auto Go = go;
	touch->onTouchBegan = [i,iswalkcopy,Go,this](Touch* t, Event* e){
		if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation()))
		{
			Go->setVisible(false);
			Go->setPosition(Go->getPosition() - Vec2(0, 500));
			auto it = players->begin();
			int stepnumber = rand() % 6;
			route::getInstance()->getpath(*it,iswalkcopy, stepnumber + 1, colcount, rowcount);
			(*it)->go(route::getInstance()->getpathrow(), route::getInstance()->getpathcol());
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touch, go);
}


void GameScene::setiswalk()
{
	int tilerow;
	int tilecol;
	Vec2 size = map->layerNamed("way")->getLayerSize();
	tilecol = (int)size.x;
	tilerow = (int)size.y;
	iswalk = new bool*[tilerow];
	for (int i = 0; i < tilerow; i++)
	{
		iswalk[i] = new bool[tilecol];
	}
	for (int i = 0; i < tilerow; i++)
	{
		for (int j = 0; j < tilecol; j++)
		{
			iswalk[i][j] = false;
		}
	}
}


bool** GameScene::getiswalk()
{
	return iswalk;
}


void GameScene::addstep_image()
{
	step_image->clear();
	auto image1 = Sprite::create("Marker1.png");
	auto image2 = Sprite::create("Marker2.png");
	auto image3 = Sprite::create("Marker3.png");
	auto image4 = Sprite::create("Marker4.png");
	auto image5 = Sprite::create("Marker5.png");
	auto image6 = Sprite::create("Marker6.png");
	step_image->pushBack(image1);
	step_image->pushBack(image2);
	step_image->pushBack(image3);
	step_image->pushBack(image4);
	step_image->pushBack(image5);
	step_image->pushBack(image6);
	image1->setVisible(false);
	image2->setVisible(false);
	image3->setVisible(false);
	image4->setVisible(false);
	image5->setVisible(false);
	image6->setVisible(false);
	map->addChild(image1);
	map->addChild(image2);
	map->addChild(image3);
	map->addChild(image4);
	map->addChild(image5);
	map->addChild(image6);
}

void GameScene::adddialog()
{
	dialog = PopupLayer::create("dialog_bg.png");
	dialog->setContentSize(Size(400, 220));
	dialog->setTitle("buy land");
	dialog->setContentText("", 20, 60, 250);
	dialog->setCallbackFunc(this, callfuncN_selector(GameScene::buyland));
	dialog->addButton("button_bg1.png", "button_bg3.png", "OK", 1);
	dialog->addButton("button_bg2.png", "button_bg3.png", "CANCEL", 0);
	addChild(dialog);
	dialog->setVisible(false);
}

void GameScene::adddialoglottery()
{
	dialoglottery = PopupLayer::create("dialog_bg.png");
	dialoglottery->settype(1);
	dialoglottery->setContentSize(Size(400,220));
	dialoglottery->setTitle("Lottery");
	dialoglottery->setContentText("", 20, 60, 250);
	dialoglottery->setPlayerVector(*players);
	dialoglottery->setTag(100);
	this->addChild(dialoglottery);
	dialoglottery->setVisible(false);

}

void GameScene::buyland(Node* node)
{
	if (node->getTag() == 1)
	{
		Sprite* image1;
		switch (dialog->getDataTag())
		{
		case 2:
		{
			player* Player = players->at(0);
			land->setTileGID(3+land_id, Vec2(buy_land_x, buy_land_y));
			image1 = Sprite::create("house1.png");
			image1->setPosition(Ui::chang_map_to_GL( Vec2(buy_land_x, buy_land_y),map).x+16,Ui::chang_map_to_GL(Vec2(buy_land_x,buy_land_y),map).y+16);
			image1->setVisible(true);
			map->addChild(image1);
			image1->setAnchorPoint(Vec2(0.5, 0.5));
			dialog->setVisible(false);

			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounding/Godbless.wav");
			update_money(Player, -1000);
			NotificationCenter::getInstance()->postNotification("one_go", String::createWithFormat("%d", 5));
			break;
		}
		case 3:
		{
			player* Player = players->at(0);
		    land->setTileGID(6+land_id, Vec2(buy_land_x, buy_land_y));
			image1 = Sprite::create("house2.png");
			image1->setPosition(Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).x + 16, Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).y + 16);
			image1->setVisible(true);
			map->addChild(image1);
			image1->setAnchorPoint(Vec2(0.5, 0.5));
			dialog->setVisible(false);

			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounding/Speaking_00458.wav");

			update_money(Player, -2000);
			NotificationCenter::getInstance()->postNotification("one_go", String::createWithFormat("%d", 5));
			break;
		}
		case 4:
		{
			player* Player = players->at(0);
			land->setTileGID(9+land_id, Vec2(buy_land_x, buy_land_y));
			image1 = Sprite::create("house3.png");
			image1->setPosition(Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).x + 16, Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).y + 16);
			image1->setVisible(true);
			map->addChild(image1);
			image1->setAnchorPoint(Vec2(0.5, 0.5));
			dialog->setVisible(false);

			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounding/Speaking_00458.wav");

			
			update_money(Player, -3000);
			NotificationCenter::getInstance()->postNotification("one_go", String::createWithFormat("%d", 5));
			break;
		}
		}
	}
	else
	{
		dialog->setVisible(false);
		NotificationCenter::getInstance()->postNotification("one_go", String::createWithFormat("%d", 5));
	}
}
//Display a dialog to ask whether to purchase estates
void GameScene::show_buy_land_dialog(int tag)
{
	String show = *String::create("");
	if (tag == 2)
	{
		show = "Purchase The Area? $1000 Needed!";
		dialog->setDataTag(2);
		dialog->getLabelContentText()->setString(show.getCString());
		dialog->setVisible(true);
	}
	else if (tag == 3)
	{
		show = "Upgrade Your Estate to Level 2? $ 2000 Needed";
		dialog->setDataTag(3);
		dialog->getLabelContentText()->setString(show.getCString());
		dialog->setVisible(true);
	}
	else if (tag == 4)
	{
		show = "Upgrade Your Estate to Level 3? $ 3000 Needed";
		dialog->setDataTag(4);
		dialog->getLabelContentText()->setString(show.getCString());
		dialog->setVisible(true);
	}
	else if (tag == 1000)
	{
		NotificationCenter::getInstance()->postNotification("one_go", String::createWithFormat("%d", 5));
	}
}



void GameScene::reg_notification_Observe()
{
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameScene::received_MSG), "buy_land", NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameScene::received_MSG), "pay_tolls", NULL);
}

void GameScene::received_MSG(Object* data)
{
	String* str = (String*)data;
	Vector<String*>message = Ui::splitString(str->getCString(), "-");
	int restype = message.at(0)->intValue();
	Sprite* image;
	if (restype == 2)
	{
		buy_land_x = message.at(1)->floatValue();
		buy_land_y = message.at(2)->floatValue();
		int tag = message.at(3)->intValue();
		if (tag == 1)
		{
			show_buy_land_dialog(restype);
		}
		else
		{
			player* Player = players->at(tag - 1);
			int money = 1000;
			Point p = Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map);
			Point q = Vec2(buy_land_x, buy_land_y);
			if (tag == 2)
			{
				land->setTileGID(1 + land_id, q);
				image = Sprite::create("house4.png");
			}
			else if (tag == 3)
			{
				land->setTileGID(2 + land_id, q);
				image = Sprite::create("house7.png");
			}
			else if (tag == 4)
			{
				land->setTileGID(10 + land_id, q);
				image = Sprite::create("house10.png");
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounding/p2_buyit.wav");

			image->setPosition(Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).x + 16, Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).y + 16);
			image->setVisible(true);
			map->addChild(image);
			image->setAnchorPoint(Vec2(0.5, 0.5));
			update_money(Player, -money);
			NotificationCenter::getInstance()->postNotification("one_go", String::createWithFormat("%d", 5));
		}
	}
	else if (restype == 3)
	{
		int money = 2000;
		buy_land_x = message.at(1)->floatValue();
		buy_land_y = message.at(2)->floatValue();
		int tag = message.at(3)->intValue();
		if (tag == 1)
		{
			show_buy_land_dialog(restype);
		}
		else
		{
			player* Player = players->at(tag - 1);
			Point p = Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map);
			Point q = Vec2(buy_land_x, buy_land_y);
			if (tag == 2)
			{
				land->setTileGID(4 + land_id, q);
				image = Sprite::create("house5.png");
			}
			else if (tag == 3)
			{
				land->setTileGID(5 + land_id, q);
				image = Sprite::create("house8.png");
			}
			else if (tag == 4)
			{
				land->setTileGID(11 + land_id, q);
				image = Sprite::create("house11.png");
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounding/p2_tiger.wav");
			image->setPosition(Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).x + 16, Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).y + 16);
			image->setVisible(true);
			map->addChild(image);
			image->setAnchorPoint(Vec2(0.5, 0.5));
			update_money(Player, -money);
			NotificationCenter::getInstance()->postNotification("one_go", String::createWithFormat("%d", 5));
		}
	}
	else if (restype == 4)
	{
		int money = 3000;
		buy_land_x = message.at(1)->floatValue();
		buy_land_y = message.at(2)->floatValue();
		int tag = message.at(3)->intValue();
		if (tag == 1)
		{
			show_buy_land_dialog(restype);
		}
		else
		{
			player* Player = players->at(tag - 1);
			Point p = Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map);
			Point q = Vec2(buy_land_x, buy_land_y);
			if (tag == 2)
			{
				land->setTileGID(7 + land_id, q);
				image = Sprite::create("house6.png");
			}
			else if (tag == 3)
			{
				land->setTileGID(8 + land_id, q);
				image = Sprite::create("house9.png");
			}
			else if (tag == 4)
			{
				land->setTileGID(12 + land_id, q);
				image = Sprite::create("house12.png");
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounding/p2_tiger.wav");

			image->setPosition(Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).x + 16, Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).y + 16);
			image->setVisible(true);
			map->addChild(image);
			image->setAnchorPoint(Vec2(0.5, 0.5));
			update_money(Player, -money);
			NotificationCenter::getInstance()->postNotification("one_go", String::createWithFormat("%d", 5));
		}
	}
	else if (restype == 1000)
	{
		int tag = message.at(3)->intValue();
		if (tag == 1)
		{
			show_buy_land_dialog(restype);
		}
		else
		{
			NotificationCenter::getInstance()->postNotification("one_go", String::createWithFormat("%d", 5));
		}
	}
	else if (restype == 6)
	{
		area_land.clear();
		int money = 500;
		buy_land_x = message.at(1)->floatValue();
		buy_land_y = message.at(2)->floatValue();
		int tag = message.at(3)->intValue();
		Point p = Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map);
		player* owner = get_land_owner(land->getTileGIDAt(Vec2(buy_land_x, buy_land_y)));
		int e_money = area_land_pay(buy_land_x, buy_land_y, players->at(tag - 1), owner->get_id().at(0), owner->get_id().at(1), owner->get_id().at(2));
		update_money(owner, e_money+money);
		update_money(players->at(tag - 1), -e_money-money);

		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounding/p2_buhuiba.wav");

		toast::addtoast(map, owner->getPosition(), String::createWithFormat("+%d",e_money+money)->getCString(),2);
		toast::addtoast(map, players->at(tag - 1)->getPosition(), String::createWithFormat("-%d", e_money + money)->getCString(),2);
		NotificationCenter::getInstance()->postNotification("one_go", String::createWithFormat("%d", 5));
	}
	else if (restype == 7)
	{
		int money = 1000;
		buy_land_x = message.at(1)->floatValue();
		buy_land_y = message.at(2)->floatValue();
		int tag = message.at(3)->intValue();
		Point p = Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map);
		player* owner = get_land_owner(land->getTileGIDAt(Vec2(buy_land_x, buy_land_y)));
		int e_money = area_land_pay(buy_land_x, buy_land_y, players->at(tag - 1), owner->get_id().at(0), owner->get_id().at(1), owner->get_id().at(2));
		update_money(owner, e_money+money);
		update_money(players->at(tag - 1), -e_money-money);

		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounding/p2_zhenmianmu.wav");

		toast::addtoast(map, owner->getPosition(), String::createWithFormat("+%d", e_money + money)->getCString(), 2);
		toast::addtoast(map, players->at(tag - 1)->getPosition(), String::createWithFormat("-%d", e_money + money)->getCString(), 2);
		NotificationCenter::getInstance()->postNotification("one_go", String::createWithFormat("%d", 5));
	}
	else if (restype ==8)
	{
		int money = 2000;
		buy_land_x = message.at(1)->floatValue();
		buy_land_y = message.at(2)->floatValue();
		int tag = message.at(3)->intValue();
		Point p = Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map);
		player* owner = get_land_owner(land->getTileGIDAt(Vec2(buy_land_x, buy_land_y)));
		int e_money = area_land_pay(buy_land_x, buy_land_y, players->at(tag - 1), owner->get_id().at(0), owner->get_id().at(1), owner->get_id().at(2));
		update_money(owner, e_money+money);
		update_money(players->at(tag - 1), -e_money-money);

		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounding/p2_qiangqiana.wav");

		toast::addtoast(map, owner->getPosition(), String::createWithFormat("+%d", e_money + money)->getCString(), 2);
		toast::addtoast(map, players->at(tag - 1)->getPosition(), String::createWithFormat("-%d", e_money + money)->getCString(), 2);
		NotificationCenter::getInstance()->postNotification("one_go", String::createWithFormat("%d", 5));
	}
}
//Update the character's money 
void GameScene::update_money(player* Player, int money)
{
	char a[20] = { 0 };
	sprintf(a, "%c %d", '$', (int)Player->getmoney() + money);
	Player->getmoney_string()->setString(a);
	Player->setmoney(Player->getmoney() + (float)money);
}


player* GameScene::get_land_owner(int Id)
{
	if (Id == 3+land_id || Id == 6+land_id || Id == 9+land_id)
	{
		return players->at(0);
	}
	else if (Id == 1+land_id || Id == 4+land_id || Id == 7+land_id)
	{
		return players->at(1);
	}
	else if (Id == 2 + land_id || Id == 5 + land_id || Id == 8 + land_id)
	{
		return players->at(2);
	}
	else if (Id == 10 + land_id || Id == 11 + land_id || Id == 12 + land_id)
	{
		return players->at(3);
	}
	return NULL;
}



int GameScene::area_land_pay(float x, float y, player* Player, int id1, int id2, int id3)
{
	area_land.clear();
	int money = 0;
	Point p = Player->getPosition();
	float nowx = Ui::chang_GL_to_map(p, map).x;
	float nowy = Ui::chang_GL_to_map(p, map).y;
	if (nowx == x)
	{
		float left = x - 1;
		float right = x + 1;
		int leftid = land->getTileGIDAt(Vec2(left, y));
		int rightid = land->getTileGIDAt(Vec2(right, y));
		area_land.pushBack(land->getTileAt(Vec2(x, y)));
		while (leftid != 0 && (leftid == id1+land_id || leftid == id2+land_id || leftid == id3+land_id))
		{
			if (leftid == id1+land_id)
				money += 500;
			if (leftid == id2+land_id)
				money += 1000;
			if (leftid == id3+land_id)
				money += 2000;
			area_land.pushBack(land->getTileAt(Vec2(left, y)));
			left -= 1;
			leftid = land->getTileGIDAt(Vec2(left, y));
			if (leftid == 0)
				break;
		}
		while (rightid != 0 && (rightid == id1+land_id || rightid == id2+land_id || rightid == id3+land_id))
		{
			if (rightid == id1+land_id)
				money += 500;
			if (rightid == id2+land_id)
				money += 1000;
			if (rightid == id3+land_id)
				money += 2000;
			area_land.pushBack(land->getTileAt(Vec2(right, y)));
			right += 1;
			rightid = land->getTileGIDAt(Vec2(right, y));
			if (rightid == 0)
				break;
		}		
	}
	if (nowy == y)
	{
		float up = y - 1;
		float down = y + 1;
		int upid = land->getTileGIDAt(Vec2(x, up));
		int downid = land->getTileGIDAt(Vec2(x, down));
		area_land.pushBack(land->getTileAt(Vec2(x, y)));
		while (upid != 0 && (upid == id1+land_id || upid == id2+land_id || upid == id3+land_id))
		{
			if (upid == id1+land_id)
				money += 500;
			if (upid == id2+land_id)
				money += 1000;
			if (upid == id3+land_id)
				money += 2000;
			area_land.pushBack(land->getTileAt(Vec2(x, up)));
			up -= 1;
			upid = land->getTileGIDAt(Vec2(x, up));
			if (upid == 0)
				break;
		}
		while (downid != 0 && (downid == id1+land_id || downid == id2+land_id || downid == id3+land_id))
		{
			if (downid == id1+land_id)
				money += 500;
			if (downid == id2+land_id)
				money += 1000;
			if (downid == id3+land_id)
				money += 2000;
			area_land.pushBack(land->getTileAt(Vec2(x, down)));
			down += 1;
			downid = land->getTileGIDAt(Vec2(x, down));
			if (downid == 0)
				break;
		}
	}
	for (auto it = area_land.begin(); it != area_land.end(); it++)
	{
		(*it)->runAction(Sequence::create(FadeOut::create(0.5)->clone(), FadeIn::create(0.5)->clone(), NULL));
	}
	return money;
}





