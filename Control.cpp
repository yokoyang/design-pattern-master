#include"Control.h"
#include"GameSceneScene.h"
#include"Route.h"
#include"Ui.h"
#include "Opportunity.h"
#include"player.h"


Control* Control::control_Instance = NULL;

Control::Control()
{
	comeX = -1;
	comeY = -1;
	struct timeval now;
	Get_time_of_day(&now, NULL);
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
	NotificationCenter::GetInstance()->AddObserver(this, CallFuncO_selector(Control::ReceiveMsg), "one_go", NULL);
}
//Registry Callback
void Control::ReceiveMsg(Object* node)
{
	int res = ((String*)node)->IntValue();
	if (res == 5)
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
	int disr = row - nowrow;
	int disc = col - nowcol;
	MoveBy* moveby;
	Repeat* repeate;
	Action* action;
	if (disr > 0)
	{
		moveby = MoveBy::Create(1.2f, Vec2(0, tileheigh));
		repeate = Repeat::Create(player->up, 1.2f);
	}
	if (disr < 0)
	{
		moveby = MoveBy::Create(1.2f, Vec2(0, -tileheigh));
		repeate = Repeat::Create(player->down, 1.2f);
	}
	if (disc > 0)
	{

		moveby = MoveBy::Create(1.2f, Vec2(tilewidth, 0));
		repeate = Repeat::Create(player->right, 1.2f);
	}
	if (disc < 0)
	{
		moveby = MoveBy::Create(1.2f, Vec2(-tilewidth, 0));
		repeate = Repeat::Create(player->left, 1.2f);
	}

	action = Sequence::Create(Spawn::Create(moveby, repeate, nullptr), CallFunc::Create(CC_CALLBACK_0(Control::EndGo, this)), nullptr);
	action->Retain();
	player->RunAction(action);
}

//The current character starts moving 
//rowVector and colVector stores the path of the current character
//player points to the current character
void Control::StartGo(std::vector<int>pathRow,std::vector<int>pathCol,Player* player)
{
	nowcol = pathCol[0];
	nowrow = pathRow[0];
	row = col = 0;
	this->pathRow = pathRow;
	this->pathCol = pathCol;
	this->player = player;
	_step = 0;
	_stepcount = pathRow.size() - 1;
	if (_stepcount == 0)
	{
		endevent();
	}
	else
	{
		moveone(player);
	}
}

//Deal with the events when the character has finished moving and ended up in one specific tile
void Control::endGo()
{
	GameScene::GetStep_image()->at(_step)->setVisible(false);
	_step++;
	if (_step >= _stepcount)
	{
		float x = pathCol[_step] * tilewidth;
		float y = pathRow[_step] * tileheigh + tileheigh;
		Point mappoint = Ui::chang_GL_to_map(Vec2(x, y), GameScene::Getmap());
		int id = GameScene::Getmap()->LayerNamed("wenhao")->GetTileGIDAt(mappoint);
		int id1 = GameScene::Getmap()->LayerNamed("way")->GetTileGIDAt(mappoint);
		int ID = GameScene::Getmap()->propertiesForGID(id1).asValueMap()["location"].asInt();
		if (ID)
		{
			image = GameScene::Get_location_image()->at(ID - 1);
			image->setVisible(true);
			image->RunAction(Spawn::Create(FadeIn::Create(1.0f),FadeOut::Create(3.0f),NULL));
			
		}
		if (id == GameScene::Get_wenhao_id())
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
					  endevent();
			}; break;
			case 4:
			case 5:
			case 6:
			case 7:
			{
					  int number = random() % 9;
					  Wealth::GetInstance()->at(number)->RunAction(player);
					  endevent();
			}; break;
			case 8:
			{
					  player->GetLottery();
					  poplottery();
					  player->RunAction(Sequence::Create(DelayTime::Create(2.0f), CallFunc::Create([this]{
						  endevent();
					  }), NULL));
			}; break;
			}
			
		}
		else

		    endevent();
		return;
	}
	nowcol = col;
	nowrow = row;
	moveone(player);
}

//Lottery publish
void Control::poplottery()
{
	GameScene::Get_dialoglottery()->setVisible(true);
	GameScene::Get_dialoglottery()->AddPlayerLottery();
	GameScene::Get_dialoglottery()->runAnmi();
}


//Non-player characters Move
void Control::robotwalk()
{
	for (auto it = GameScene::GetPlayers()->Begin(); it != GameScene::GetPlayers()->End(); it++)
	{
		auto Player1 = dynamic_cast<Player*>(*it);

		if (Player1->Getturnme())
		{
			int randNumber = rand() % 6 + 1;
			Route::GetInstance()->GetPath(Player1,GameScene::isWalk, randNumber,GameScene::Getcol_count(),GameScene::Getrow_count());
			Player1->go(Route::GetInstance()->GetPathRow(), Route::GetInstance()->GetPathCol());
			return;
		}

	}
	GameScene::Get_go()->setPosition(GameScene::Get_go()->GetPosition() + Vec2(0, 500));
	GameScene::Get_go()->setVisible(true);
	oneRoundend = true;
	reSetPlayerGoTurn();
}

//The remaining characters initiation
void Control::reSetPlayerGoTurn()
{
	for (auto it = GameScene::GetPlayers()->Begin(); it != GameScene::GetPlayers()->End(); it++)
	{
		Player* richerPlayer = dynamic_cast<Player*>(*it);
		richerPlayer->SetTurnMe(true);

	}
}

void Control::endevent()
{
	oneRoundend = false;
	float x = pathCol[_step] * tilewidth;
	float y = pathRow[_step] * tileheigh + tileheigh;
	std::vector<Vec2>dir;
	dir.push_back(Vec2(x, y + tileheigh));
	dir.push_back(Vec2(x, y - tileheigh));
	dir.push_back(Vec2(x - tilewidth, y));
	dir.push_back(Vec2(x + tilewidth, y));
	int flag = 0;
	for (int i = 0; i < 4; i++)
	{
		Point mappoint = Ui::chang_GL_to_map(dir.at(i), GameScene::Getmap());
		int id = GameScene::GetLandLayer()->GetTileGIDAt(mappoint);
		GameScene::buy_land_x = mappoint.x;
		GameScene::buy_land_y = mappoint.y;
		if (id == GameScene::GetLand_id())
		{
			flag++;
			String* str = String::CreateWithFormat("%d-%f-%f-%d", 2, mappoint.x, mappoint.y,player->GetTag());
			NotificationCenter::GetInstance()->PostNotification("buy_land", str);
			break;
		}
		if (id == 3 + GameScene::GetLand_id())
		{
			if (player->GetTag() == 1)
			{
				flag++;
				String* str = String::CreateWithFormat("%d-%f-%f-%d", 3, mappoint.x, mappoint.y, player->GetTag());
				NotificationCenter::GetInstance()->PostNotification("buy_land", str);
				break;
			}
			else
			{
				flag++;
				String* str = String::CreateWithFormat("%d-%f-%f-%d", 6, mappoint.x, mappoint.y, player->GetTag());
				NotificationCenter::GetInstance()->PostNotification("pay_tolls", str);
				break;
			}
		}
		if (id == 1 + GameScene::GetLand_id())
		{
			flag++;
			if (player->GetTag() == 2)
			{
				String* str = String::CreateWithFormat("%d-%f-%f-%d", 3, mappoint.x, mappoint.y, player->GetTag());
				NotificationCenter::GetInstance()->PostNotification("buy_land", str);
				break;
			}
			else
			{
				String* str = String::CreateWithFormat("%d-%f-%f-%d", 6, mappoint.x, mappoint.y, player->GetTag());
				NotificationCenter::GetInstance()->PostNotification("pay_tolls", str);
				break;
			}
		}
		if (id == 2 + GameScene::GetLand_id())
		{
			flag++;
			if (player->GetTag() == 3)
			{
				String* str = String::CreateWithFormat("%d-%f-%f-%d", 3, mappoint.x, mappoint.y, player->GetTag());
				NotificationCenter::GetInstance()->PostNotification("buy_land", str);
				break;
			}
			else
			{
				String* str = String::CreateWithFormat("%d-%f-%f-%d", 6, mappoint.x, mappoint.y, player->GetTag());
				NotificationCenter::GetInstance()->PostNotification("pay_tolls", str);
				break;
			}
		}
		if (id == 10 + GameScene::GetLand_id())
		{
			flag++;
			if (player->GetTag() == 4)
			{
				String* str = String::CreateWithFormat("%d-%f-%f-%d", 3, mappoint.x, mappoint.y, player->GetTag());
				NotificationCenter::GetInstance()->PostNotification("buy_land", str);
				break;
			}
			else
			{
				String* str = String::CreateWithFormat("%d-%f-%f-%d", 6, mappoint.x, mappoint.y, player->GetTag());
				NotificationCenter::GetInstance()->PostNotification("pay_tolls", str);
				break;
			}
		}
		if (id == 6 + GameScene::GetLand_id())
		{
			flag++;
			if (player->GetTag() == 1)
			{
				String* str = String::CreateWithFormat("%d-%f-%f-%d", 4, mappoint.x, mappoint.y, player->GetTag());
				NotificationCenter::GetInstance()->PostNotification("buy_land", str);
				break;
			}
			else
			{
				String* str = String::CreateWithFormat("%d-%f-%f-%d", 7, mappoint.x, mappoint.y, player->GetTag());
				NotificationCenter::GetInstance()->PostNotification("pay_tolls", str);
				break;
			}
		}
		if (id == 4 + GameScene::GetLand_id())
		{
			flag++;
			if (player->GetTag() == 2)
			{
				String* str = String::CreateWithFormat("%d-%f-%f-%d", 4, mappoint.x, mappoint.y, player->GetTag());
				NotificationCenter::GetInstance()->PostNotification("buy_land", str);
				break;
			}
			else
			{
				String* str = String::CreateWithFormat("%d-%f-%f-%d", 7, mappoint.x, mappoint.y, player->GetTag());
				NotificationCenter::GetInstance()->PostNotification("pay_tolls", str);
				break;
			}
		}
		if (id == 5 + GameScene::GetLand_id())
		{
			flag++;
			if (player->GetTag() == 3)
			{
				String* str = String::CreateWithFormat("%d-%f-%f-%d", 4, mappoint.x, mappoint.y, player->GetTag());
				NotificationCenter::GetInstance()->PostNotification("buy_land", str);
				break;
			}
			else
			{
				String* str = String::CreateWithFormat("%d-%f-%f-%d", 7, mappoint.x, mappoint.y, player->GetTag());
				NotificationCenter::GetInstance()->PostNotification("pay_tolls", str);
				break;
			}
		}
		if (id == 11 + GameScene::GetLand_id())
		{
			flag++;
			if (player->GetTag() == 4)
			{
				String* str = String::CreateWithFormat("%d-%f-%f-%d", 4, mappoint.x, mappoint.y, player->GetTag());
				NotificationCenter::GetInstance()->PostNotification("buy_land", str);
				break;
			}
			else
			{
				String* str = String::CreateWithFormat("%d-%f-%f-%d", 7, mappoint.x, mappoint.y, player->GetTag());
				NotificationCenter::GetInstance()->PostNotification("pay_tolls", str);
				break;
			}
		}
		if (id == 9 + GameScene::GetLand_id())
		{
			flag++;
			if (player->GetTag() == 1)
			{
				String* str = String::CreateWithFormat("%d-%f-%f-%d", 1000, mappoint.x, mappoint.y, player->GetTag());
				NotificationCenter::GetInstance()->PostNotification("buy_land", str);
				break;
			}
			else
			{
				String* str = String::CreateWithFormat("%d-%f-%f-%d", 8, mappoint.x, mappoint.y, player->GetTag());
				NotificationCenter::GetInstance()->PostNotification("pay_tolls", str);
				break;
			}
		}
		if (id == 7 + GameScene::GetLand_id())
		{
			flag++;
			if (player->GetTag() == 2)
			{
				String* str = String::CreateWithFormat("%d-%f-%f-%d", 1000, mappoint.x, mappoint.y, player->GetTag());
				NotificationCenter::GetInstance()->PostNotification("buy_land", str);
				break;
			}
			else
			{
				String* str = String::CreateWithFormat("%d-%f-%f-%d", 8, mappoint.x, mappoint.y, player->GetTag());
				NotificationCenter::GetInstance()->PostNotification("pay_tolls", str);
				break;
			}
		}
		if (id == 8 + GameScene::GetLand_id())
		{
			flag++;
			if (player->GetTag() == 3)
			{
				String* str = String::CreateWithFormat("%d-%f-%f-%d", 1000, mappoint.x, mappoint.y, player->GetTag());
				NotificationCenter::GetInstance()->PostNotification("buy_land", str);
				break;
			}
			else
			{
				String* str = String::CreateWithFormat("%d-%f-%f-%d", 8, mappoint.x, mappoint.y, player->GetTag());
				NotificationCenter::GetInstance()->PostNotification("pay_tolls", str);
				break;
			}
		}
		if (id == 12 + GameScene::GetLand_id())
		{
			flag++;
			if (player->GetTag() == 4)
			{
				String* str = String::CreateWithFormat("%d-%f-%f-%d", 1000, mappoint.x, mappoint.y, player->GetTag());
				NotificationCenter::GetInstance()->PostNotification("buy_land", str);
				break;
			}
			else
			{
				String* str = String::CreateWithFormat("%d-%f-%f-%d", 8, mappoint.x, mappoint.y, player->GetTag());
				NotificationCenter::GetInstance()->PostNotification("pay_tolls", str);
				break;
			}
		}
	}
	if (!flag)
	{
		NotificationCenter::GetInstance()->PostNotification("one_go", String::CreateWithFormat("%d", 5));
	}
}




