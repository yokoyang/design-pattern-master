#include"control.h"
#include"GameSceneScene.h"
#include"route.h"
#include"Ui.h"
#include"Duang.h"


control* control::control_Instance = NULL;

control::control()
{
	comex = -1;
	comey = -1;
	struct timeval now;
	gettimeofday(&now, NULL);
	unsigned rand_seed = (unsigned)(now.tv_sec * 1000 + now.tv_usec / 1000);
	srand(rand_seed);
}

bool control::init()
{
	if (!Layer::init())
		return false;

	res_notification_Observe();
	oneroundend = false;
	return true;
}
//Add a registry in order to call some certain functions
void control::res_notification_Observe()
{
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(control::receivemsg), "one_go", NULL);
}
//Registry Callback
void control::receivemsg(Object* node)
{
	int res = ((String*)node)->intValue();
	if (res == 5)
	{
		robotwalk();
	}
}

control* control::getInstance()
{
	if (!control_Instance)
	{
		control_Instance = new control();
		control_Instance->init();
	}

	return control_Instance;
}

control::~control()
{
	control_Instance = NULL;
}
//Move the character one step ahead
void control::moveone(player* Player)
{
	row = pathrow[_step + 1];
	col = pathcol[_step + 1];
	int disr = row - nowrow;
	int disc = col - nowcol;
	MoveBy* moveby;
	Repeat* repeate;
	Action* action;
	if (disr > 0)
	{
		moveby = MoveBy::create(1.2f, Vec2(0, tileheigh));
		repeate = Repeat::create(Player->up, 1.2f);
	}
	if (disr < 0)
	{
		moveby = MoveBy::create(1.2f, Vec2(0, -tileheigh));
		repeate = Repeat::create(Player->down, 1.2f);
	}
	if (disc > 0)
	{

		moveby = MoveBy::create(1.2f, Vec2(tilewidth, 0));
		repeate = Repeat::create(Player->right, 1.2f);
	}
	if (disc < 0)
	{
		moveby = MoveBy::create(1.2f, Vec2(-tilewidth, 0));
		repeate = Repeat::create(Player->left, 1.2f);
	}

	action = Sequence::create(Spawn::create(moveby, repeate, nullptr), CallFunc::create(CC_CALLBACK_0(control::endGo, this)), nullptr);
	action->retain();
	Player->runAction(action);
}

//The current character starts moving 
//rowVector and colVector stores the path of the current character
//Player points to the current character
void control::startgo(std::vector<int>pathrow,std::vector<int>pathcol,player* Player)
{
	nowcol = pathcol[0];
	nowrow = pathrow[0];
	row = col = 0;
	this->pathrow = pathrow;
	this->pathcol = pathcol;
	this->Player = Player;
	_step = 0;
	_stepcount = pathrow.size() - 1;
	if (_stepcount == 0)
	{
		endevent();
	}
	else
	{
		moveone(Player);
	}
}

//Deal with the events when the character has finished moving and ended up in one specific tile
void control::endGo()
{
	GameScene::getstep_image()->at(_step)->setVisible(false);
	_step++;
	if (_step >= _stepcount)
	{
		float x = pathcol[_step] * tilewidth;
		float y = pathrow[_step] * tileheigh + tileheigh;
		Point mappoint = Ui::chang_GL_to_map(Vec2(x, y), GameScene::getmap());
		int id = GameScene::getmap()->layerNamed("wenhao")->getTileGIDAt(mappoint);
		int id1 = GameScene::getmap()->layerNamed("way")->getTileGIDAt(mappoint);
		int ID = GameScene::getmap()->propertiesForGID(id1).asValueMap()["location"].asInt();
		if (ID)
		{
			image = GameScene::get_location_image()->at(ID - 1);
			image->setVisible(true);
			image->runAction(Spawn::create(FadeIn::create(1.0f),FadeOut::create(3.0f),NULL));
			
		}
		if (id == GameScene::get_wenhao_id())
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
					  Forwards::getInstance()->at(number)->RunAction(Player);
			}; break;
			case 2:
			case 3:
			{
					  int number = random() % 7;
					  Delay::getInstance()->at(number)->RunAction(Player);
					  endevent();
			}; break;
			case 4:
			case 5:
			case 6:
			case 7:
			{
					  int number = random() % 9;
					  Wealth::getInstance()->at(number)->RunAction(Player);
					  endevent();
			}; break;
			case 8:
			{
					  Player->getLottery();
					  poplottery();
					  Player->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create([this]{
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
	moveone(Player);
}

//Lottery publish
void control::poplottery()
{
	GameScene::get_dialoglottery()->setVisible(true);
	GameScene::get_dialoglottery()->addplayerlottery();
	GameScene::get_dialoglottery()->runanmi();
}


//Non-player characters Move
void control::robotwalk()
{
	for (auto it = GameScene::getplayers()->begin(); it != GameScene::getplayers()->end(); it++)
	{
		auto Player1 = dynamic_cast<player*>(*it);

		if (Player1->getturnme())
		{
			int randNumber = rand() % 6 + 1;
			route::getInstance()->getpath(Player1,GameScene::iswalk, randNumber,GameScene::getcol_count(),GameScene::getrow_count());
			Player1->go(route::getInstance()->getpathrow(), route::getInstance()->getpathcol());
			return;
		}

	}
	GameScene::get_go()->setPosition(GameScene::get_go()->getPosition() + Vec2(0, 500));
	GameScene::get_go()->setVisible(true);
	oneroundend = true;
	resetPlayerGoTurn();
}

//The remaining characters initiation
void control::resetPlayerGoTurn()
{
	for (auto it = GameScene::getplayers()->begin(); it != GameScene::getplayers()->end(); it++)
	{
		player* richerPlayer = dynamic_cast<player*>(*it);
		richerPlayer->setturnme(true);

	}
}

void control::endevent()
{
	oneroundend = false;
	float x = pathcol[_step] * tilewidth;
	float y = pathrow[_step] * tileheigh + tileheigh;
	std::vector<Vec2>dir;
	dir.push_back(Vec2(x, y + tileheigh));
	dir.push_back(Vec2(x, y - tileheigh));
	dir.push_back(Vec2(x - tilewidth, y));
	dir.push_back(Vec2(x + tilewidth, y));
	int flag = 0;
	for (int i = 0; i < 4; i++)
	{
		Point mappoint = Ui::chang_GL_to_map(dir.at(i), GameScene::getmap());
		int id = GameScene::getlandlayer()->getTileGIDAt(mappoint);
		GameScene::buy_land_x = mappoint.x;
		GameScene::buy_land_y = mappoint.y;
		if (id == GameScene::getland_id())
		{
			flag++;
			String* str = String::createWithFormat("%d-%f-%f-%d", 2, mappoint.x, mappoint.y,Player->getTag());
			NotificationCenter::getInstance()->postNotification("buy_land", str);
			break;
		}
		if (id == 3 + GameScene::getland_id())
		{
			if (Player->getTag() == 1)
			{
				flag++;
				String* str = String::createWithFormat("%d-%f-%f-%d", 3, mappoint.x, mappoint.y, Player->getTag());
				NotificationCenter::getInstance()->postNotification("buy_land", str);
				break;
			}
			else
			{
				flag++;
				String* str = String::createWithFormat("%d-%f-%f-%d", 6, mappoint.x, mappoint.y, Player->getTag());
				NotificationCenter::getInstance()->postNotification("pay_tolls", str);
				break;
			}
		}
		if (id == 1 + GameScene::getland_id())
		{
			flag++;
			if (Player->getTag() == 2)
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", 3, mappoint.x, mappoint.y, Player->getTag());
				NotificationCenter::getInstance()->postNotification("buy_land", str);
				break;
			}
			else
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", 6, mappoint.x, mappoint.y, Player->getTag());
				NotificationCenter::getInstance()->postNotification("pay_tolls", str);
				break;
			}
		}
		if (id == 2 + GameScene::getland_id())
		{
			flag++;
			if (Player->getTag() == 3)
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", 3, mappoint.x, mappoint.y, Player->getTag());
				NotificationCenter::getInstance()->postNotification("buy_land", str);
				break;
			}
			else
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", 6, mappoint.x, mappoint.y, Player->getTag());
				NotificationCenter::getInstance()->postNotification("pay_tolls", str);
				break;
			}
		}
		if (id == 10 + GameScene::getland_id())
		{
			flag++;
			if (Player->getTag() == 4)
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", 3, mappoint.x, mappoint.y, Player->getTag());
				NotificationCenter::getInstance()->postNotification("buy_land", str);
				break;
			}
			else
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", 6, mappoint.x, mappoint.y, Player->getTag());
				NotificationCenter::getInstance()->postNotification("pay_tolls", str);
				break;
			}
		}
		if (id == 6 + GameScene::getland_id())
		{
			flag++;
			if (Player->getTag() == 1)
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", 4, mappoint.x, mappoint.y, Player->getTag());
				NotificationCenter::getInstance()->postNotification("buy_land", str);
				break;
			}
			else
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", 7, mappoint.x, mappoint.y, Player->getTag());
				NotificationCenter::getInstance()->postNotification("pay_tolls", str);
				break;
			}
		}
		if (id == 4 + GameScene::getland_id())
		{
			flag++;
			if (Player->getTag() == 2)
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", 4, mappoint.x, mappoint.y, Player->getTag());
				NotificationCenter::getInstance()->postNotification("buy_land", str);
				break;
			}
			else
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", 7, mappoint.x, mappoint.y, Player->getTag());
				NotificationCenter::getInstance()->postNotification("pay_tolls", str);
				break;
			}
		}
		if (id == 5 + GameScene::getland_id())
		{
			flag++;
			if (Player->getTag() == 3)
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", 4, mappoint.x, mappoint.y, Player->getTag());
				NotificationCenter::getInstance()->postNotification("buy_land", str);
				break;
			}
			else
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", 7, mappoint.x, mappoint.y, Player->getTag());
				NotificationCenter::getInstance()->postNotification("pay_tolls", str);
				break;
			}
		}
		if (id == 11 + GameScene::getland_id())
		{
			flag++;
			if (Player->getTag() == 4)
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", 4, mappoint.x, mappoint.y, Player->getTag());
				NotificationCenter::getInstance()->postNotification("buy_land", str);
				break;
			}
			else
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", 7, mappoint.x, mappoint.y, Player->getTag());
				NotificationCenter::getInstance()->postNotification("pay_tolls", str);
				break;
			}
		}
		if (id == 9 + GameScene::getland_id())
		{
			flag++;
			if (Player->getTag() == 1)
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", 1000, mappoint.x, mappoint.y, Player->getTag());
				NotificationCenter::getInstance()->postNotification("buy_land", str);
				break;
			}
			else
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", 8, mappoint.x, mappoint.y, Player->getTag());
				NotificationCenter::getInstance()->postNotification("pay_tolls", str);
				break;
			}
		}
		if (id == 7 + GameScene::getland_id())
		{
			flag++;
			if (Player->getTag() == 2)
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", 1000, mappoint.x, mappoint.y, Player->getTag());
				NotificationCenter::getInstance()->postNotification("buy_land", str);
				break;
			}
			else
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", 8, mappoint.x, mappoint.y, Player->getTag());
				NotificationCenter::getInstance()->postNotification("pay_tolls", str);
				break;
			}
		}
		if (id == 8 + GameScene::getland_id())
		{
			flag++;
			if (Player->getTag() == 3)
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", 1000, mappoint.x, mappoint.y, Player->getTag());
				NotificationCenter::getInstance()->postNotification("buy_land", str);
				break;
			}
			else
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", 8, mappoint.x, mappoint.y, Player->getTag());
				NotificationCenter::getInstance()->postNotification("pay_tolls", str);
				break;
			}
		}
		if (id == 12 + GameScene::getland_id())
		{
			flag++;
			if (Player->getTag() == 4)
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", 1000, mappoint.x, mappoint.y, Player->getTag());
				NotificationCenter::getInstance()->postNotification("buy_land", str);
				break;
			}
			else
			{
				String* str = String::createWithFormat("%d-%f-%f-%d", 8, mappoint.x, mappoint.y, Player->getTag());
				NotificationCenter::getInstance()->postNotification("pay_tolls", str);
				break;
			}
		}
	}
	if (!flag)
	{
		NotificationCenter::getInstance()->postNotification("one_go", String::createWithFormat("%d", 5));
	}
}




