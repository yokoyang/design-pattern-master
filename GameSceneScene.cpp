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
Vector<Sprite*>* GameScene::playerImg = new Vector<Sprite*>();
Vector<Sprite*>* GameScene::step_image = new Vector<Sprite*>();
Vector<Sprite*> GameScene::area_land;
Vector<Sprite*> * GameScene::location_image = new Vector<Sprite*>();
int GameScene::playerNumber = MAX_PLAYER_NUMBER;
int GameScene::map_type = MAP_TAG_1;
bool** GameScene::isWalk = NULL;
TMXLayer* GameScene::land = NULL;
TMXLayer* GameScene::quesMark = NULL;
TMXTiledMap* GameScene::map = NULL;
PopupLayer* GameScene::dialog = NULL;
PopupLayer* GameScene::dialogLottery = NULL;
float GameScene::buy_land_x = 0;
float GameScene::buy_land_y = 0;
Layer* GameScene::final_layer = NULL;
int GameScene::rowCount = 0;
int GameScene::quesMark_id = 0;
int GameScene::colCount = 0;
int GameScene::land_id = 0;
Sprite* GameScene::Go = NULL;



Scene* GameScene::CreateScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::Create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::Create();

    // add layer as a child to scene
    scene->AddChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::Init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::Init() )
    {
        return false;
    }
    
    visibleSize = Director::GetInstance()->GetVisibleSize();
    Vec2 origin = Director::GetInstance()->GetVisibleOrigin();

	auto background = Sprite::Create(LOAD_PAGE);
	background->SetPosition(visibleSize / 2);
	background->SetAnchorPoint(Vec2(0.5, 0.5));
	background->SetScale(1.5);
	AddChild(background);
	AddProgressTimer();
	ScheduleOnce(schedule_selector(GameScene::AddInfor), 1.60f);

    return true;
}

//Add all sorts of game resources
void GameScene::AddInfor(float t)
{
	auto Size = Director::GetInstance()->GetVisibleSize();
	auto layer = Layer::Create();
	AddMap(map_type);
	AddPlayerImg();
	AddPlayerInformation(playerNumber);
	SetIsWalk();
	GetWayGild();
	AddStepImage();
	AddPlayer(playerNumber);
	AddDice(layer);
	reg_notification_Observe();
	AddChild(layer);
	AddDialog();
	AddDialogLottery();
	AddFinalLayer();
	Opportunity::Load();
	AddLocationImage();
	auto back=Sprite::Create(QUIT_BUTTON);
	back->SetPosition(150, 50);
	back->SetScale(0.5);
	AddChild(back);
	auto listener = EventListenerTouchOneByOne::Create();
	listener->onTouchBegan = [back](Touch* t, Event* e){
		if (back->getBoundingBox().containsPoint(t->getLocation()))
		{
			Director::GetInstance()->end();
		}
		return false;
	};
	Director::GetInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, back);
}

//Add progress timer
void GameScene::AddProgressTimer()
{
	auto Size = Director::GetInstance()->GetVisibleSize();
	progressBgSprite = Sprite::Create(SLIDER);
	progressBgSprite->SetPosition(Size/2);
	AddChild(progressBgSprite);
	auto progressSprite1 = Sprite::Create(SLIDER);
	progress1 = ProgressTimer::Create(progressSprite1);
	progress1->setType(kCCProgressTimerTypeBar);
	progress1->SetPosition(Size/2);
	progress1->setMidpoint(Vec2(0, 0));
	progress1->setBarChangeRate(Vec2(1, 0));
	progress1->setPercentage(0);
	AddChild(progress1);
	numsTTF = Label::CreateWithTTF(START_NUMBER, SETTING_FONT, 18);
	numsTTF->SetPosition(Vec2(300, 300));
	AddChild(numsTTF, 1);
	scheduleUpdate();
}
//Update the progress timer
void GameScene::Update(float t)
{
	float cu = progress1->GetPercentage();
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
		numsTTF->SetVisible(false);
		progress1->SetVisible(false);
		progressBgSprite->SetVisible(false);
	}
}

void GameScene::AddFinalLayer()
{
	final_layer = FinalScene::Create();
	AddChild(final_layer);
	final_layer->SetPosition(visibleSize / 2);
	final_layer->SetVisible(false);
}

void GameScene::AddMap(int type)
{
	if (type == MAP_TAG_1)
	{
		map = TMXTiledMap::Create(MAP_1);
		auto background = Sprite::Create(GAME_BACKGROUND);
		background->SetAnchorPoint(Vec2(0.5, 0.5));
		background->SetPosition(visibleSize / 2);
		background->SetScale(visibleSize.width / background->GetContentSize().width, visibleSize.height / background->GetContentSize().height);
		AddChild(background);
	}
	else if (type == MAP_TAG_2)
	{
		map = TMXTiledMap::Create(MAP_2);
		auto background = Sprite::Create(GAME_BACKGROUND);
		background->SetAnchorPoint(Vec2(0.5, 0.5));
		background->SetPosition(visibleSize / 2);
		background->SetScale(visibleSize.width / background->GetContentSize().width, visibleSize.height / background->GetContentSize().height);
		AddChild(background);
	}
	else if (type == MAP_TAG_3)
	{
		map = TMXTiledMap::Create(MAP_3);
		auto background = Sprite::Create(GAME_BACKGROUND);
		background->SetAnchorPoint(Vec2(0.5, 0.5));
		background->SetPosition(visibleSize / 2);
		background->SetScale(visibleSize.width / background->GetContentSize().width, visibleSize.height / background->GetContentSize().height);
		AddChild(background);
	}
	AddChild(map);
	map->SetAnchorPoint(Point(0.5, 0.5));
	map->SetPosition(visibleSize.width / 2 - 100, visibleSize.height / 2);
	Size tile = map->getTileSize();
	tileWidth = tile.width;
	tileHeigh = tile.height;
	land = map->layerNamed(LAND_BLOCK_NAME);
	rowCount = map->GetContentSize().height/tileHeigh;
	colCount = map->GetContentSize().width/tileWidth;
	quesMark = map->layerNamed(OPPORTUNITY);
	if (type == MAP_TAG_1)
	{
		land_id = MAP_1_LAND_ID;
		quesMark_id = MAP_1_OPPORTUNITY_ID;
	}
	else if (type == MAP_TAG_2)
	{
		quesMark_id = MAP_2_OPPORTUNITY_ID;
		land_id = MAP_2_LAND_ID;
	}
	else if (type == MAP_TAG_3)
	{
		quesMark_id = MAP_3_OPPORTUNITY_ID;
		land_id = MAP_3_LAND_ID;
	}
}



//add a new player
void GameScene::AddPlayerInformation(int number)
{
	auto it = playerImg->begin();
	for (int i = 0; i < number; i++, it++)
	{
		auto player = Sprite::Create();
		player = *it;
		AddChild(player);
		player->SetAnchorPoint(Point(0.5,0.5));
		player->SetPosition(Vec2(visibleSize.width / 24 * 19, visibleSize.height / number / 2 + (number - 1 - i) * visibleSize.height / number));
	}
}


void GameScene::AddPlayerImg()
{
	playerImg->clear();
	//四种不同的角色通过工厂的方法进行创建
	PlayerA* player1 = FactoryA::CreatePlayer();
	PlayerB* player2 = FactoryB::CreatePlayer();
	PlayerC* player3 = FactoryC::CreatePlayer();
	PlayerD* player4 = FactoryD::CreatePlayer();
	playerImg->PushBack(player1);
	playerImg->PushBack(player2);
	playerImg->PushBack(player3);
	playerImg->PushBack(player4);
}
//没改
void GameScene::AddLocationImage()
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
        auto temp = Sprite::Create(picName);
        location_image->PushBack(temp);
        AddChild(temp);
        temp->SetVisible(false);
        temp->SetAnchorPoint(Vec2(0.5, 0.5));
        temp->SetPosition(visibleSize / 2);
    }
}

void GameScene::AddPlayer(int number)
{
	playerNumber = number;
	float money = INIT_MONEY;
	auto framecache = SpriteFrameCache::GetInstance();
	framecache->addSpriteFramesWithFile(PLAYER1_ANIM_PLIST, PLAYER1_ANIM_PNG);
	auto s1 = framecache->getSpriteFrameByName(PLAYER1_ANIM_PNG_1);
	player1 = PlayerA::CreateWith(PLAYER1_NAME, PLAYER1_TAG, s1, money);
	player1->SetTileSize(tileWidth, tileHeigh);
	player1->SetAnchorPoint(Point(0, 0.5));
	Point q = point[0];
	q.y = tileHeigh + q.y;
	map->AddChild(player1);
	player1->SetPosition(q);
	player1->setturnme(true);
	player1->set_id(PLAYER1_LEVEL1_LAND_ID, PLAYER1_LEVEL2_LAND_ID, PLAYER1_LEVEL3_LAND_ID);
	framecache->addSpriteFramesWithFile(PLAYER2_ANIM_PLIST, PLAYER2_ANIM_PNG);
	auto s2 = framecache->getSpriteFrameByName(PLAYER2_ANIM_PNG_1);
	auto player2 = PlayerB::CreateWith(PLAYER2_NAME, PLAYER2_TAG, s2, money);
	player2->SetTileSize(tileWidth, tileHeigh);
	Point q1 = point[39];
	q1.y = tileHeigh + q1.y;
	map->AddChild(player2);
	player2->SetPosition(q1);
	player2->SetAnchorPoint(Point(0, 0.5));
	player2->setturnme(true);
	player2->set_id(PLAYER2_LEVEL1_LAND_ID, PLAYER2_LEVEL2_LAND_ID, PLAYER2_LEVEL3_LAND_ID);
	framecache->addSpriteFramesWithFile(PLAYER3_ANIM_PLIST, PLAYER3_ANIM_PNG);
	auto s3 = framecache->getSpriteFrameByName(PLAYER3_ANIM_PNG_1);
	auto player3 = PlayerC::CreateWith(PLAYER3_NAME, PLAYER3_TAG, s3, money);
	player3->SetTileSize(tileWidth, tileHeigh);
	Point q2 = point[10];
	q2.y = tileHeigh + q2.y;
	map->AddChild(player3);
	player3->SetPosition(q2);
	player3->SetAnchorPoint(Point(0, 0.5));
	player3->setturnme(true);
	player3->set_id(PLAYER3_LEVEL1_LAND_ID, PLAYER3_LEVEL2_LAND_ID, PLAYER3_LEVEL3_LAND_ID);
	framecache->addSpriteFramesWithFile(PLAYER4_ANIM_PLIST, PLAYER4_ANIM_PNG);
	auto s4 = framecache->getSpriteFrameByName(PLAYER4_ANIM_PNG_1);
	auto player4 = PlayerD::CreateWith(PLAYER4_NAME, PLAYER4_TAG, s4, money);
	player4->SetTileSize(tileWidth, tileHeigh);
	Point q3 = point[29];
	q3.y = tileHeigh + q3.y;
	map->AddChild(player4);
	player4->SetPosition(q3);
	player4->SetAnchorPoint(Point(0, 0.5));
	player4->setturnme(true);
	player4->set_id(PLAYER4_LEVEL1_LAND_ID, PLAYER4_LEVEL2_LAND_ID, PLAYER4_LEVEL3_LAND_ID);
	players->clear();
	if (number == MAX_PLAYER_NUMBER - 1)
	{
		players->PushBack(player1);
		players->PushBack(player2);
		players->PushBack(player3);
		players->PushBack(player4);
	}
	else if (number == MAX_PLAYER_NUMBER - 2)
	{
		players->PushBack(player1);
		players->PushBack(player2);
		players->PushBack(player3);
		player4->SetVisible(false);
	}
	else if (number == MAX_PLAYER_NUMBER - 3)
	{
		players->PushBack(player1);
		players->PushBack(player2);
		player3->SetVisible(false);
		player4->SetVisible(false);
	}
	auto it = players->begin();
	int j = 0;
	for (; it != players->end(); it++)
	{
		j++;
		char a[20] = { 0 };
		sprintf(a, "%c%d", '$', (int)(*it)->GetMoney());
		(*it)->getmoney_string()->setString(a);
		(*it)->get_name()->SetColor(Color3B::BLACK);
		(*it)->get_name()->SetScale(1.5);
		(*it)->getmoney_string()->SetPosition(visibleSize.width / 12 * 11, (number - j + 1) * visibleSize.height / number - visibleSize.height / number / 2 - 30);
		(*it)->get_name()->SetPosition(visibleSize.width / 12 * 11, (number - j + 1) * visibleSize.height / number - visibleSize.height / number / 2 + 40);
		(*it)->getmoney_string()->SetColor(Color3B::BLACK);
		(*it)->getmoney_string()->SetScale(1.5);
		AddChild((*it)->getmoney_string());
		AddChild((*it)->get_name());
	}
}


//Get the coordinate in the map where the character can move to
void GameScene::GetWayGild()
{
	point.clear();
	auto way = map->layerNamed(WAY_BLOCK_NAME);
	Size waysize = way->GetLayerSize();
	for (int i = 0; i < waysize.width; i++)
	{
		for (int j = 1; j < waysize.height; j++)
		{
			auto p = way->tileAt(Point(i, j));
			if (p)
			{
				Vec2 P = p->GetPosition();
				point.push_back(P);
				float x = p->GetPositionX();
				float y = p->GetPositionY();
				isWalk[(int)(y/tileHeigh)][(int)(x/tileWidth)] = true;
			}
		}
	}
}

void GameScene::AddDice(Layer* layer)
{
	srand(clock());
	int i = 0;
	Go = Sprite::Create(START_BUTTON);
	Go->SetScale(0.5);
	layer->AddChild(Go);
	Go->SetAnchorPoint(Point(0,1));
	Go->SetPosition(Vec2(280, 80));
	auto touch = EventListenerTouchOneByOne::Create();
	bool** isWalkCopy = isWalk;
	auto Go = Go;
	touch->onTouchBegan = [i,isWalkCopy,Go,this](Touch* t, Event* e){
		if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation()))
		{
			Go->SetVisible(false);
			Go->SetPosition(Go->GetPosition() - Vec2(0, 500));
			auto it = players->begin();
			int stepNumber = rand() % 6;
			Route::GetInstance()->GetPath(*it,isWalkCopy, stepNumber + 1, colCount, rowCount);
			NotificationCenter::GetInstance()->postNotification(MSG_GO, String::createWithFormat("%d", MSG_GO_HIDE_TAG));
			(*it)->Go(Route::GetInstance()->GetPathRow(), Route::GetInstance()->GetPathCol());
		}
		return false;
	};
	Director::GetInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touch, Go);
}


void GameScene::SetIsWalk()
{
	int tileRow;
	int tileCol;
	Vec2 size = map->layerNamed(WAY_BLOCK_NAME)->GetLayerSize();
	tileCol = (int)size.x;
	tileRow = (int)size.y;
	isWalk = new bool*[tileRow];
	for (int i = 0; i < tileRow; i++)
	{
		isWalk[i] = new bool[tileCol];
	}
	for (int i = 0; i < tileRow; i++)
	{
		for (int j = 0; j < tileCol; j++)
		{
			isWalk[i][j] = false;
		}
	}
}


bool** GameScene::GetIsWalk()
{
	return isWalk;
}


void GameScene::AddStepImage()
{
	step_image->clear();

    char*picName = new char[20];
    memset(picName, 0, 20);
	//sprintf来减少重复代码
	for(int i=1;i<=6;i++){
        sprintf(picName, "Marker%02d.png", i);
		auto image1 = Sprite::Create(picName);
		step_image->PushBack(image1);
		image1->SetVisible(false);
		map->AddChild(image1);
    	memset(picName, 0, 20);

	}

}

void GameScene::AddDialog()
{
	dialog = PopupLayer::Create(DIALOG_BACKGROUND);
	dialog->setContentSize(Size(400, 220));
	dialog->setTitle(BUY_LAND_DIALOG_TITLE);
	dialog->setContentText("", 20, 60, 250);
	dialog->SetCallbackFunc(this, callfuncN_selector(GameScene::BuyLand));
	dialog->AddButton(BUTTON_BACKGROUND_1, BUTTON_BACKGROUND_3, OK, 1);
	dialog->AddButton(BUTTON_BACKGROUND_2, BUTTON_BACKGROUND_3, CANCEL, 0);
	AddChild(dialog);
	dialog->SetVisible(false);
}

void GameScene::AddDialogLottery()
{
	dialogLottery = PopupLayer::Create(DIALOG_BACKGROUND);
	dialogLottery->settype(1);
	dialogLottery->setContentSize(Size(400,220));
	dialogLottery->setTitle(LOTTERY_DIALOG_TITLE);
	dialogLottery->setContentText("", 20, 60, 250);
	dialogLottery->SetPlayerVector(*players);
	dialogLottery->SetTag(100);
	this->AddChild(dialogLottery);
	dialogLottery->SetVisible(false);

}

void GameScene::BuyLand(Node* node)
{
	if (node->getTag() == 1)
	{
		Sprite* image1;
		switch (dialog->getDataTag())
		{
		case MSG_BUY_BLANK_TAG:
		{
			Player* player = players->at(0);
			land->setTileGID(PLAYER1_LEVEL1_LAND_ID + land_id, Vec2(buy_land_x, buy_land_y));
			image1 = Sprite::Create(PLAYER1_LEVEL1_HOUSE);
			image1->SetPosition(Ui::chang_map_to_GL( Vec2(buy_land_x, buy_land_y),map).x+16,Ui::chang_map_to_GL(Vec2(buy_land_x,buy_land_y),map).y+16);
			image1->SetVisible(true);
			map->AddChild(image1);
			image1->SetAnchorPoint(Vec2(0.5, 0.5));
			dialog->SetVisible(false);

			CocosDenshion::SimpleAudioEngine::GetInstance()->playEffect(GOD_BLESS_MUSIC);
			UpdateMoney(Player, -LAND_BLANK_MONEY);
			NotificationCenter::GetInstance()->postNotification(MSG_PICKONE_TOGO, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
			break;
		}
		case MSG_BUY_LAND_1_TAG:
		{
			Player* player = players->at(0);
			land->setTileGID(PLAYER1_LEVEL2_LAND_ID + land_id, Vec2(buy_land_x, buy_land_y));
			image1 = Sprite::Create(PLAYER1_LEVEL2_HOUSE);
			image1->SetPosition(Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).x + 16, Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).y + 16);
			image1->SetVisible(true);
			map->AddChild(image1);
			image1->SetAnchorPoint(Vec2(0.5, 0.5));
			dialog->SetVisible(false);

			CocosDenshion::SimpleAudioEngine::GetInstance()->playEffect(RANDOM_MUSCI);

			UpdateMoney(Player, -LAND_LEVEL_1_MONEY);
			NotificationCenter::GetInstance()->postNotification(MSG_PICKONE_TOGO, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
			break;
		}
		case MSG_BUY_LAND_2_TAG:
		{
			Player* player = players->at(0);
			land->setTileGID(PLAYER1_LEVEL3_LAND_ID + land_id, Vec2(buy_land_x, buy_land_y));
			image1 = Sprite::Create(PLAYER1_LEVEL3_HOUSE);
			image1->SetPosition(Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).x + 16, Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).y + 16);
			image1->SetVisible(true);
			map->AddChild(image1);
			image1->SetAnchorPoint(Vec2(0.5, 0.5));
			dialog->SetVisible(false);

			CocosDenshion::SimpleAudioEngine::GetInstance()->playEffect(RANDOM_MUSCI);

			
			UpdateMoney(Player, -LAND_LEVEL_2_MONEY);
			NotificationCenter::GetInstance()->postNotification(MSG_PICKONE_TOGO, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
			break;
		}
		}
	}
	else
	{
		dialog->SetVisible(false);
		NotificationCenter::GetInstance()->postNotification(MSG_PICKONE_TOGO, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
	}
}
//Display a dialog to ask whether to purchase estates
void GameScene::show_buy_land_dialog(int tag)
{
	String show = *String::Create("");
	if (tag == MSG_BUY_BLANK_TAG)
	{
		show = "Purchase The Area? $1000 Needed!";
		dialog->setDataTag(MSG_BUY_BLANK_TAG);
		dialog->GetLabelContentText()->setString(show.getCString());
		dialog->SetVisible(true);
	}
	else if (tag == MSG_BUY_LAND_1_TAG)
	{
		show = "Upgrade Your Estate to Level 2? $ 2000 Needed";
		dialog->setDataTag(MSG_BUY_LAND_1_TAG);
		dialog->GetLabelContentText()->setString(show.getCString());
		dialog->SetVisible(true);
	}
	else if (tag == MSG_BUY_LAND_2_TAG)
	{
		show = "Upgrade Your Estate to Level 3? $ 3000 Needed";
		dialog->setDataTag(MSG_BUY_LAND_2_TAG);
		dialog->GetLabelContentText()->setString(show.getCString());
		dialog->SetVisible(true);
	}
	else if (tag == MSG_CON_GO)
	{
		NotificationCenter::GetInstance()->postNotification(MSG_PICKONE_TOGO, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
	}
}



void GameScene::reg_notification_Observe()
{
	NotificationCenter::GetInstance()->addObserver(this, callfuncO_selector(GameScene::ReceivedMsg), MSG_GO, NULL);
	NotificationCenter::GetInstance()->addObserver(this, callfuncO_selector(GameScene::ReceivedMsg), MSG_PAY_TOLLS, NULL);
	NotificationCenter::GetInstance()->addObserver(this, callfuncO_selector(GameBaseScene::ReceivedMsg), MSG_BUY, NULL);
}

void GameScene::ReceivedMsg(Object* data)
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
			Player* player = players->at(tag - 1);
			int money = LAND_BLANK_MONEY;
			Point p = Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map);
			Point q = Vec2(buy_land_x, buy_land_y);
			if (tag == PLAYER2_TAG)
			{
				land->setTileGID(PLAYER2_LEVEL1_LAND_ID + land_id, q);
				image = Sprite::Create(PLAYER2_LEVEL1_HOUSE);
			}
			else if (tag == PLAYER3_TAG)
			{
				land->setTileGID(PLAYER3_LEVEL1_LAND_ID + land_id, q);
				image = Sprite::Create(PLAYER3_LEVEL1_HOUSE);
			}
			else if (tag == PLAYER4_TAG)
			{
				land->setTileGID(PLAYER4_LEVEL1_LAND_ID + land_id, q);
				image = Sprite::Create(PLAYER4_LEVEL1_HOUSE);
			}
			CocosDenshion::SimpleAudioEngine::GetInstance()->playEffect(BUY_MUSIC);

			image->SetPosition(Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).x + 16, Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).y + 16);
			image->SetVisible(true);
			map->AddChild(image);
			image->SetAnchorPoint(Vec2(0.5, 0.5));
			UpdateMoney(Player, -money);
			NotificationCenter::GetInstance()->postNotification(MSG_PICKONE_TOGO, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
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
			Player* player = players->at(tag - 1);
			Point p = Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map);
			Point q = Vec2(buy_land_x, buy_land_y);
			if (tag == PLAYER2_TAG)
			{
				land->setTileGID(PLAYER2_LEVEL2_LAND_ID + land_id, q);
				image = Sprite::Create(PLAYER2_LEVEL2_HOUSE);
			}
			else if (tag == PLAYER3_TAG)
			{
				land->setTileGID(PLAYER3_LEVEL2_LAND_ID + land_id, q);
				image = Sprite::Create(PLAYER3_LEVEL2_HOUSE);
			}
			else if (tag == PLAYER4_TAG)
			{
				land->setTileGID(PLAYER4_LEVEL2_LAND_ID + land_id, q);
				image = Sprite::Create(PLAYER4_LEVEL2_HOUSE);
			}
			CocosDenshion::SimpleAudioEngine::GetInstance()->playEffect(TIGER_MUSIC);
			image->SetPosition(Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).x + 16, Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).y + 16);
			image->SetVisible(true);
			map->AddChild(image);
			image->SetAnchorPoint(Vec2(0.5, 0.5));
			UpdateMoney(Player, -money);
			NotificationCenter::GetInstance()->postNotification(MSG_PICKONE_TOGO, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
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
			Player* player = players->at(tag - 1);
			Point p = Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map);
			Point q = Vec2(buy_land_x, buy_land_y);
			if (tag == PLAYER2_TAG)
			{
				land->setTileGID(PLAYER2_LEVEL3_LAND_ID + land_id, q);
				image = Sprite::Create(PLAYER2_LEVEL3_HOUSE);
			}
			else if (tag == PLAYER3_TAG)
			{
				land->setTileGID(PLAYER3_LEVEL3_LAND_ID + land_id, q);
				image = Sprite::Create(PLAYER3_LEVEL3_HOUSE);
			}
			else if (tag == PLAYER4_TAG)
			{
				land->setTileGID(PLAYER4_LEVEL3_LAND_ID + land_id, q);
				image = Sprite::Create(PLAYER4_LEVEL3_HOUSE);
			}
			CocosDenshion::SimpleAudioEngine::GetInstance()->playEffect(TIGER_MUSIC);

			image->SetPosition(Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).x + 16, Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).y + 16);
			image->SetVisible(true);
			map->AddChild(image);
			image->SetAnchorPoint(Vec2(0.5, 0.5));
			UpdateMoney(Player, -money);
			NotificationCenter::GetInstance()->postNotification(MSG_PICKONE_TOGO, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
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
			NotificationCenter::GetInstance()->postNotification(MSG_PICKONE_TOGO, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
		}
		break;
	case MSG_PAY_TOLLS_1_TAG:
		area_land.clear();
		int money = PAY_TOLLS_MONEY_1;
		buy_land_x = message.at(1)->floatValue();
		buy_land_y = message.at(2)->floatValue();
		int tag = message.at(3)->intValue();
		Point p = Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map);
		Player* owner = get_land_owner(land->GetTileGIDAt(Vec2(buy_land_x, buy_land_y)));
		int e_money = AreaLandPay(buy_land_x, buy_land_y, players->at(tag - 1), owner->get_id().at(0), owner->get_id().at(1), owner->get_id().at(2));
		UpdateMoney(owner, e_money + money);
		UpdateMoney(players->at(tag - 1), -e_money - money);

		CocosDenshion::SimpleAudioEngine::GetInstance()->playEffect(UNBELIEVE_MUSIC);

		toast::addtoast(map, owner->GetPosition(), String::createWithFormat("+%d", e_money + money)->getCString(), 2);
		toast::addtoast(map, players->at(tag - 1)->GetPosition(), String::createWithFormat("-%d", e_money + money)->getCString(), 2);
		NotificationCenter::GetInstance()->postNotification(MSG_PICKONE_TOGO, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
		break;
	case MSG_PAY_TOLLS_2_TAG:
		int money = PAY_TOLLS_MONEY_2;
		buy_land_x = message.at(1)->floatValue();
		buy_land_y = message.at(2)->floatValue();
		int tag = message.at(3)->intValue();
		Point p = Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map);
		Player* owner = get_land_owner(land->GetTileGIDAt(Vec2(buy_land_x, buy_land_y)));
		int e_money = AreaLandPay(buy_land_x, buy_land_y, players->at(tag - 1), owner->get_id().at(0), owner->get_id().at(1), owner->get_id().at(2));
		UpdateMoney(owner, e_money + money);
		UpdateMoney(players->at(tag - 1), -e_money - money);

		CocosDenshion::SimpleAudioEngine::GetInstance()->playEffect(UNHEPPY_MUSIC4);

		toast::addtoast(map, owner->GetPosition(), String::createWithFormat("+%d", e_money + money)->getCString(), 2);
		toast::addtoast(map, players->at(tag - 1)->GetPosition(), String::createWithFormat("-%d", e_money + money)->getCString(), 2);
		NotificationCenter::GetInstance()->postNotification(MSG_PICKONE_TOGO, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
		break;
	case MSG_PAY_TOLLS_3_TAG:
		int money = PAY_TOLLS_MONEY_3;
		buy_land_x = message.at(1)->floatValue();
		buy_land_y = message.at(2)->floatValue();
		int tag = message.at(3)->intValue();
		Point p = Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map);
		Player* owner = get_land_owner(land->GetTileGIDAt(Vec2(buy_land_x, buy_land_y)));
		int e_money = AreaLandPay(buy_land_x, buy_land_y, players->at(tag - 1), owner->get_id().at(0), owner->get_id().at(1), owner->get_id().at(2));
		UpdateMoney(owner, e_money + money);
		UpdateMoney(players->at(tag - 1), -e_money - money);

		CocosDenshion::SimpleAudioEngine::GetInstance()->preloadEffect(UNHEPPY_MUSIC3);

		toast::addtoast(map, owner->GetPosition(), String::createWithFormat("+%d", e_money + money)->getCString(), 2);
		toast::addtoast(map, players->at(tag - 1)->GetPosition(), String::createWithFormat("-%d", e_money + money)->getCString(), 2);
		NotificationCenter::GetInstance()->postNotification(MSG_PICKONE_TOGO, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
		break;
	
}
//Update the character's money 
void GameScene::UpdateMoney(Player* player, int money)
{
	char a[20] = { 0 };
	sprintf(a, "%c %d", '$', (int)Player->GetMoney() + money);
	Player->getmoney_string()->setString(a);
	Player->setmoney(Player->GetMoney() + (float)money);
}


Player* GameScene::get_land_owner(int Id)
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



int GameScene::AreaLandPay(float x, float y, Player* player, int id1, int id2, int id3)
{
	area_land.clear();
	int money = 0;
	Point p = Player->GetPosition();
	float nowx = Ui::chang_GL_to_map(p, map).x;
	float nowy = Ui::chang_GL_to_map(p, map).y;
	if (nowx == x)
	{
		float left = x - 1;
		float right = x + 1;
		int leftid = land->GetTileGIDAt(Vec2(left, y));
		int rightid = land->GetTileGIDAt(Vec2(right, y));
		area_land.PushBack(land->getTileAt(Vec2(x, y)));
		while (leftid != 0 && (leftid == id1+land_id || leftid == id2+land_id || leftid == id3+land_id))
		{
			if (leftid == id1+land_id)
				money += PAY_TOLLS_MONEY_1;
			if (leftid == id2+land_id)
				money += PAY_TOLLS_MONEY_2;
			if (leftid == id3+land_id)
				money += PAY_TOLLS_MONEY_3;
			area_land.PushBack(land->getTileAt(Vec2(left, y)));
			left -= 1;
			leftid = land->GetTileGIDAt(Vec2(left, y));
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
			area_land.PushBack(land->getTileAt(Vec2(right, y)));
			right += 1;
			rightid = land->GetTileGIDAt(Vec2(right, y));
			if (rightid == 0)
				break;
		}		
	}
	if (nowy == y)
	{
		float up = y - 1;
		float down = y + 1;
		int upid = land->GetTileGIDAt(Vec2(x, up));
		int downid = land->GetTileGIDAt(Vec2(x, down));
		area_land.PushBack(land->getTileAt(Vec2(x, y)));
		while (upid != 0 && (upid == id1+land_id || upid == id2+land_id || upid == id3+land_id))
		{
			if (upid == id1+land_id)
				money += PAY_TOLLS_MONEY_1;
			if (upid == id2+land_id)
				money += PAY_TOLLS_MONEY_2;
			if (upid == id3+land_id)
				money += PAY_TOLLS_MONEY_3;
			area_land.PushBack(land->getTileAt(Vec2(x, up)));
			up -= 1;
			upid = land->GetTileGIDAt(Vec2(x, up));
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
			area_land.PushBack(land->getTileAt(Vec2(x, down)));
			down += 1;
			downid = land->GetTileGIDAt(Vec2(x, down));
			if (downid == 0)
				break;
		}
	}
	for (auto it = area_land.begin(); it != area_land.end(); it++)
	{
		(*it)->RunAction(Sequence::Create(FadeOut::Create(0.5)->clone(), FadeIn::Create(0.5)->clone(), NULL));
	}
	return money;
}