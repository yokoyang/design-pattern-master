#include"route.h"
#include"GameSceneScene.h"

route* route::Route = 0;

route::route()
{
	comex = -1;
	comey = -1;
	struct timeval now;
	gettimeofday(&now, NULL);
	unsigned rand_seed = (unsigned)(now.tv_sec * 1000 + now.tv_usec / 1000); 
	srand(rand_seed);
}

route::~route()
{
	Route = NULL;
}
//Returns the single instance
route* route::getInstance()
{
	if (Route == NULL)
		Route = new route();
	return Route;
}

void route::settilesize(float tilewidth, float tileheigh)
{
	this->tilewidth = tilewidth;
	this->tileheigh = tileheigh;
}
//Acquire the path the players are to take 
void route::getpath(player* playername, bool** iswalk, int step, int colcount, int rowcount)
{
	pathrow.clear();
	pathcol.clear();
	int now_positionx, now_positiony;
	int next_positionx, next_positiony;
	Point p = playername->getPosition();
	p.y = p.y - tileheigh;
	now_positionx = p.x / tilewidth;
	now_positiony = p.y / tileheigh;
	next_positionx = next_positiony = 0;
	pathrow.push_back(now_positiony);
	pathcol.push_back(now_positionx);
	bool** pass = new bool*[rowcount];
	for (int i = 0; i < rowcount; i++)
	{
		pass[i] = new bool[colcount];
	}
	for (int i = 0; i < rowcount; i++)
	{
		for (int j = 0; j < colcount; j++)
		{
			pass[i][j] = iswalk[i][j];
		}
	}
	comex = playername->getcomex();
	comey = playername->getcomey();
	if (comex <= -1 && comey <= -1)
	{
		comex = now_positionx;
		comey = now_positiony;
		playername->setcomex(comex);
		playername->setcomey(comey);
	}
	pass[comey][comex] = false;
	std::vector<int>dir;
	for (int stepnumber = 0; stepnumber < step; stepnumber++)
	{
		dir.clear();
		//0代表上，1代表下，2代表左，3代表右
		if (iscango(now_positionx, now_positiony, 0, pass))
		{
			dir.push_back(0);
		}
		if (iscango(now_positionx, now_positiony, 1, pass))
		{
			dir.push_back(1);
		}
		if (iscango(now_positionx, now_positiony, 2, pass))
		{
			dir.push_back(2);
		}
		if (iscango(now_positionx, now_positiony, 3, pass))
		{
			dir.push_back(3);
		}
		if (dir.size() == 0)return;
		int i = rand() % dir.size();
		switch (dir[i])
		{
		case 0:
		{
				  next_positionx = now_positionx;
				  next_positiony = now_positiony + 1;
				  break;
		}
		case 1:
		{
				  next_positionx = now_positionx;
				  next_positiony = now_positiony - 1;
				  break;
		}
		case 2:
		{
				  next_positionx = now_positionx - 1;
				  next_positiony = now_positiony;
				  break;
		}
		case 3:
		{
				  next_positionx = now_positionx + 1;
				  next_positiony = now_positiony;
				  break;
		}
		default:
			break;
		}
		pathrow.push_back(next_positiony);
		pathcol.push_back(next_positionx);
		pass[now_positiony][now_positionx] = false;
		now_positionx = next_positionx;
		now_positiony = next_positiony;
	}
	comex = pathcol[pathcol.size() - 2];
	comey = pathrow[pathrow.size() - 2];
	if (playername->get_stayRounds() != 0)
	{
	}
	else
	{
		playername->setcomex(comex);
		playername->setcomey(comey);
	}
	dir.clear();
	CC_SAFE_DELETE(pass);
}


//Decide which of the four directions are accessible
bool route::iscango(int x, int y, int dir, bool** pass)
{
	switch (dir)
	{
	case 0:
	{
			  return pass[y + 1][x];
			  break;
	}
	case 1:
	{
			  return pass[y - 1][x];
			  break;
	}
	case 2:
	{
			  return pass[y][x - 1];
			  break;
	}
	case 3:
	{
			  return pass[y][x + 1];
			  break;
	}
	}
	return false;
}