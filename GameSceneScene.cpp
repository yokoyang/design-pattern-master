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
    
    visibleSize = Director::GetInstance()->GetVisibleSize();
    Vec2 origin = Director::GetInstance()->GetVisibleOrigin();

	auto background = Sprite::Create("world.jpg");
	background->SetPosition(visibleSize / 2);
	background->SetAnchorPoint(Vec2(0.5, 0.5));
	background->SetScale(1.5);
	AddChild(background);
	AddProgressTimer();
	ScheduleOnce(schedule_selector(GameScene::Add_infor), 1.60f);

    return true;
}

//Add all sorts of game resources
void GameScene::Add_infor(float t)
{
	auto Size = Director::GetInstance()->GetVisibleSize();
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
	back->SetPosition(150, 50);
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
	auto Size = Director::GetInstance()->GetVisibleSize();
	progressBgSprite = Sprite::Create("slider.png");
	progressBgSprite->SetPosition(Size/2);
	AddChild(progressBgSprite);
	auto progressSprite1 = Sprite::Create("slider.png");
	progress1 = ProgressTimer::Create(progressSprite1);
	progress1->SetType(kCCProgressTimerTypeBar);
	progress1->SetPosition(Size/2);
	progress1->SetMidpoint(Vec2(0, 0));
	progress1->SetBarChangeRate(Vec2(1, 0));
	progress1->SetPercentage(0);
	AddChild(progress1);
	numsTTF = Label::CreateWithTTF("0", "fonts/Gazzarel.TTF", 18);
	numsTTF->SetPosition(Vec2(300, 300));
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
		numsTTF->SetVisible(false);
		progress1->SetVisible(false);
		progressBgSprite->SetVisible(false);
	}
}

void GameScene::AddFinal_layer()
{
	final_layer = FinalScene::Create();
	AddChild(final_layer);
	final_layer->SetPosition(visibleSize / 2);
	final_layer->SetVisible(false);
}

void GameScene::Addmap(int type)
{
	if (type == 1)
	{
		map = TMXTiledMap::Create("map1.tmx");
		auto background = Sprite::Create("Sea.jpg");
		background->SetAnchorPoint(Vec2(0.5, 0.5));
		background->SetPosition(visibleSize / 2);
		background->SetScale(visibleSize.width / background->GetContentSize().width, visibleSize.height / background->GetContentSize().height);
		AddChild(background);
	}
	else if (type == 2)
	{
		map = TMXTiledMap::Create("map2.tmx");
		auto background = Sprite::Create("Sea.jpg");
		background->SetAnchorPoint(Vec2(0.5, 0.5));
		background->SetPosition(visibleSize / 2);
		background->SetScale(visibleSize.width / background->GetContentSize().width, visibleSize.height / background->GetContentSize().height);
		AddChild(background);
	}
	else if (type == 3)
	{
		map = TMXTiledMap::Create("map3.tmx");
		auto background = Sprite::Create("Sea.jpg");
		background->SetAnchorPoint(Vec2(0.5, 0.5));
		background->SetPosition(visibleSize / 2); background->SetScale(visibleSize.width / background->GetContentSize().width, visibleSize.height / background->GetContentSize().height); e().height);
		AddChild(background);
	}
	AddChild(map);
	map->SetAnchorPoint(Point(0.5, 0.5));
	map->SetPosition(visibleSize.width / 2 - 100, visibleSize.height / 2);
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
		player->SetAnchorPoint(Point(0.5,0.5));
		player->SetPosition(Vec2(visibleSize.width / 24 * 19, visibleSize.height / number / 2 + (number - 1 - i) * visibleSize.height / number));
	}
}


void GameScene::AddPlayerImg()
{
	playerImg->Clear();
	auto player1 = Sprite::Create("player1.jpg");
	auto player2 = Sprite::Create("player2.png");
	auto player3 = Sprite::Create("player3.png");
	auto player4 = Sprite::Create("player4.png");
	playerImg->PushBack(player1);
	playerImg->PushBack(player2);
	playerImg->PushBack(player3);
	playerImg->PushBack(player4);
}

void GameScene::Add_location_image()
{
	if (!location_image->Empty())
	{
		return;
	}
	auto temp1 = Sprite::Create("Austria.jpg");
	auto temp2 = Sprite::Create("Australia.jpg");
	auto temp3 = Sprite::Create("Belgium.jpg");
	auto temp4 = Sprite::Create("Beijing.jpg");
	auto temp5 = Sprite::Create("Bermingham.jpg");
	auto temp6 = Sprite::Create("Bhutan.jpg");
	auto temp7 = Sprite::Create("Chicago.jpg");
	auto temp8 = Sprite::Create("Coppenhagen.jpg");
	auto temp9 = Sprite::Create("Desert.jpg");
	auto temp10 = Sprite::Create("Dubai.jpg");
	auto temp11 = Sprite::Create("FujiYama.jpg");
	auto temp12 = Sprite::Create("Guilin.jpg");
	auto temp13 = Sprite::Create("Hainan.jpg");
	auto temp14 = Sprite::Create("India.jpg");
	auto temp15 = Sprite::Create("Iraq.jpg");
	auto temp16 = Sprite::Create("Jiangnan.jpg");
	auto temp17 = Sprite::Create("LA.jpg");
	auto temp18 = Sprite::Create("London.jpg");
	auto temp19 = Sprite::Create("Maldives.jpg");
	auto temp20 = Sprite::Create("Manchester.jpg");
	auto temp21 = Sprite::Create("Mongolia.jpg");
	auto temp22 = Sprite::Create("Moscow.jpg");
	auto temp23 = Sprite::Create("Nara.jpg");
	auto temp24 = Sprite::Create("Norway.jpg");
	auto temp25 = Sprite::Create("NY.jpg");
	auto temp26 = Sprite::Create("Pakistan.jpg");
	auto temp27 = Sprite::Create("Paris.jpg");
	auto temp28 = Sprite::Create("Phillipines.jpg");
	auto temp29 = Sprite::Create("Portugal.jpg");
	auto temp30 = Sprite::Create("Qinghai.jpg");
	auto temp31 = Sprite::Create("SH.jpg");
	auto temp32 = Sprite::Create("Singapore.jpg");
	auto temp33 = Sprite::Create("Spain.jpg");
	auto temp34 = Sprite::Create("Switzerland.jpg");
	auto temp35 = Sprite::Create("Thailand.jpg");
	auto temp36 = Sprite::Create("Tibet.jpg");
	auto temp37 = Sprite::Create("Toulouse.jpg");
	auto temp38 = Sprite::Create("Vatican.jpg");
	auto temp39 = Sprite::Create("Vienna.jpg");
	auto temp40 = Sprite::Create("Yunnan.jpg");
	location_image->PushBack(temp1);
	location_image->PushBack(temp2);
	location_image->PushBack(temp3);
	location_image->PushBack(temp4);
	location_image->PushBack(temp5);
	location_image->PushBack(temp6);
	location_image->PushBack(temp7);
	location_image->PushBack(temp8);
	location_image->PushBack(temp9); 
	location_image->PushBack(temp10);
	location_image->PushBack(temp11);
	location_image->PushBack(temp12);
	location_image->PushBack(temp13);
	location_image->PushBack(temp14);
	location_image->PushBack(temp15);
	location_image->PushBack(temp16);
	location_image->PushBack(temp17);
	location_image->PushBack(temp18);
	location_image->PushBack(temp19);
	location_image->PushBack(temp20);
	location_image->PushBack(temp21);
	location_image->PushBack(temp22);
	location_image->PushBack(temp23);
	location_image->PushBack(temp24);
	location_image->PushBack(temp25);
	location_image->PushBack(temp26);
	location_image->PushBack(temp27);
	location_image->PushBack(temp28);
	location_image->PushBack(temp29);
	location_image->PushBack(temp30);
	location_image->PushBack(temp31);
	location_image->PushBack(temp32);
	location_image->PushBack(temp33);
	location_image->PushBack(temp34);
	location_image->PushBack(temp35);
	location_image->PushBack(temp36);
	location_image->PushBack(temp37);
	location_image->PushBack(temp38);
	location_image->PushBack(temp39);
	location_image->PushBack(temp40);
	AddChild(temp1);
	AddChild(temp2);
	AddChild(temp3);
	AddChild(temp4);
	AddChild(temp5);
	AddChild(temp6);
	AddChild(temp7);
	AddChild(temp8);
	AddChild(temp9);
	AddChild(temp10);
	AddChild(temp11);
	AddChild(temp12);
	AddChild(temp13);
	AddChild(temp14);
	AddChild(temp15);
	AddChild(temp16);
	AddChild(temp17);
	AddChild(temp18);
	AddChild(temp19);
	AddChild(temp20);
	AddChild(temp21);
	AddChild(temp22);
	AddChild(temp23);
	AddChild(temp24);
	AddChild(temp25);
	AddChild(temp26);
	AddChild(temp27);
	AddChild(temp28);
	AddChild(temp29);
	AddChild(temp30);
	AddChild(temp31);
	AddChild(temp32);
	AddChild(temp33);
	AddChild(temp34);
	AddChild(temp35);
	AddChild(temp36);
	AddChild(temp37);
	AddChild(temp38);
	AddChild(temp39);
	AddChild(temp40);
	temp1->SetVisible(false);
	temp2->SetVisible(false);
	temp3->SetVisible(false);
	temp4->SetVisible(false);
	temp5->SetVisible(false);
	temp6->SetVisible(false);
	temp7->SetVisible(false);
	temp8->SetVisible(false);
	temp9->SetVisible(false);
	temp10->SetVisible(false);
	temp11->SetVisible(false);
	temp12->SetVisible(false);
	temp13->SetVisible(false);
	temp14->SetVisible(false);
	temp15->SetVisible(false);
	temp16->SetVisible(false);
	temp17->SetVisible(false);
	temp18->SetVisible(false);
	temp19->SetVisible(false);
	temp20->SetVisible(false);
	temp21->SetVisible(false);
	temp22->SetVisible(false);
	temp23->SetVisible(false);
	temp24->SetVisible(false);
	temp25->SetVisible(false);
	temp26->SetVisible(false);
	temp27->SetVisible(false);
	temp28->SetVisible(false);
	temp29->SetVisible(false);
	temp30->SetVisible(false);
	temp31->SetVisible(false);
	temp32->SetVisible(false);
	temp33->SetVisible(false);
	temp34->SetVisible(false);
	temp35->SetVisible(false);
	temp36->SetVisible(false);
	temp37->SetVisible(false);
	temp38->SetVisible(false);
	temp39->SetVisible(false);
	temp40->SetVisible(false);
	temp1->SetAnchorPoint(Vec2(0.5, 0.5));
	temp1->SetPosition(visibleSize / 2);
	temp2->SetAnchorPoint(Vec2(0.5, 0.5));
	temp2->SetPosition(visibleSize / 2);
	temp3->SetAnchorPoint(Vec2(0.5, 0.5));
	temp3->SetPosition(visibleSize / 2);
	temp4->SetAnchorPoint(Vec2(0.5, 0.5));
	temp4->SetPosition(visibleSize / 2);
	temp5->SetAnchorPoint(Vec2(0.5, 0.5));
	temp5->SetPosition(visibleSize / 2);
	temp6->SetAnchorPoint(Vec2(0.5, 0.5));
	temp6->SetPosition(visibleSize / 2);
	temp7->SetAnchorPoint(Vec2(0.5, 0.5));
	temp7->SetPosition(visibleSize / 2);
	temp8->SetAnchorPoint(Vec2(0.5, 0.5));
	temp8->SetPosition(visibleSize / 2);
	temp9->SetAnchorPoint(Vec2(0.5, 0.5));
	temp9->SetPosition(visibleSize / 2);
	temp10->SetAnchorPoint(Vec2(0.5, 0.5));
	temp10->SetPosition(visibleSize / 2);
	temp11->SetAnchorPoint(Vec2(0.5, 0.5));
	temp11->SetPosition(visibleSize / 2);
	temp12->SetAnchorPoint(Vec2(0.5, 0.5));
	temp12->SetPosition(visibleSize / 2);
	temp13->SetAnchorPoint(Vec2(0.5, 0.5));
	temp13->SetPosition(visibleSize / 2);
	temp14->SetAnchorPoint(Vec2(0.5, 0.5));
	temp14->SetPosition(visibleSize / 2);
	temp15->SetAnchorPoint(Vec2(0.5, 0.5));
	temp15->SetPosition(visibleSize / 2);
	temp16->SetAnchorPoint(Vec2(0.5, 0.5));
	temp16->SetPosition(visibleSize / 2);
	temp17->SetAnchorPoint(Vec2(0.5, 0.5));
	temp17->SetPosition(visibleSize / 2);
	temp18->SetAnchorPoint(Vec2(0.5, 0.5));
	temp18->SetPosition(visibleSize / 2);
	temp19->SetAnchorPoint(Vec2(0.5, 0.5));
	temp19->SetPosition(visibleSize / 2);
	temp20->SetAnchorPoint(Vec2(0.5, 0.5));
	temp20->SetPosition(visibleSize / 2);
	temp21->SetAnchorPoint(Vec2(0.5, 0.5));
	temp21->SetPosition(visibleSize / 2);
	temp22->SetAnchorPoint(Vec2(0.5, 0.5));
	temp22->SetPosition(visibleSize / 2);
	temp23->SetAnchorPoint(Vec2(0.5, 0.5));
	temp23->SetPosition(visibleSize / 2);
	temp24->SetAnchorPoint(Vec2(0.5, 0.5));
	temp24->SetPosition(visibleSize / 2);
	temp25->SetAnchorPoint(Vec2(0.5, 0.5));
	temp25->SetPosition(visibleSize / 2);
	temp26->SetAnchorPoint(Vec2(0.5, 0.5));
	temp26->SetPosition(visibleSize / 2);
	temp27->SetAnchorPoint(Vec2(0.5, 0.5));
	temp27->SetPosition(visibleSize / 2);
	temp28->SetAnchorPoint(Vec2(0.5, 0.5));
	temp28->SetPosition(visibleSize / 2);
	temp29->SetAnchorPoint(Vec2(0.5, 0.5));
	temp29->SetPosition(visibleSize / 2);
	temp30->SetAnchorPoint(Vec2(0.5, 0.5));
	temp30->SetPosition(visibleSize / 2);
	temp31->SetAnchorPoint(Vec2(0.5, 0.5));
	temp31->SetPosition(visibleSize / 2);
	temp32->SetAnchorPoint(Vec2(0.5, 0.5));
	temp32->SetPosition(visibleSize / 2);
	temp33->SetAnchorPoint(Vec2(0.5, 0.5));
	temp33->SetPosition(visibleSize / 2);
	temp34->SetAnchorPoint(Vec2(0.5, 0.5));
	temp34->SetPosition(visibleSize / 2);
	temp35->SetAnchorPoint(Vec2(0.5, 0.5));
	temp35->SetPosition(visibleSize / 2);
	temp36->SetAnchorPoint(Vec2(0.5, 0.5));
	temp36->SetPosition(visibleSize / 2);
	temp37->SetAnchorPoint(Vec2(0.5, 0.5));
	temp37->SetPosition(visibleSize / 2);
	temp38->SetAnchorPoint(Vec2(0.5, 0.5));
	temp38->SetPosition(visibleSize / 2);
	temp39->SetAnchorPoint(Vec2(0.5, 0.5));
	temp39->SetPosition(visibleSize / 2);
	temp40->SetAnchorPoint(Vec2(0.5, 0.5));
	temp40->SetPosition(visibleSize / 2);
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
	player1->SetAnchorPoint(Point(0, 0.5));
	Point q = point[0];
	q.y = tileheigh + q.y;
	map->AddChild(player1);
	player1->SetPosition(q);
	player1->SetTurnMe(true);
	player1->Set_id(3, 6, 9);
	framecache->AddSpriteFramesWithFile("player2_anim.plist", "player2_anim.png");
	auto s2 = framecache->GetSpriteFrameByName("player2_anim_01.png");
	auto player2 = Player::Createwith("player2", 2, s2, money);
	player2->SettileSize(tilewidth, tileheigh);
	Point q1 = point[39];
	q1.y = tileheigh + q1.y;
	map->AddChild(player2);
	player2->SetPosition(q1);
	player2->SetAnchorPoint(Point(0, 0.5));
	player2->SetTurnMe(true);
	player2->Set_id(1, 4, 7);
	framecache->AddSpriteFramesWithFile("player3_anim.plist", "player3_anim.png");
	auto s3 = framecache->GetSpriteFrameByName("player3_anim_01.png");
	auto player3 = Player::Createwith("player3", 3, s3, money);
	player3->SettileSize(tilewidth, tileheigh);
	Point q2 = point[10];
	q2.y = tileheigh + q2.y;
	map->AddChild(player3);
	player3->SetPosition(q2);
	player3->SetAnchorPoint(Point(0, 0.5));
	player3->SetTurnMe(true);
	player3->Set_id(2, 5, 8);
	framecache->AddSpriteFramesWithFile("player4_anim.plist", "player4_anim.png");
	auto s4 = framecache->GetSpriteFrameByName("player4_anim_01.png");
	auto player4 = Player::Createwith("player4", 4, s4, money);
	player4->SettileSize(tilewidth, tileheigh);
	Point q3 = point[29];
	q3.y = tileheigh + q3.y;
	map->AddChild(player4);
	player4->SetPosition(q3);
	player4->SetAnchorPoint(Point(0, 0.5));
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
		player4->SetVisible(false);
	}
	else if (number == 2)
	{
		players->PushBack(player1);
		players->PushBack(player2);
		player3->SetVisible(false);
		player4->SetVisible(false);
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
		(*it)->GetMoney_string()->SetPosition(visibleSize.width / 12 * 11, (number - j + 1) * visibleSize.height / number - visibleSize.height / number / 2 - 30);
		(*it)->GetName()->SetPosition(visibleSize.width / 12 * 11, (number - j + 1) * visibleSize.height / number - visibleSize.height / number / 2 + 40);
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
	go->SetAnchorPoint(Point(0,1));
	go->SetPosition(Vec2(280, 80));
	auto touch = EventListenerTouchOneByOne::Create();
	bool** isWalkCopy = isWalk;
	auto Go = go;
	touch->onTouchBegan = [i,isWalkCopy,Go,this](Touch* t, Event* e){
		if (e->GetCurrentTarGet()->GetBoundingBox().ContainsPoint(t->GetLocation()))
		{
			Go->SetVisible(false);
			Go->SetPosition(Go->GetPosition() - Vec2(0, 500));
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
	auto image1 = Sprite::Create("Marker1.png");
	auto image2 = Sprite::Create("Marker2.png");
	auto image3 = Sprite::Create("Marker3.png");
	auto image4 = Sprite::Create("Marker4.png");
	auto image5 = Sprite::Create("Marker5.png");
	auto image6 = Sprite::Create("Marker6.png");
	step_image->PushBack(image1);
	step_image->PushBack(image2);
	step_image->PushBack(image3);
	step_image->PushBack(image4);
	step_image->PushBack(image5);
	step_image->PushBack(image6);
	image1->SetVisible(false);
	image2->SetVisible(false);
	image3->SetVisible(false);
	image4->SetVisible(false);
	image5->SetVisible(false);
	image6->SetVisible(false);
	map->AddChild(image1);
	map->AddChild(image2);
	map->AddChild(image3);
	map->AddChild(image4);
	map->AddChild(image5);
	map->AddChild(image6);
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
	dialog->SetVisible(false);
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
	dialogLottery->SetVisible(false);

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
			image1->SetPosition(Ui::chang_map_to_GL( Vec2(buy_land_x, buy_land_y),map).x+16,Ui::chang_map_to_GL(Vec2(buy_land_x,buy_land_y),map).y+16);
			image1->SetVisible(true);
			map->AddChild(image1);
			image1->SetAnchorPoint(Vec2(0.5, 0.5));
			dialog->SetVisible(false);

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
			image1->SetPosition(Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).x + 16, Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).y + 16);
			image1->SetVisible(true);
			map->AddChild(image1);
			image1->SetAnchorPoint(Vec2(0.5, 0.5));
			dialog->SetVisible(false);

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
			image1->SetPosition(Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).x + 16, Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).y + 16);
			image1->SetVisible(true);
			map->AddChild(image1);
			image1->SetAnchorPoint(Vec2(0.5, 0.5));
			dialog->SetVisible(false);

			CocosDenshion::SimpleAudioEngine::GetInstance()->PlayEffect("Sounding/Speaking_00458.wav");

			
			UpdateMoney(player, -3000);
			NotificationCenter::GetInstance()->PostNotification("one_go", String::CreateWithFormat("%d", 5));
			break;
		}
		}
	}
	else
	{
		dialog->SetVisible(false);
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
		dialog->SetVisible(true);
	}
	else if (tag == 3)
	{
		show = "Upgrade Your Estate to Level 2? $ 2000 Needed";
		dialog->SetDataTag(3);
		dialog->GetLabelContentText()->SetString(show.GetCString());
		dialog->SetVisible(true);
	}
	else if (tag == 4)
	{
		show = "Upgrade Your Estate to Level 3? $ 3000 Needed";
		dialog->SetDataTag(4);
		dialog->GetLabelContentText()->SetString(show.GetCString());
		dialog->SetVisible(true);
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

			image->SetPosition(Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).x + 16, Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).y + 16);
			image->SetVisible(true);
			map->AddChild(image);
			image->SetAnchorPoint(Vec2(0.5, 0.5));
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
			image->SetPosition(Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).x + 16, Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).y + 16);
			image->SetVisible(true);
			map->AddChild(image);
			image->SetAnchorPoint(Vec2(0.5, 0.5));
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

			image->SetPosition(Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).x + 16, Ui::chang_map_to_GL(Vec2(buy_land_x, buy_land_y), map).y + 16);
			image->SetVisible(true);
			map->AddChild(image);
			image->SetAnchorPoint(Vec2(0.5, 0.5));
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





