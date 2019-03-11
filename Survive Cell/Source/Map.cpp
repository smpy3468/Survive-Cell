#include "StdAfx.h"

#include "gamelib.h"
#include "GameSystem.h"
#include "Map.h"

bool Map::coordinate[SIZE_X][SIZE_Y] = { false };//紀錄哪個座標有物件

void Map::SetStaticObject()//設定不會移動的物件座標，只會在遊戲一開始呼叫
{
	for (auto i = GameSystem::GetAllGameObject().begin(); i != GameSystem::GetAllGameObject().end(); i++)
	{
		for (int x = i->GetX(); x != i->GetX() + i->GetWidth(); x++)
		{
			for (int y = i->GetY(); y != i->GetY() + i->GetHeight(); y++)
			{
				coordinate[x][y] = true;//物件的長寬範圍以內的座標都設為true
			}
		}
	}
}

void Map::SetDynamicObject()//設定會移動的物件座標(玩家、怪物)
{

}

bool Map::HasObject(int x, int y)//該座標是否有物件
{
	return coordinate[x][y];//回傳該座標是否有物件
}
