#include "GameSceneScene.h"
#include "toast.h"
#include "FinalScene.h"
#include <string>
#include <Opportunity.h>
#include <SimpleAudioEngine.h>
#include "VirtualPlayer.h"
#include "Factory.h"

USING_NS_CC;


//统一处理父类和子类，利用多态机制，Vector中存放父类指针
Vector<VirtualPlayer*>* GameScene::players = new Vector<VirtualPlayer*>();

//全局变量 global
Vector<Sprite*>* GameScene::playerimg = new Vector<Sprite*>();
Vector<Sprite*>* GameScene::step_image = new Vector<Sprite*>();
Vector<Sprite*> GameScene::area_land;
Vector<Sprite*> * GameScene::location_image = new Vector<Sprite*>();
int GameScene::playernumber = MAX_PLAYER_NUMBER;
int GameScene::map_type = MAP_TAG_1;
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

	auto background = Sprite::create(LOAD_PAGE);
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
	auto back=Sprite::create(QUIT_BUTTON);
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
	progressbgSprite = Sprite::create(SLIDER);
	progressbgSprite->setPosition(Size/2);
	addChild(progressbgSprite);
	auto progressSprite1 = Sprite::create(SLIDER);
	progress1 = ProgressTimer::create(progressSprite1);
	progress1->setType(kCCProgressTimerTypeBar);
	progress1->setPosition(Size/2);
	progress1->setMidpoint(Vec2(0, 0));
	progress1->setBarChangeRate(Vec2(1, 0));
	progress1->setPercentage(0);
	addChild(progress1);
	numsTTF = Label::createWithTTF(START_NUMBER, SETTING_FONT, 18);
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
	if (type == MAP_TAG_1)
	{
		map = TMXTiledMap::create(MAP_1);
		auto background = Sprite::create(GAME_BACKGROUND);
		background->setAnchorPoint(Vec2(0.5, 0.5));
		background->setPosition(visibleSize / 2);
		background->setScale(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
		addChild(background);
	}
	else if (type == MAP_TAG_2)
	{
		map = TMXTiledMap::create(MAP_2);
		auto background = Sprite::create(GAME_BACKGROUND);
		background->setAnchorPoint(Vec2(0.5, 0.5));
		background->setPosition(visibleSize / 2);
		background->setScale(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
		addChild(background);
	}
	else if (type == MAP_TAG_3)
	{
		map = TMXTiledMap::create(MAP_3);
		auto background = Sprite::create(GAME_BACKGROUND);
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
	land = map->layerNamed(LAND_BLOCK_NAME);
	rowcount = map->getContentSize().height/tileheigh;
	colcount = map->getContentSize().width/tilewidth;
	wenhao = map->layerNamed(OPPORTUNITY);
	if (type == MAP_TAG_1)
	{
		land_id = MAP_1_LAND_ID;
		wenhao_id = MAP_1_OPPORTUNITY_ID;
	}
	else if (type == MAP_TAG_2)
	{
		wenhao_id = MAP_2_OPPORTUNITY_ID;
		land_id = MAP_2_LAND_ID;
	}
	else if (type == MAP_TAG_3)
	{
		wenhao_id = MAP_3_OPPORTUNITY_ID;
		land_id = MAP_3_LAND_ID;
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
	//四种不同的角色通过工厂的方法进行创建
	PlayerA* player1 = FactoryA::CreatePlayer();
	PlayerB* player2 = FactoryB::CreatePlayer();
	PlayerC* player3 = FactoryC::CreatePlayer();
	PlayerD* player4 = FactoryD::CreatePlayer();
	playerimg->pushBack(player1);
	playerimg->pushBack(player2);
	playerimg->pushBack(player3);
	playerimg->pushBack(player4);
}
//没改
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
	float money = INIT_MONEY;
	auto framecache = SpriteFrameCache::getInstance();
	framecache->addSpriteFramesWithFile(PLAYER1_ANIM_PLIST, PLAYER1_ANIM_PNG);
	auto s1 = framecache->getSpriteFrameByName(PLAYER1_ANIM_PNG_1);
	player1 = PlayerA::createwith(PLAYER1_NAME, PLAYER1_TAG, s1, money);
	player1->settilesize(tilewidth, tileheigh);
	player1->setAnchorPoint(Point(0, 0.5));
	Point q = point[0];
	q.y = tileheigh + q.y;
	map->addChild(player1);
	player1->setPosition(q);
	player1->setturnme(true);
	player1->set_id(PLAYER1_LEVEL1_LAND_ID, PLAYER1_LEVEL2_LAND_ID, PLAYER1_LEVEL3_LAND_ID);
	framecache->addSpriteFramesWithFile(PLAYER2_ANIM_PLIST, PLAYER2_ANIM_PNG);
	auto s2 = framecache->getSpriteFrameByName(PLAYER2_ANIM_PNG_1);
	auto player2 = PlayerB::createwith(PLAYER2_NAME, PLAYER2_TAG, s2, money);
	player2->settilesize(tilewidth, tileheigh);
	Point q1 = point[39];
	q1.y = tileheigh + q1.y;
	map->addChild(player2);
	player2->setPosition(q1);
	player2->setAnchorPoint(Point(0, 0.5));
	player2->setturnme(true);
	player2->set_id(PLAYER2_LEVEL1_LAND_ID, PLAYER2_LEVEL2_LAND_ID, PLAYER2_LEVEL3_LAND_ID);
	framecache->addSpriteFramesWithFile(PLAYER3_ANIM_PLIST, PLAYER3_ANIM_PNG);
	auto s3 = framecache->getSpriteFrameByName(PLAYER3_ANIM_PNG_1);
	auto player3 = PlayerC::createwith(PLAYER3_NAME, PLAYER3_TAG, s3, money);
	player3->settilesize(tilewidth, tileheigh);
	Point q2 = point[10];
	q2.y = tileheigh + q2.y;
	map->addChild(player3);
	player3->setPosition(q2);
	player3->setAnchorPoint(Point(0, 0.5));
	player3->setturnme(true);
	player3->set_id(PLAYER3_LEVEL1_LAND_ID, PLAYER3_LEVEL2_LAND_ID, PLAYER3_LEVEL3_LAND_ID);
	framecache->addSpriteFramesWithFile(PLAYER4_ANIM_PLIST, PLAYER4_ANIM_PNG);
	auto s4 = framecache->getSpriteFrameByName(PLAYER4_ANIM_PNG_1);
	auto player4 = PlayerD::createwith(PLAYER4_NAME, PLAYER4_TAG, s4, money);
	player4->settilesize(tilewidth, tileheigh);
	Point q3 = point[29];
	q3.y = tileheigh + q3.y;
	map->addChild(player4);
	player4->setPosition(q3);
	player4->setAnchorPoint(Point(0, 0.5));
	player4->setturnme(true);
	player4->set_id(PLAYER4_LEVEL1_LAND_ID, PLAYER4_LEVEL2_LAND_ID, PLAYER4_LEVEL3_LAND_ID);
	players->clear();
	if (number == MAX_PLAYER_NUMBER - 1)
	{
		players->pushBack(player1);
		players->pushBack(player2);
		players->pushBack(player3);
		players->pushBack(player4);
	}
	else if (number == MAX_PLAYER_NUMBER - 2)
	{
		players->pushBack(player1);
		players->pushBack(player2);
		players->pushBack(player3);
		player4->setVisible(false);
	}
	else if (number == MAX_PLAYER_NUMBER - 3)
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
	auto way = map->layerNamed(WAY_BLOCK_NAME);
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
	go = Sprite::create(START_BUTTON);
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
			NotificationCenter::getInstance()->postNotification(MSG_GO, String::createWithFormat("%d", MSG_GO_HIDE_TAG));
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
	Vec2 size = map->layerNamed(WAY_BLOCK_NAME)->getLayerSize();
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

    char*picName = new char[20];
    memset(picName, 0, 20);
	//sprintf来减少重复代码
	for(int i=1;i<=6;i++){
        sprintf(picName, "Marker%02d.png", i);
		auto image1 = Sprite::create(picName);
		step_image->pushBack(image1);
		image1->setVisible(false);
		map->addChild(image1);
    	memset(picName, 0, 20);

	}

}

void GameScene::adddialog()
{
	dialog = PopupLayer::create(DIALOG_BACKGROUND);
	dialog->setContentSize(Size(400, 220));
	dialog->setTitle(BUY_LAND_DIALOG_TITLE);
	dialog->setContentText("", 20, 60, 250);
	dialog->setCallbackFunc(this, callfuncN_selector(GameScene::buyland));
	dialog->addButton(BUTTON_BACKGROUND_1, BUTTON_BACKGROUND_3, OK, 1);
	dialog->addButton(BUTTON_BACKGROUND_2, BUTTON_BACKGROUND_3, CANCEL, 0);
	addChild(dialog);
	dialog->setVisible(false);
}

void GameScene::adddialoglottery()
{
	dialoglottery = PopupLayer::create(DIALOG_BACKGROUND);
	dialoglottery->settype(1);
	dialoglottery->setContentSize(Size(400,220));
	dialoglottery->setTitle(LOTTERY_DIALOG_TITLE);
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
		case MSG_BUY_BLANK_TAG:
		{
			player* Player = players->at(0);
			land->setTileGID(PLAYER1_LEVEL1_LAND_ID + land_id, Vec2(buy_land_x, buy_land_y));
			image1 = Sprite::create(PLAYER1_LEVEL1_HOUSE);
			image1->setPosition(Ui::chang_map_to_GL( Vec2(buy_land_x, buy_land_y),map).x+16,Ui::chang_map_to_GL(Vec2(buy_land_x,buy_land_y),map).y+16);
			image1->setVisible(true);
			map->addChild(image1);
			image1->setAnchorPoint(Vec2(0.5, 0.5));
			dialog->setVisible(false);

			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GOD_BLESS_MUSIC);
			update_money(Player, -LAND_BLANK_MONEY);
			NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
			break;
		}
		case MSG_BUY_LAND_1_TAG:
		{
			player* Player = players->at(0);
			land->setTileGID(PLAYER1_LEVEL2_LAND_ID + land_id, Vec2(buy_land_x, buy_land_y));
			image1 = Sprite::create(PLAYER1_LEVEL2_HOUSE);
			image1->setPosition(Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).x + 16, Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).y + 16);
			image1->setVisible(true);
			map->addChild(image1);
			image1->setAnchorPoint(Vec2(0.5, 0.5));
			dialog->setVisible(false);

			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(RANDOM_MUSCI);

			update_money(Player, -LAND_LEVEL_1_MONEY);
			NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
			break;
		}
		case MSG_BUY_LAND_2_TAG:
		{
			player* Player = players->at(0);
			land->setTileGID(PLAYER1_LEVEL3_LAND_ID + land_id, Vec2(buy_land_x, buy_land_y));
			image1 = Sprite::create(PLAYER1_LEVEL3_HOUSE);
			image1->setPosition(Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).x + 16, Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).y + 16);
			image1->setVisible(true);
			map->addChild(image1);
			image1->setAnchorPoint(Vec2(0.5, 0.5));
			dialog->setVisible(false);

			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(RANDOM_MUSCI);

			
			update_money(Player, -LAND_LEVEL_2_MONEY);
			NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
			break;
		}
		}
	}
	else
	{
		dialog->setVisible(false);
		NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
	}
}
//Display a dialog to ask whether to purchase estates
void GameScene::show_buy_land_dialog(int tag)
{
	String show = *String::create("");
	if (tag == MSG_BUY_BLANK_TAG)
	{
		show = "Purchase The Area? $1000 Needed!";
		dialog->setDataTag(MSG_BUY_BLANK_TAG);
		dialog->getLabelContentText()->setString(show.getCString());
		dialog->setVisible(true);
	}
	else if (tag == MSG_BUY_LAND_1_TAG)
	{
		show = "Upgrade Your Estate to Level 2? $ 2000 Needed";
		dialog->setDataTag(MSG_BUY_LAND_1_TAG);
		dialog->getLabelContentText()->setString(show.getCString());
		dialog->setVisible(true);
	}
	else if (tag == MSG_BUY_LAND_2_TAG)
	{
		show = "Upgrade Your Estate to Level 3? $ 3000 Needed";
		dialog->setDataTag(MSG_BUY_LAND_2_TAG);
		dialog->getLabelContentText()->setString(show.getCString());
		dialog->setVisible(true);
	}
	else if (tag == MSG_CON_GO)
	{
		NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
	}
}



void GameScene::reg_notification_Observe()
{
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameScene::received_MSG), MSG_GO, NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameScene::received_MSG), MSG_PAY_TOLLS, NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameBaseScene::received_MSG), MSG_BUY, NULL);
}

void GameScene::received_MSG(Object* data)
{
	String* str = (String*)data;
	Vector<String*>message = Ui::splitString(str->getCString(), "-");
	int restype = message.at(0)->intValue();
	Sprite* image;
	switch (restype)
	{
	case MSG_BUY_BLANK_TAG:
		buy_land_x = message.at(1)->floatValue();
		buy_land_y = message.at(2)->floatValue();
		int tag = message.at(3)->intValue();
		if (tag == PLAYER1_TAG)
		{
			show_buy_land_dialog(restype);
		}
		else
		{
			player* Player = players->at(tag - 1);
			int money = LAND_BLANK_MONEY;
			Point p = Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map);
			Point q = Vec2(buy_land_x, buy_land_y);
			if (tag == PLAYER2_TAG)
			{
				land->setTileGID(PLAYER2_LEVEL1_LAND_ID + land_id, q);
				image = Sprite::create(PLAYER2_LEVEL1_HOUSE);
			}
			else if (tag == PLAYER3_TAG)
			{
				land->setTileGID(PLAYER3_LEVEL1_LAND_ID + land_id, q);
				image = Sprite::create(PLAYER3_LEVEL1_HOUSE);
			}
			else if (tag == PLAYER4_TAG)
			{
				land->setTileGID(PLAYER4_LEVEL1_LAND_ID + land_id, q);
				image = Sprite::create(PLAYER4_LEVEL1_HOUSE);
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(BUY_MUSIC);

			image->setPosition(Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).x + 16, Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).y + 16);
			image->setVisible(true);
			map->addChild(image);
			image->setAnchorPoint(Vec2(0.5, 0.5));
			update_money(Player, -money);
			NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
		}
		break;
	}
	case MSG_BUY_LAND_1_TAG:
		int money = LAND_LEVEL_1_MONEY;
		buy_land_x = message.at(1)->floatValue();
		buy_land_y = message.at(2)->floatValue();
		int tag = message.at(3)->intValue();
		if (tag == PLAYER1_TAG)
		{
			show_buy_land_dialog(restype);
		}
		else
		{
			player* Player = players->at(tag - 1);
			Point p = Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map);
			Point q = Vec2(buy_land_x, buy_land_y);
			if (tag == PLAYER2_TAG)
			{
				land->setTileGID(PLAYER2_LEVEL2_LAND_ID + land_id, q);
				image = Sprite::create(PLAYER2_LEVEL2_HOUSE);
			}
			else if (tag == PLAYER3_TAG)
			{
				land->setTileGID(PLAYER3_LEVEL2_LAND_ID + land_id, q);
				image = Sprite::create(PLAYER3_LEVEL2_HOUSE);
			}
			else if (tag == PLAYER4_TAG)
			{
				land->setTileGID(PLAYER4_LEVEL2_LAND_ID + land_id, q);
				image = Sprite::create(PLAYER4_LEVEL2_HOUSE);
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(TIGER_MUSIC);
			image->setPosition(Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).x + 16, Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).y + 16);
			image->setVisible(true);
			map->addChild(image);
			image->setAnchorPoint(Vec2(0.5, 0.5));
			update_money(Player, -money);
			NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
		}
		break;
	case MSG_BUY_LAND_2_TAG:
		int money = LAND_LEVEL_2_MONEY;
		buy_land_x = message.at(1)->floatValue();
		buy_land_y = message.at(2)->floatValue();
		int tag = message.at(3)->intValue();
		if (tag == PLAYER1_TAG)
		{
			show_buy_land_dialog(restype);
		}
		else
		{
			player* Player = players->at(tag - 1);
			Point p = Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map);
			Point q = Vec2(buy_land_x, buy_land_y);
			if (tag == PLAYER2_TAG)
			{
				land->setTileGID(PLAYER2_LEVEL3_LAND_ID + land_id, q);
				image = Sprite::create(PLAYER2_LEVEL3_HOUSE);
			}
			else if (tag == PLAYER3_TAG)
			{
				land->setTileGID(PLAYER3_LEVEL3_LAND_ID + land_id, q);
				image = Sprite::create(PLAYER3_LEVEL3_HOUSE);
			}
			else if (tag == PLAYER4_TAG)
			{
				land->setTileGID(PLAYER4_LEVEL3_LAND_ID + land_id, q);
				image = Sprite::create(PLAYER4_LEVEL3_HOUSE);
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(TIGER_MUSIC);

			image->setPosition(Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).x + 16, Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).y + 16);
			image->setVisible(true);
			map->addChild(image);
			image->setAnchorPoint(Vec2(0.5, 0.5));
			update_money(Player, -money);
			NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
		};
		break;
	case MSG_CON_GO:
		int tag = message.at(3)->intValue();
		if (tag == 1)
		{
			show_buy_land_dialog(restype);
		}
		else
		{
			NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
		}
		break;
	case MSG_PAY_TOLLS_1_TAG:
		area_land.clear();
		int money = PAY_TOLLS_MONEY_1;
		buy_land_x = message.at(1)->floatValue();
		buy_land_y = message.at(2)->floatValue();
		int tag = message.at(3)->intValue();
		Point p = Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map);
		player* owner = get_land_owner(land->getTileGIDAt(Vec2(buy_land_x, buy_land_y)));
		int e_money = area_land_pay(buy_land_x, buy_land_y, players->at(tag - 1), owner->get_id().at(0), owner->get_id().at(1), owner->get_id().at(2));
		update_money(owner, e_money + money);
		update_money(players->at(tag - 1), -e_money - money);

		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(UNBELIEVE_MUSIC);

		toast::addtoast(map, owner->getPosition(), String::createWithFormat("+%d", e_money + money)->getCString(), 2);
		toast::addtoast(map, players->at(tag - 1)->getPosition(), String::createWithFormat("-%d", e_money + money)->getCString(), 2);
		NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
		break;
	case MSG_PAY_TOLLS_2_TAG:
		int money = PAY_TOLLS_MONEY_2;
		buy_land_x = message.at(1)->floatValue();
		buy_land_y = message.at(2)->floatValue();
		int tag = message.at(3)->intValue();
		Point p = Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map);
		player* owner = get_land_owner(land->getTileGIDAt(Vec2(buy_land_x, buy_land_y)));
		int e_money = area_land_pay(buy_land_x, buy_land_y, players->at(tag - 1), owner->get_id().at(0), owner->get_id().at(1), owner->get_id().at(2));
		update_money(owner, e_money + money);
		update_money(players->at(tag - 1), -e_money - money);

		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(UNHEPPY_MUSIC4);

		toast::addtoast(map, owner->getPosition(), String::createWithFormat("+%d", e_money + money)->getCString(), 2);
		toast::addtoast(map, players->at(tag - 1)->getPosition(), String::createWithFormat("-%d", e_money + money)->getCString(), 2);
		NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
		break;
	case MSG_PAY_TOLLS_3_TAG:
		int money = PAY_TOLLS_MONEY_3;
		buy_land_x = message.at(1)->floatValue();
		buy_land_y = message.at(2)->floatValue();
		int tag = message.at(3)->intValue();
		Point p = Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map);
		player* owner = get_land_owner(land->getTileGIDAt(Vec2(buy_land_x, buy_land_y)));
		int e_money = area_land_pay(buy_land_x, buy_land_y, players->at(tag - 1), owner->get_id().at(0), owner->get_id().at(1), owner->get_id().at(2));
		update_money(owner, e_money + money);
		update_money(players->at(tag - 1), -e_money - money);

		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(UNHEPPY_MUSIC3);

		toast::addtoast(map, owner->getPosition(), String::createWithFormat("+%d", e_money + money)->getCString(), 2);
		toast::addtoast(map, players->at(tag - 1)->getPosition(), String::createWithFormat("-%d", e_money + money)->getCString(), 2);
		NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
		break;
	
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
	if (Id == PLAYER1_LEVEL1_LAND_ID + land_id || Id == PLAYER1_LEVEL2_LAND_ID + land_id || Id == PLAYER1_LEVEL3_LAND_ID + land_id)
	{
		return players->at(0);
	}
	else if (Id == PLAYER2_LEVEL1_LAND_ID + land_id || Id == PLAYER2_LEVEL2_LAND_ID + land_id || Id == PLAYER2_LEVEL3_LAND_ID + land_id)
	{
		return players->at(1);
	}
	else if (Id == PLAYER3_LEVEL1_LAND_ID + land_id || Id == PLAYER3_LEVEL2_LAND_ID + land_id || Id == PLAYER3_LEVEL3_LAND_ID + land_id)
	{
		return players->at(2);
	}
	else if (Id == PLAYER4_LEVEL1_LAND_ID + land_id || Id == PLAYER4_LEVEL2_LAND_ID + land_id || Id == PLAYER4_LEVEL3_LAND_ID + land_id)
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
				money += PAY_TOLLS_MONEY_1;
			if (leftid == id2+land_id)
				money += PAY_TOLLS_MONEY_2;
			if (leftid == id3+land_id)
				money += PAY_TOLLS_MONEY_3;
			area_land.pushBack(land->getTileAt(Vec2(left, y)));
			left -= 1;
			leftid = land->getTileGIDAt(Vec2(left, y));
			if (leftid == 0)
				break;
		}
		while (rightid != 0 && (rightid == id1+land_id || rightid == id2+land_id || rightid == id3+land_id))
		{
			if (rightid == id1+land_id)
				money += PAY_TOLLS_MONEY_1;
			if (rightid == id2+land_id)
				money += PAY_TOLLS_MONEY_2;
			if (rightid == id3+land_id)
				money += PAY_TOLLS_MONEY_3;
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
				money += PAY_TOLLS_MONEY_1;
			if (upid == id2+land_id)
				money += PAY_TOLLS_MONEY_2;
			if (upid == id3+land_id)
				money += PAY_TOLLS_MONEY_3;
			area_land.pushBack(land->getTileAt(Vec2(x, up)));
			up -= 1;
			upid = land->getTileGIDAt(Vec2(x, up));
			if (upid == 0)
				break;
		}
		while (downid != 0 && (downid == id1+land_id || downid == id2+land_id || downid == id3+land_id))
		{
			if (downid == id1+land_id)
				money += PAY_TOLLS_MONEY_1;
			if (downid == id2+land_id)
				money += PAY_TOLLS_MONEY_2;
			if (downid == id3+land_id)
				money += PAY_TOLLS_MONEY_3;
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