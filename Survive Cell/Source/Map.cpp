#include "StdAfx.h"

#include "gamelib.h"
using namespace game_framework;
#include "GameSystem.h"
#include "Map.h"

CMovingBitmap Map::backgroundPic;//�I���Ϥ�
bool Map::coordinate[SIZE_X][SIZE_Y] = { false };//�������Ӯy�Ц�����
int Map::sx = 0;//�w�]�ù����W���b�a�Ϯy�Ъ�0,0 
int Map::sy = 0;//�w�]�ù����W���b�a�Ϯy�Ъ�0,0 

void Map::SetSX(int x)
{
	sx = x;
}

void Map::SetSY(int y)
{
	sy = y;
}

void Map::LoadBackgroundPic()
{
	backgroundPic.LoadBitmap(IDB_BACKGROUND);
}

void Map::ShowBackgroundPic()
{
	backgroundPic.SetTopLeft(-sx, -sy);
	backgroundPic.ShowBitmap();
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

void Map::SetStaticObject()//�]�w���|���ʪ�����y�СA�u�|�b�C���@�}�l�I�s
{
	for (auto& i : GameSystem::GetAllGameObject())
	{
		if (!(i->GetTag() == "Player" || i->GetTag() == "Monster"))//���O���|�ʪ�����
		{
			for (int x = i->GetX(); x < i->GetX() + i->GetWidth(); x++)
			{
				for (int y = i->GetY(); y < i->GetY() + i->GetHeight(); y++)
				{
					coordinate[x][y] = true;//���󪺪��e�d��H�����y�г��]��true
				}
			}
		}
	}
}

bool Map::HasObject(int x, int y)//�Ӯy�ЬO�_������
{
	return coordinate[x][y];//�^�ǸӮy�ЬO�_������
}