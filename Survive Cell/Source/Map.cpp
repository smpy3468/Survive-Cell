#include "StdAfx.h"

#include "gamelib.h"
using namespace game_framework;
#include "GameSystem.h"
#include "Map.h"

CMovingBitmap Map::backgroundPic;//背景圖片
bool Map::coordinate[WORLD_SIZE_X][WORLD_SIZE_Y] = { false };//紀錄哪個座標有物件
int Map::sx = 0;//預設螢幕左上角在地圖座標的0,0 
int Map::sy = 0;//預設螢幕左上角在地圖座標的0,0 

void Map::LoadBackgroundPic()
{
	backgroundPic.LoadBitmap(IDB_BACKGROUND);
}

void Map::ShowBackgroundPic()
{
	backgroundPic.SetTopLeft(-sx, -sy);
	backgroundPic.ShowBitmap();
}

void Map::SetSX(int x)
{
	if(x >= 0 && x + SIZE_X < WORLD_SIZE_X)//確保螢幕在遊戲畫面中
		sx = x;
	else
	{

	}
}

void Map::SetSY(int y)
{
	if (y >= 0 && y + SIZE_Y < WORLD_SIZE_Y)//確保螢幕在遊戲畫面中
		sy = y;
}

int Map::GetSX()
{
	return sx;
}

int Map::GetSY()
{
	return sy;
}

void Map::MoveScreenTopLeft(int dx, int dy)
{
	Map::SetSX(Map::GetSX() + dx);
	Map::SetSY(Map::GetSY() + dy);
}

void Map::SetStaticObject()//設定不會移動的物件座標，只會在遊戲一開始呼叫
{
	for (auto& i : GameSystem::GetAllGameObject())
	{
		if (i->GetTag() == "Floor")//不記錄會動的物件
		{
			for (int x = i->GetX(); x < i->GetX() + i->GetWidth(); x++)
			{
				for (int y = i->GetY(); y < i->GetY() + i->GetHeight(); y++)
				{
					coordinate[x][y] = true;//物件的長寬範圍以內的座標都設為true
				}
			}
		}
	}
}

bool Map::HasObject(int x, int y)//該座標是否有物件
{
	return coordinate[x][y];//回傳該座標是否有物件
}