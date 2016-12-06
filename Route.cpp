#include"Route.h"
#include"GameSceneScene.h"

Route* Route::route = 0;

Route::Route()
{
	comeX = -1;
	comeY = -1;
	struct timeval now;
	GetTimeOfDay(&now, NULL);
	unsigned rand_seed = (unsigned)(now.tv_sec * 1000 + now.tv_usec / 1000); 
	srand(rand_seed);
}

Route::~Route()
{
	route = NULL;
}
//Returns the single instance
Route* Route::GetInstance()
{
	if (route == NULL)
		route = new Route();
	return route;
}

void Route::SettileSize(float tilewidth, float tileheigh)
{
	this->tilewidth = tilewidth;
	this->tileheigh = tileheigh;
}
//Acquire the path the players are to take 
void Route::GetPath(Player* playername, bool** isWalk, int step, int colCount, int rowCount)
{
	pathRow.Clear();
	pathCol.Clear();
	int now_positionx, now_positiony;
	int next_positionx, next_positiony;
	Point p = playername->GetPosition();
	p.y = p.y - tileheigh;
	now_positionx = p.x / tilewidth;
	now_positiony = p.y / tileheigh;
	next_positionx = next_positiony = 0;
	pathRow.push_back(now_positiony);
	pathCol.push_back(now_positionx);
	bool** pass = new bool*[rowCount];
	for (int i = 0; i < rowCount; i++)
	{
		pass[i] = new bool[colCount];
	}
	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < colCount; j++)
		{
			pass[i][j] = isWalk[i][j];
		}
	}
	comeX = playername->GetComeX();
	comeY = playername->GetComeY();
	if (comeX <= -1 && comeY <= -1)
	{
		comeX = now_positionx;
		comeY = now_positiony;
		playername->SetComeX(comeX);
		playername->SetComeY(comeY);
	}
	pass[comeY][comeX] = false;
	std::vector<int>dir;
	for (int stepNumber = 0; stepNumber < step; stepNumber++)
	{
		dir.Clear();
		//0代表上，1代表下，2代表左，3代表右
		if (IsCanGo(now_positionx, now_positiony, 0, pass))
		{
			dir.push_back(0);
		}
		if (IsCanGo(now_positionx, now_positiony, 1, pass))
		{
			dir.push_back(1);
		}
		if (IsCanGo(now_positionx, now_positiony, 2, pass))
		{
			dir.push_back(2);
		}
		if (IsCanGo(now_positionx, now_positiony, 3, pass))
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
		pathRow.push_back(next_positiony);
		pathCol.push_back(next_positionx);
		pass[now_positiony][now_positionx] = false;
		now_positionx = next_positionx;
		now_positiony = next_positiony;
	}
	comeX = pathCol[pathCol.size() - 2];
	comeY = pathRow[pathRow.size() - 2];
	if (playername->Get_stayRounds() != 0)
	{
	}
	else
	{
		playername->SetComeX(comeX);
		playername->SetComeY(comeY);
	}
	dir.Clear();
	CC_SAFE_DELETE(pass);
}


//Decide which of the four directions are accessible
bool Route::IsCanGo(int x, int y, int dir, bool** pass)
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