#include"Control.h"
#include"GameSceneScene.h"
#include"route.h"
#include"Ui.h"
#include"Duang.h"


Control* Control::control_Instance = NULL;

Control::Control()
{
	comeX = -1;
	comeY = -1;
	struct timeval now;
	gettimeofday(&now, NULL);
	unsigned rand_seed = (unsigned)(now.tv_sec * 1000 + now.tv_usec / 1000);
	srand(rand_seed);
}

bool Control::Init()
{
	if (!Layer::Init())
		return false;

	res_notification_Observe();
	oneRoundend = false;
	return true;
}
//Add a registry in order to call some certain functions
void Control::res_notification_Observe()
{
	NotificationCenter::GetInstance()->addObserver(this, callfuncO_selector(Control::ReceiveMsg), MSG_PICKONE_TOGO, NULL);
}
//Registry Callback
void Control::ReceiveMsg(Object* node)
{
	int res = ((String*)node)->intValue();
	if (res == MSG_PICKONE_TOGO_TAG)
	{
		RobotWalk();
	}
}

Control* Control::GetInstance()
{
	if (!control_Instance)
	{
		control_Instance = new Control();
		control_Instance->Init();
	}

	return control_Instance;
}

Control::~Control()
{
	control_Instance = NULL;
}
//Move the character one step ahead
void Control::MoveOne(Player* player)
{
	row = pathRow[_step + 1];
	col = pathCol[_step + 1];
	int disr = row - nowRow;
	int disc = col - nowCol;
	MoveBy* moveby;
	Repeat* repeate;
	Action* action;
	if (disr > 0)
	{
		moveby = MoveBy::Create(1.2f, Vec2(0, tileHeigh));
		repeate = Repeat::Create(Player->up, 1.2f);
	}
	if (disr < 0)
	{
		moveby = MoveBy::Create(1.2f, Vec2(0, -tileHeigh));
		repeate = Repeat::Create(Player->down, 1.2f);
	}
	if (disc > 0)
	{

		moveby = MoveBy::Create(1.2f, Vec2(tileWidth, 0));
		repeate = Repeat::Create(Player->right, 1.2f);
	}
	if (disc < 0)
	{
		moveby = MoveBy::Create(1.2f, Vec2(-tileWidth, 0));
		repeate = Repeat::Create(Player->left, 1.2f);
	}

	action = Sequence::Create(Spawn::Create(moveby, repeate, nullptr), CallFunc::Create(CC_CALLBACK_0(Control::EndGo, this)), nullptr);
	action->retain();
	Player->RunAction(action);
}

//The current character starts moving 
//rowVector and colVector stores the path of the current character
//Player points to the current character
void Control::StartGo(std::vector<int>pathRow,std::vector<int>pathCol,Player* player)
{
	nowCol = pathCol[0];
	nowRow = pathRow[0];
	row = col = 0;
	this->pathRow = pathRow;
	this->pathCol = pathCol;
	this->Player = player;
	_step = 0;
	_stepCount = pathRow.size() - 1;
	if (_stepCount == 0)
	{
		EndEvent();
	}
	else
	{
		MoveOne(Player);
	}
}

//Deal with the events when the character has finished moving and ended up in one specific tile
void Control::EndGo()
{
	GameScene::GetStepImage()->at(_step)->SetVisible(false);
	_step++;
	if (_step >= _stepCount)
	{
		float x = pathCol[_step] * tileWidth;
		float y = pathRow[_step] * tileHeigh + tileHeigh;
		Point mapPoint = Ui::chang_GL_to_map(Vec2(x, y), GameScene::GetMap());
		int id = GameScene::GetMap()->layerNamed(OPPORTUNITY)->GetTileGIDAt(mapPoint);
		int id1 = GameScene::GetMap()->layerNamed(WAY_BLOCK_NAME)->GetTileGIDAt(mapPoint);
		int ID = GameScene::GetMap()->propertiesForGID(id1).asValueMap()["location"].asInt();
		if (ID)
		{
			image = GameScene::get_location_image()->at(ID - 1);
			image->SetVisible(true);
			image->RunAction(Spawn::Create(FadeIn::Create(1.0f),FadeOut::Create(3.0f),NULL));
			
		}
		if (id == GameScene::Get_quesMark_id())
		{
			srand(clock());
			log("card");
			int type = random() % 9;
			switch (type)
			{
			case 0:
			case 1:
			{
					  int number = random() % 6;
					  Forwards::GetInstance()->at(number)->RunAction(player);
			}; break;
			case 2:
			case 3:
			{
					  int number = random() % 7;
					  Delay::GetInstance()->at(number)->RunAction(player);
					  EndEvent();
			}; break;
			case 4:
			case 5:
			case 6:
			case 7:
			{
					  int number = random() % 9;
					  Wealth::GetInstance()->at(number)->RunAction(player);
					  EndEvent();
			}; break;
			case 8:
			{
					  Player->GetLottery();
					  PopLottery();
					  Player->RunAction(Sequence::Create(DelayTime::Create(2.0f), CallFunc::Create([this]{
						  EndEvent();
					  }), NULL));
			}; break;
			}
			
		}
		else

		    EndEvent();
		return;
	}
	nowCol = col;
	nowRow = row;
	MoveOne(player);
}

//Lottery publish
void Control::PopLottery()
{
	GameScene::GetDialogLottery()->SetVisible(true);
	GameScene::GetDialogLottery()->AddPlayerLottery();
	GameScene::GetDialogLottery()->RunAnmi();
}


//Non-player characters Move
void Control::RobotWalk()
{
	for (auto it = GameScene::GetPlayers()->begin(); it != GameScene::GetPlayers()->end(); it++)
	{
		auto Player1 = dynamic_cast<Player*>(*it);

		if (Player1->getturnme())
		{
			int randNumber = rand() % 6 + 1;
			Route::GetInstance()->GetPath(Player1,GameScene::isWalk, randNumber,GameScene::GetColCount(),GameScene::GetRowCount());
			Player1->Go(Route::GetInstance()->GetPathRow(), Route::GetInstance()->GetPathCol());
			return;
		}

	}
	GameScene::GetGo()->SetPosition(GameScene::GetGo()->GetPosition() + Vec2(0, 500));
	GameScene::GetGo()->SetVisible(true);
	oneRoundend = true;
	ResetPlayerGoTurn();
}

//The remaining characters initiation
void Control::ResetPlayerGoTurn()
{
	for (auto it = GameScene::GetPlayers()->begin(); it != GameScene::GetPlayers()->end(); it++)
	{
		Player* richerPlayer = dynamic_cast<Player*>(*it);
		richerPlayer->setturnme(true);

	}
}
//end oneround
void Control::EndEvent()
{
	oneRoundend = false;
	float x = pathCol[_step] * tileWidth;
	float y = pathRow[_step] * tileHeigh + tileHeigh;
	std::vector<Vec2>dir;
	dir.push_back(Vec2(x, y + tileHeigh));
	dir.push_back(Vec2(x, y - tileHeigh));
	dir.push_back(Vec2(x - tileWidth, y));
	dir.push_back(Vec2(x + tileWidth, y));
	int flag = 0;
	for (int i = 0; i < 4; i++)
	{
		Point mapPoint = Ui::chang_GL_to_map(dir.at(i), GameScene::GetMap());
		int id = GameScene::GetLandLayer()->GetTileGIDAt(mapPoint);
		GameScene::buy_land_x = mapPoint.x;
		GameScene::buy_land_y = mapPoint.y;
		if (id == GameScene::GetLand_id())
		{
			flag++;
			String* str = String::createWithFormat("%d-%f-%f-%d", MSG_BUY_BLANK_TAG, mapPoint.x, mapPoint.y, Player->getTag());
			NotificationCenter::GetInstance()->postNotification(MSG_BUY, str);
			break;
		}
		if (id == PLAYER1_LEVEL1_LAND_ID + GameScene::GetLand_id())
		{
			if (Player->getTag() == PLAYER1_TAG)
			{
				flag++;
				String* str = String::createWithFormat("%d-%f-%f-%d", MSG_BUY_LAND_1_TAG, mapPoint.x, mapPoint.y, Player->getTag());
				NotificationCenter::GetInstance()->postNotification(MSG_BUY, str);
				break;
			}
			else
			{
				flag++;
				String* str = String::createWithFormat("%d-%f-%f-%d", MSG_PAY_TOLLS_1_TAG, mapPoint.x, mapPoint.y, Player->getTag());
				NotificationCenter::GetInstance()->postNotification(MSG_PAY_TOLLS, str);
				break;
			}
		}
		if (id == PLAYER2_LEVEL1_LAND_ID + GameScene::GetLand_id())
		{
			flag++;
			if (Player->getTag() == PLAYER2_TAG)
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", MSG_BUY_LAND_1_TAG, mapPoint.x, mapPoint.y, Player->getTag());
				NotificationCenter::GetInstance()->postNotification(MSG_BUY, str);
				break;
			}
			else
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", MSG_PAY_TOLLS_1_TAG, mapPoint.x, mapPoint.y, Player->getTag());
				NotificationCenter::GetInstance()->postNotification(MSG_PAY_TOLLS, str);
				break;
			}
		}
		if (id == PLAYER3_LEVEL1_LAND_ID + GameScene::GetLand_id())
		{
			flag++;
			if (Player->getTag() == PLAYER3_TAG)
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", MSG_BUY_LAND_1_TAG, mapPoint.x, mapPoint.y, Player->getTag());
				NotificationCenter::GetInstance()->postNotification(MSG_BUY, str);
				break;
			}
			else
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", MSG_PAY_TOLLS_1_TAG, mapPoint.x, mapPoint.y, Player->getTag());
				NotificationCenter::GetInstance()->postNotification(MSG_PAY_TOLLS, str);
				break;
			}
		}
		if (id == PLAYER4_LEVEL1_LAND_ID + GameScene::GetLand_id())
		{
			flag++;
			if (Player->getTag() == PLAYER4_TAG)
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", MSG_BUY_LAND_1_TAG, mapPoint.x, mapPoint.y, Player->getTag());
				NotificationCenter::GetInstance()->postNotification(MSG_BUY, str);
				break;
			}
			else
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", MSG_PAY_TOLLS_1_TAG, mapPoint.x, mapPoint.y, Player->getTag());
				NotificationCenter::GetInstance()->postNotification(MSG_PAY_TOLLS, str);
				break;
			}
		}
		if (id == PLAYER1_LEVEL2_LAND_ID + GameScene::GetLand_id())
		{
			flag++;
			if (Player->getTag() == PLAYER1_TAG)
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", MSG_BUY_LAND_2_TAG, mapPoint.x, mapPoint.y, Player->getTag());
				NotificationCenter::GetInstance()->postNotification(MSG_BUY, str);
				break;
			}
			else
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", MSG_PAY_TOLLS_2_TAG, mapPoint.x, mapPoint.y, Player->getTag());
				NotificationCenter::GetInstance()->postNotification(MSG_PAY_TOLLS, str);
				break;
			}
		}
		if (id == PLAYER2_LEVEL2_LAND_ID + GameScene::GetLand_id())
		{
			flag++;
			if (Player->getTag() == PLAYER2_TAG)
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", MSG_BUY_LAND_2_TAG, mapPoint.x, mapPoint.y, Player->getTag());
				NotificationCenter::GetInstance()->postNotification(MSG_BUY, str);
				break;
			}
			else
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", MSG_PAY_TOLLS_2_TAG, mapPoint.x, mapPoint.y, Player->getTag());
				NotificationCenter::GetInstance()->postNotification(MSG_PAY_TOLLS, str);
				break;
			}
		}
		if (id == PLAYER3_LEVEL2_LAND_ID + GameScene::GetLand_id())
		{
			flag++;
			if (Player->getTag() == PLAYER3_TAG)
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", MSG_BUY_LAND_2_TAG, mapPoint.x, mapPoint.y, Player->getTag());
				NotificationCenter::GetInstance()->postNotification(MSG_BUY, str);
				break;
			}
			else
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", MSG_PAY_TOLLS_2_TAG, mapPoint.x, mapPoint.y, Player->getTag());
				NotificationCenter::GetInstance()->postNotification(MSG_PAY_TOLLS, str);
				break;
			}
		}
		if (id == PLAYER4_LEVEL2_LAND_ID + GameScene::GetLand_id())
		{
			flag++;
			if (Player->getTag() == PLAYER4_TAG)
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", MSG_BUY_LAND_2_TAG, mapPoint.x, mapPoint.y, Player->getTag());
				NotificationCenter::GetInstance()->postNotification(MSG_BUY, str);
				break;
			}
			else
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", MSG_PAY_TOLLS_2_TAG, mapPoint.x, mapPoint.y, Player->getTag());
				NotificationCenter::GetInstance()->postNotification(MSG_PAY_TOLLS, str);
				break;
			}
		}
		if (id == PLAYER1_LEVEL3_LAND_ID + GameScene::GetLand_id())
		{
			flag++;
			if (Player->getTag() == PLAYER1_TAG)
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", MSG_CON_GO, mapPoint.x, mapPoint.y, Player->getTag());
				NotificationCenter::GetInstance()->postNotification(MSG_BUY, str);
				break;
			}
			else
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", MSG_PAY_TOLLS_3_TAG, mapPoint.x, mapPoint.y, Player->getTag());
				NotificationCenter::GetInstance()->postNotification(MSG_PAY_TOLLS, str);
				break;
			}
		}
		if (id == PLAYER2_LEVEL3_LAND_ID + GameScene::GetLand_id())
		{
			flag++;
			if (Player->getTag() == PLAYER2_TAG)
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", MSG_CON_GO, mapPoint.x, mapPoint.y, Player->getTag());
				NotificationCenter::GetInstance()->postNotification(MSG_BUY, str);
				break;
			}
			else
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", MSG_PAY_TOLLS_3_TAG, mapPoint.x, mapPoint.y, Player->getTag());
				NotificationCenter::GetInstance()->postNotification(MSG_PAY_TOLLS, str);
				break;
			}
		}
		if (id == PLAYER3_LEVEL3_LAND_ID + GameScene::GetLand_id())
		{
			flag++;
			if (Player->getTag() == PLAYER3_TAG)
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", MSG_CON_GO, mapPoint.x, mapPoint.y, Player->getTag());
				NotificationCenter::GetInstance()->postNotification(MSG_BUY, str);
				break;
			}
			else
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", MSG_PAY_TOLLS_3_TAG, mapPoint.x, mapPoint.y, Player->getTag());
				NotificationCenter::GetInstance()->postNotification(MSG_PAY_TOLLS, str);
				break;
			}
		}
		if (id == PLAYER4_LEVEL3_LAND_ID + GameScene::GetLand_id())
		{
			flag++;
			if (Player->getTag() == PLAYER4_TAG)
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", MSG_CON_GO, mapPoint.x, mapPoint.y, Player->getTag());
				NotificationCenter::GetInstance()->postNotification(MSG_BUY, str);
				break;
			}
			else
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", MSG_PAY_TOLLS_3_TAG, mapPoint.x, mapPoint.y, Player->getTag());
				NotificationCenter::GetInstance()->postNotification(MSG_PAY_TOLLS, str);
				break;
			}
		}
	}
	if (!flag)
	{
		NotificationCenter::GetInstance()->postNotification(MSG_PICKONE_TOGO, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
	}
}




