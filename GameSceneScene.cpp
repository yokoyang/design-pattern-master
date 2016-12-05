#include "GameSceneScene.h"
#include"Toast.h"
#include"FinalScene.h"
#include<string>
#include<Opportunity.h>
#include<SimpleAudioEngine.h>

USING_NS_CC;

//全局变量 global
Vector<Sprite*>* GameScene::playerImg = new Vector<Sprite*>();
Vector<Player*>* GameScene::players = new Vector<Player*>();
Vector<Sprite*>* GameScene::step_image = new Vector<Sprite*>();
Vector<Sprite*> GameScene::area_land;
Vector<Sprite*> * GameScene::location_image = new Vector<Sprite*>();
int GameScene::playerNumber = 4;
int GameScene::map_type = 1;
bool** GameScene::isWalk = NULL;
TMXLayer* GameScene::land = NULL;
TMXLayer* GameScene::wenhao = NULL;
TMXTiledMap* GameScene::map = NULL;
PopupLayer* GameScene::dialog = NULL;
PopupLayer* GameScene::dialogLottery = NULL;
float GameScene::buy_land_x = 0;
float GameScene::buy_land_y = 0;
Layer* GameScene::final_layer = NULL;
int GameScene::rowCount = 0;
int GameScene::quesmark_id = 0;
int GameScene::colCount = 0;
int GameScene::land_id = 0;
Sprite* GameScene::go = NULL;



Scene* GameScene::CreateScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::Create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::Create();

    // Add layer as a child to scene
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
    
    visibleSize = Director::GetInstance()->GetvisibleSize();
    Vec2 origin = Director::GetInstance()->GetVisibleOrigin();

	auto background = Sprite::Create("world.jpg");
	background->setPosition(visibleSize / 2);
	background->setAnchorPoint(Vec2(0.5, 0.5));
	background->SetScale(1.5);
	AddChild(background);
	AddProgressTimer();
	ScheduleOnce(schedule_selector(GameScene::Add_infor), 1.60f);

    return true;
}

//Add all sorts of game resources
void GameScene::Add_infor(float t)
{
	auto Size = Director::GetInstance()->GetvisibleSize();
	auto layer = Layer::Create();
	AddMap(map_type);
	AddPlayerImg();
	AddPlayerInformation(playerNumber);
	SetIsWalk();
	GetWayGild();
	AddStep_image();
	AddPlayer(playerNumber);
	AddShaiZi(layer);
	reg_notification_Observe();
	AddChild(layer);
	AddDialog();
	AddDialogLottery();
	AddFinal_layer();
	Opportunity::Load();
	Add_location_image();
	auto back=Sprite::Create("Quit Button.png");
	back->setPosition(150, 50);
	back->SetScale(0.5);
	AddChild(back);
	auto listener = EventListenerTouchOneByOne::Create();
	listener->OnTouchBegan = [back](Touch* t, Event* e){
		if (back->GetBoundingBox().ContainsPoint(t->GetLocation()))
		{
			Director::GetInstance()->End();
		}
		return false;
	};
	Director::GetInstance()->GetEventDispatcher()->AddEventListenerWithSceneGraphPriority(listener, back);
}

//Add progress timer
void GameScene::AddProgressTimer()
{
	auto Size = Director::GetInstance()->GetvisibleSize();
	progressBgSprite = Sprite::Create("slider.png");
	progressBgSprite->setPosition(Size/2);
	AddChild(progressBgSprite);
	auto progressSprite1 = Sprite::Create("slider.png");
	progress1 = ProgressTimer::Create(progressSprite1);
	progress1->SetType(kCCProgressTimerTypeBar);
	progress1->setPosition(Size/2);
	progress1->SetMidpoint(Vec2(0, 0));
	progress1->SetBarChangeRate(Vec2(1, 0));
	progress1->SetPercentage(0);
	AddChild(progress1);
	numsTTF = Label::CreateWithTTF("0", "fonts/Gazzarel.TTF", 18);
	numsTTF->setPosition(Vec2(300, 300));
	AddChild(numsTTF, 1);
	ScheduleUpdate();
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
	progress1->SetPercentage(cu);
	String *str = String::CreateWithFormat("%.0f%%", cu);
	numsTTF->SetString(str->GetCString());
	if (cu >= 100)
	{
		numsTTF->setVisible(false);
		progress1->setVisible(false);
		progressBgSprite->setVisible(false);
	}
}

void GameScene::AddFinal_layer()
{
	final_layer = FinalScene::Create();
	AddChild(final_layer);
	final_layer->setPosition(visibleSize / 2);
	final_layer->setVisible(false);
}

void GameScene::AddMap(int type)
{
	if (type == 1)
	{
		map = TMXTiledMap::Create("map1.tmx");
		auto background = Sprite::Create("Sea.jpg");
		background->setAnchorPoint(Vec2(0.5, 0.5));
		background->setPosition(visibleSize / 2);
		background->SetScale(visibleSize.width / background->GetContentSize().width, visibleSize.height / background->GetContentSize().height);
		AddChild(background);
	}
	else if (type == 2)
	{
		map = TMXTiledMap::Create("map2.tmx");
		auto background = Sprite::Create("Sea.jpg");
		background->setAnchorPoint(Vec2(0.5, 0.5));
		background->setPosition(visibleSize / 2);
		background->SetScale(visibleSize.width / background->GetContentSize().width, visibleSize.height / background->GetContentSize().height);
		AddChild(background);
	}
	else if (type == 3)
	{
		map = TMXTiledMap::Create("map3.tmx");
		auto background = Sprite::Create("Sea.jpg");
		background->setAnchorPoint(Vec2(0.5, 0.5));
		background->setPosition(visibleSize / 2); background->SetScale(visibleSize.width / background->GetContentSize().width, visibleSize.height / background->GetContentSize().height); e().height);
		AddChild(background);
	}
	AddChild(map);
	map->setAnchorPoint(Point(0.5, 0.5));
	map->setPosition(visibleSize.width / 2 - 100, visibleSize.height / 2);
	Size tile = map->GetTileSize();
	tilewidth = tile.width;
	tileheigh = tile.height;
	land = map->LayerNamed("land");
	rowCount = map->GetContentSize().height/tileheigh;
	colCount = map->GetContentSize().width/tilewidth;
	wenhao = map->LayerNamed("wenhao");
	if (type == 2 || type == 3)
	{
		quesmark_id = 469;
		land_id = 273;
	}
	else if (type == 1)
	{
		land_id = 870;
		quesmark_id = 1048;
	}
}


void GameScene::AddPlayerInformation(int number)
{
	auto it = playerImg->Begin();
	for (int i = 0; i < number; i++, it++)
	{
		auto player = Sprite::Create();
		player = *it;
		AddChild(player);
		player->setAnchorPoint(Point(0.5,0.5));
		player->setPosition(Vec2(visibleSize.width / 24 * 19, visibleSize.height / number / 2 + (number - 1 - i) * visibleSize.height / number));
	}
}


//去除冗余代码
void GameScene::AddPlayerImg()
{
	playerImg->Clear();
	for (int i = 1; i < 5; i++)
	{
		auto player = Sprite::Create("player%d.jpg",i);
		playerImg->PushBack(player);

	}
}
void GameScene::Add_location_image()
{
	if (!location_image->Empty())
	{
		return;
	}
	for (int i = 0; i < 39; i++)
	{
		auto temp = Sprite::Create("Location%02d.jpg", i);
		location_image->PushBack(temp);
		AddChild(temp);
		temp->setVisible(false);
		temp->setAnchorPoint(Vec2(0.5, 0.5));
		temp->setPosition(visibleSize / 2);
	}
}


void GameScene::AddPlayer(int number)
{
	playerNumber = number;
	float money = 10000;
	auto framecache = SpriteFrameCache::GetInstance();
	framecache->AddSpriteFramesWithFile("player1_anim.plist", "player1_anim.png");
	auto s1 = framecache->GetSpriteFrameByName("player1_anim_01.png");
	player1 = Player::Createwith("player1", 1, s1, money);
	player1->SettileSize(tilewidth, tileheigh);
	player1->setAnchorPoint(Point(0, 0.5));
	Point q = point[0];
	q.y = tileheigh + q.y;
	map->AddChild(player1);
	player1->setPosition(q);
	player1->SetTurnMe(true);
	player1->Set_id(3, 6, 9);
	framecache->AddSpriteFramesWithFile("player2_anim.plist", "player2_anim.png");
	auto s2 = framecache->GetSpriteFrameByName("player2_anim_01.png");
	auto player2 = Player::Createwith("player2", 2, s2, money);
	player2->SettileSize(tilewidth, tileheigh);
	Point q1 = point[39];
	q1.y = tileheigh + q1.y;
	map->AddChild(player2);
	player2->setPosition(q1);
	player2->setAnchorPoint(Point(0, 0.5));
	player2->SetTurnMe(true);
	player2->Set_id(1, 4, 7);
	framecache->AddSpriteFramesWithFile("player3_anim.plist", "player3_anim.png");
	auto s3 = framecache->GetSpriteFrameByName("player3_anim_01.png");
	auto player3 = Player::Createwith("player3", 3, s3, money);
	player3->SettileSize(tilewidth, tileheigh);
	Point q2 = point[10];
	q2.y = tileheigh + q2.y;
	map->AddChild(player3);
	player3->setPosition(q2);
	player3->setAnchorPoint(Point(0, 0.5));
	player3->SetTurnMe(true);
	player3->Set_id(2, 5, 8);
	framecache->AddSpriteFramesWithFile("player4_anim.plist", "player4_anim.png");
	auto s4 = framecache->GetSpriteFrameByName("player4_anim_01.png");
	auto player4 = Player::Createwith("player4", 4, s4, money);
	player4->SettileSize(tilewidth, tileheigh);
	Point q3 = point[29];
	q3.y = tileheigh + q3.y;
	map->AddChild(player4);
	player4->setPosition(q3);
	player4->setAnchorPoint(Point(0, 0.5));
	player4->SetTurnMe(true);
	player4->Set_id(10, 11, 12);
	players->Clear();
	if (number == 4)
	{
		players->PushBack(player1);
		players->PushBack(player2);
		players->PushBack(player3);
		players->PushBack(player4);
	}
	else if (number == 3)
	{
		players->PushBack(player1);
		players->PushBack(player2);
		players->PushBack(player3);
		player4->setVisible(false);
	}
	else if (number == 2)
	{
		players->PushBack(player1);
		players->PushBack(player2);
		player3->setVisible(false);
		player4->setVisible(false);
	}
	auto it = players->Begin();
	int j = 0;
	for (; it != players->End(); it++)
	{
		j++;
		char a[20] = { 0 };
		sprintf(a, "%c%d", '$', (int)(*it)->GetMoney());
		(*it)->GetMoney_string()->SetString(a);
		(*it)->GetName()->SetColor(Color3B::BLACK);
		(*it)->GetName()->SetScale(1.5);
		(*it)->GetMoney_string()->setPosition(visibleSize.width / 12 * 11, (number - j + 1) * visibleSize.height / number - visibleSize.height / number / 2 - 30);
		(*it)->GetName()->setPosition(visibleSize.width / 12 * 11, (number - j + 1) * visibleSize.height / number - visibleSize.height / number / 2 + 40);
		(*it)->GetMoney_string()->SetColor(Color3B::BLACK);
		(*it)->GetMoney_string()->SetScale(1.5);
		AddChild((*it)->GetMoney_string());
		AddChild((*it)->GetName());
	}
}


//Get the coordinate in the map where the character can move to
void GameScene::GetWayGild()
{
	point.Clear();
	auto way = map->LayerNamed("way");
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
				isWalk[(int)(y/tileheigh)][(int)(x/tilewidth)] = true;
			}
		}
	}
}

void GameScene::AddShaiZi(Layer* layer)
{
	srand(clock());
	int i = 0;
	go = Sprite::Create("Start Button.png");
	go->SetScale(0.5);
	layer->AddChild(go);
	go->setAnchorPoint(Point(0,1));
	go->setPosition(Vec2(280, 80));
	auto touch = EventListenerTouchOneByOne::Create();
	bool** isWalkCopy = isWalk;
	auto Go = go;
	touch->onTouchBegan = [i,isWalkCopy,Go,this](Touch* t, Event* e){
		if (e->GetCurrentTarGet()->GetBoundingBox().ContainsPoint(t->GetLocation()))
		{
			Go->setVisible(false);
			Go->setPosition(Go->GetPosition() - Vec2(0, 500));
			auto it = players->Begin();
			int stepNumber = rand() % 6;
			Route::GetInstance()->GetPath(*it,isWalkCopy, stepNumber + 1, colCount, rowCount);
			(*it)->go(Route::GetInstance()->GetPathRow(), Route::GetInstance()->GetPathCol());
		}
		return false;
	};
	Director::GetInstance()->GetEventDispatcher()->AddEventListenerWithSceneGraphPriority(touch, go);
}


void GameScene::SetIsWalk()
{
	int tileRow;
	int tileCol;
	Vec2 size = map->LayerNamed("way")->GetLayerSize();
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



void GameScene::AddStep_image()
{
	step_image->Clear();
	for (int i = 1; i < 7; i++)
	{
		auto image = Sprite::Create("Marker%d.png", i);
		step_image->PushBack(image);
		image->setVisible(false);
		map->AddChild(image);
	}

}

void GameScene::AddDialog()
{
	dialog = PopupLayer::Create("dialog_bg.png");
	dialog->SetContentSize(Size(400, 220));
	dialog->SetTitle("buy land");
	dialog->SetContentText("", 20, 60, 250);
	dialog->SetCallbackFunc(this, callfuncN_selector(GameScene::BuyLand));
	dialog->AddButton("button_bg1.png", "button_bg3.png", "OK", 1);
	dialog->AddButton("button_bg2.png", "button_bg3.png", "CANCEL", 0);
	AddChild(dialog);
	dialog->setVisible(false);
}

void GameScene::AddDialogLottery()
{
	dialogLottery = PopupLayer::Create("dialog_bg.png");
	dialogLottery->SetType(1);
	dialogLottery->SetContentSize(Size(400,220));
	dialogLottery->SetTitle("Lottery");
	dialogLottery->SetContentText("", 20, 60, 250);
	dialogLottery->SetPlayerVector(*players);
	dialogLottery->SetTag(100);
	this->AddChild(dialogLottery);
	dialogLottery->setVisible(false);

}

void GameScene::BuyLand(Node* node)
{
	if (node->GetTag() == 1)
	{
		Sprite* image1;
		switch (dialog->GetDataTag())
		{
		case 2:
		{
			Player* player = players->at(0);
			land->SetTileGID(3+land_id, Vec2(buy_land_x, buy_land_y));
			image1 = Sprite::Create("house1.png");
			image1->setPosition(Ui::chang_map_to_GL( Vec2(buy_land_x, buy_land_y),map).x+16,Ui::chang_map_to_GL(Vec2(buy_land_x,buy_land_y),map).y+16);
			image1->setVisible(true);
			map->AddChild(image1);
			image1->setAnchorPoint(Vec2(0.5, 0.5));
			dialog->setVisible(false);

			CocosDenshion::SimpleAudioEngine::GetInstance()->PlayEffect("Sounding/Godbless.wav");
			UpdateMoney(player, -1000);
			NotificationCenter::GetInstance()->PostNotification("one_go", String::CreateWithFormat("%d", 5));
			break;
		}
		case 3:
		{
			Player* player = players->at(0);
		    land->SetTileGID(6+land_id, Vec2(buy_land_x, buy_land_y));
			image1 = Sprite::Create("house2.png");
			image1->setPosition(Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).x + 16, Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).y + 16);
			image1->setVisible(true);
			map->AddChild(image1);
			image1->setAnchorPoint(Vec2(0.5, 0.5));
			dialog->setVisible(false);

			CocosDenshion::SimpleAudioEngine::GetInstance()->PlayEffect("Sounding/Speaking_00458.wav");

			UpdateMoney(player, -2000);
			NotificationCenter::GetInstance()->PostNotification("one_go", String::CreateWithFormat("%d", 5));
			break;
		}
		case 4:
		{
			Player* player = players->at(0);
			land->SetTileGID(9+land_id, Vec2(buy_land_x, buy_land_y));
			image1 = Sprite::Create("house3.png");
			image1->setPosition(Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).x + 16, Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).y + 16);
			image1->setVisible(true);
			map->AddChild(image1);
			image1->setAnchorPoint(Vec2(0.5, 0.5));
			dialog->setVisible(false);

			CocosDenshion::SimpleAudioEngine::GetInstance()->PlayEffect("Sounding/Speaking_00458.wav");

			
			UpdateMoney(player, -3000);
			NotificationCenter::GetInstance()->PostNotification("one_go", String::CreateWithFormat("%d", 5));
			break;
		}
		}
	}
	else
	{
		dialog->setVisible(false);
		NotificationCenter::GetInstance()->PostNotification("one_go", String::CreateWithFormat("%d", 5));
	}
}
//Display a dialog to ask whether to purchase estates
void GameScene::show_buy_land_dialog(int tag)
{
	String show = *String::Create("");
	if (tag == 2)
	{
		show = "Purchase The Area? $1000 Needed!";
		dialog->SetDataTag(2);
		dialog->GetLabelContentText()->SetString(show.GetCString());
		dialog->setVisible(true);
	}
	else if (tag == 3)
	{
		show = "Upgrade Your Estate to Level 2? $ 2000 Needed";
		dialog->SetDataTag(3);
		dialog->GetLabelContentText()->SetString(show.GetCString());
		dialog->setVisible(true);
	}
	else if (tag == 4)
	{
		show = "Upgrade Your Estate to Level 3? $ 3000 Needed";
		dialog->SetDataTag(4);
		dialog->GetLabelContentText()->SetString(show.GetCString());
		dialog->setVisible(true);
	}
	else if (tag == 1000)
	{
		NotificationCenter::GetInstance()->PostNotification("one_go", String::CreateWithFormat("%d", 5));
	}
}



void GameScene::reg_notification_Observe()
{
	NotificationCenter::GetInstance()->AddObserver(this, CallFuncO_selector(GameScene::Received_MSG), "buy_land", NULL);
	NotificationCenter::GetInstance()->AddObserver(this, CallFuncO_selector(GameScene::Received_MSG), "pay_tolls", NULL);
}

void GameScene::Received_MSG(Object* data)
{
	String* str = (String*)data;
	Vector<String*>message = Ui::SplitString(str->GetCString(), "-");
	int restype = message.at(0)->IntValue();
	Sprite* image;
	if (restype == 2)
	{
		buy_land_x = message.at(1)->FloatValue();
		buy_land_y = message.at(2)->FloatValue();
		int tag = message.at(3)->IntValue();
		if (tag == 1)
		{
			show_buy_land_dialog(restype);
		}
		else
		{
			Player* player = players->at(tag - 1);
			int money = 1000;
			Point p = Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map);
			Point q = Vec2(buy_land_x, buy_land_y);
			if (tag == 2)
			{
				land->SetTileGID(1 + land_id, q);
				image = Sprite::Create("house4.png");
			}
			else if (tag == 3)
			{
				land->SetTileGID(2 + land_id, q);
				image = Sprite::Create("house7.png");
			}
			else if (tag == 4)
			{
				land->SetTileGID(10 + land_id, q);
				image = Sprite::Create("house10.png");
			}
			CocosDenshion::SimpleAudioEngine::GetInstance()->PlayEffect("Sounding/p2_buyit.wav");

			image->setPosition(Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).x + 16, Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).y + 16);
			image->setVisible(true);
			map->AddChild(image);
			image->setAnchorPoint(Vec2(0.5, 0.5));
			UpdateMoney(player, -money);
			NotificationCenter::GetInstance()->PostNotification("one_go", String::CreateWithFormat("%d", 5));
		}
	}
	else if (restype == 3)
	{
		int money = 2000;
		buy_land_x = message.at(1)->FloatValue();
		buy_land_y = message.at(2)->FloatValue();
		int tag = message.at(3)->IntValue();
		if (tag == 1)
		{
			show_buy_land_dialog(restype);
		}
		else
		{
			Player* player = players->at(tag - 1);
			Point p = Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map);
			Point q = Vec2(buy_land_x, buy_land_y);
			if (tag == 2)
			{
				land->SetTileGID(4 + land_id, q);
				image = Sprite::Create("house5.png");
			}
			else if (tag == 3)
			{
				land->SetTileGID(5 + land_id, q);
				image = Sprite::Create("house8.png");
			}
			else if (tag == 4)
			{
				land->SetTileGID(11 + land_id, q);
				image = Sprite::Create("house11.png");
			}
			CocosDenshion::SimpleAudioEngine::GetInstance()->PlayEffect("Sounding/p2_tiger.wav");
			image->setPosition(Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).x + 16, Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).y + 16);
			image->setVisible(true);
			map->AddChild(image);
			image->setAnchorPoint(Vec2(0.5, 0.5));
			UpdateMoney(player, -money);
			NotificationCenter::GetInstance()->PostNotification("one_go", String::CreateWithFormat("%d", 5));
		}
	}
	else if (restype == 4)
	{
		int money = 3000;
		buy_land_x = message.at(1)->FloatValue();
		buy_land_y = message.at(2)->FloatValue();
		int tag = message.at(3)->IntValue();
		if (tag == 1)
		{
			show_buy_land_dialog(restype);
		}
		else
		{
			Player* player = players->at(tag - 1);
			Point p = Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map);
			Point q = Vec2(buy_land_x, buy_land_y);
			if (tag == 2)
			{
				land->SetTileGID(7 + land_id, q);
				image = Sprite::Create("house6.png");
			}
			else if (tag == 3)
			{
				land->SetTileGID(8 + land_id, q);
				image = Sprite::Create("house9.png");
			}
			else if (tag == 4)
			{
				land->SetTileGID(12 + land_id, q);
				image = Sprite::Create("house12.png");
			}
			CocosDenshion::SimpleAudioEngine::GetInstance()->PlayEffect("Sounding/p2_tiger.wav");

			image->setPosition(Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).x + 16, Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).y + 16);
			image->setVisible(true);
			map->AddChild(image);
			image->setAnchorPoint(Vec2(0.5, 0.5));
			UpdateMoney(player, -money);
			NotificationCenter::GetInstance()->PostNotification("one_go", String::CreateWithFormat("%d", 5));
		}
	}
	else if (restype == 1000)
	{
		int tag = message.at(3)->IntValue();
		if (tag == 1)
		{
			show_buy_land_dialog(restype);
		}
		else
		{
			NotificationCenter::GetInstance()->PostNotification("one_go", String::CreateWithFormat("%d", 5));
		}
	}
	else if (restype == 6)
	{
		area_land.Clear();
		int money = 500;
		buy_land_x = message.at(1)->FloatValue();
		buy_land_y = message.at(2)->FloatValue();
		int tag = message.at(3)->IntValue();
		Point p = Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map);
		Player* owner = get_land_owner(land->GetTileGIDAt(Vec2(buy_land_x, buy_land_y)));
		int e_money = area_land_pay(buy_land_x, buy_land_y, players->at(tag - 1), owner->Get_id().at(0), owner->Get_id().at(1), owner->Get_id().at(2));
		UpdateMoney(owner, e_money+money);
		UpdateMoney(players->at(tag - 1), -e_money-money);

		CocosDenshion::SimpleAudioEngine::GetInstance()->PlayEffect("Sounding/p2_buhuiba.wav");

		Toast::AddToast(map, owner->GetPosition(), String::CreateWithFormat("+%d",e_money+money)->GetCString(),2);
		Toast::AddToast(map, players->at(tag - 1)->GetPosition(), String::CreateWithFormat("-%d", e_money + money)->GetCString(),2);
		NotificationCenter::GetInstance()->PostNotification("one_go", String::CreateWithFormat("%d", 5));
	}
	else if (restype == 7)
	{
		int money = 1000;
		buy_land_x = message.at(1)->FloatValue();
		buy_land_y = message.at(2)->FloatValue();
		int tag = message.at(3)->IntValue();
		Point p = Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map);
		Player* owner = get_land_owner(land->GetTileGIDAt(Vec2(buy_land_x, buy_land_y)));
		int e_money = area_land_pay(buy_land_x, buy_land_y, players->at(tag - 1), owner->Get_id().at(0), owner->Get_id().at(1), owner->Get_id().at(2));
		UpdateMoney(owner, e_money+money);
		UpdateMoney(players->at(tag - 1), -e_money-money);

		CocosDenshion::SimpleAudioEngine::GetInstance()->PlayEffect("Sounding/p2_zhenmianmu.wav");

		Toast::AddToast(map, owner->GetPosition(), String::CreateWithFormat("+%d", e_money + money)->GetCString(), 2);
		Toast::AddToast(map, players->at(tag - 1)->GetPosition(), String::CreateWithFormat("-%d", e_money + money)->GetCString(), 2);
		NotificationCenter::GetInstance()->PostNotification("one_go", String::CreateWithFormat("%d", 5));
	}
	else if (restype ==8)
	{
		int money = 2000;
		buy_land_x = message.at(1)->FloatValue();
		buy_land_y = message.at(2)->FloatValue();
		int tag = message.at(3)->IntValue();
		Point p = Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map);
		Player* owner = get_land_owner(land->GetTileGIDAt(Vec2(buy_land_x, buy_land_y)));get_land_owner
		int e_money = area_land_pay(buy_land_x, buy_land_y, players->at(tag - 1), owner->Get_id().at(0), owner->Get_id().at(1), owner->Get_id().at(2));
		UpdateMoney(owner, e_money+money);
		UpdateMoney(players->at(tag - 1), -e_money-money);

		CocosDenshion::SimpleAudioEngine::GetInstance()->PreloadEffect("Sounding/p2_qiangqiana.wav");

		Toast::AddToast(map, owner->GetPosition(), String::CreateWithFormat("+%d", e_money + money)->GetCString(), 2);
		Toast::AddToast(map, players->at(tag - 1)->GetPosition(), String::CreateWithFormat("-%d", e_money + money)->GetCString(), 2);
		NotificationCenter::GetInstance()->PostNotification("one_go", String::CreateWithFormat("%d", 5));
	}
}
//Update the character's money 
void GameScene::UpdateMoney(Player* player, int money)
{
	char a[20] = { 0 };
	sprintf(a, "%c %d", '$', (int)player->GetMoney() + money);
	player->GetMoney_string()->SetString(a);
	player->SetMoney(player->GetMoney() + (float)money);
}


Player* GameScene::get_land_owner(int Id)
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



int GameScene::area_land_pay(float x, float y, Player* player, int id1, int id2, int id3)
{
	area_land.Clear();
	int money = 0;
	Point p = player->GetPosition();
	float nowx = Ui::chang_GL_to_map(p, map).x;
	float nowy = Ui::chang_GL_to_map(p, map).y;
	if (nowx == x)
	{
		float left = x - 1;
		float right = x + 1;
		int leftid = land->GetTileGIDAt(Vec2(left, y));
		int rightid = land->GetTileGIDAt(Vec2(right, y));
		area_land.PushBack(land->GetTileAt(Vec2(x, y)));
		while (leftid != 0 && (leftid == id1+land_id || leftid == id2+land_id || leftid == id3+land_id))
		{
			if (leftid == id1+land_id)
				money += 500;
			if (leftid == id2+land_id)
				money += 1000;
			if (leftid == id3+land_id)
				money += 2000;
			area_land.PushBack(land->GetTileAt(Vec2(left, y)));
			left -= 1;
			leftid = land->GetTileGIDAt(Vec2(left, y));
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
			area_land.PushBack(land->GetTileAt(Vec2(right, y)));
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
		area_land.PushBack(land->GetTileAt(Vec2(x, y)));
		while (upid != 0 && (upid == id1+land_id || upid == id2+land_id || upid == id3+land_id))
		{
			if (upid == id1+land_id)
				money += 500;
			if (upid == id2+land_id)
				money += 1000;
			if (upid == id3+land_id)
				money += 2000;
			area_land.PushBack(land->GetTileAt(Vec2(x, up)));
			up -= 1;
			upid = land->GetTileGIDAt(Vec2(x, up));
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
			area_land.PushBack(land->GetTileAt(Vec2(x, down)));
			down += 1;
			downid = land->GetTileGIDAt(Vec2(x, down));
			if (downid == 0)
				break;
		}
	}
	for (auto it = area_land.Begin(); it != area_land.End(); it++)
	{
		(*it)->RunAction(Sequence::Create(FadeOut::Create(0.5)->clone(), FadeIn::Create(0.5)->clone(), NULL));
	}
	return money;
}





