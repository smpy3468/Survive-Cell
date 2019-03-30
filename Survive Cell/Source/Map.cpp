#include "StdAfx.h"

#include "gamelib.h"
using namespace game_framework;
#include "GameSystem.h"
#include "Map.h"

CMovingBitmap Map::backgroundPic;//�I���Ϥ�
bool Map::coordinate[WORLD_SIZE_X][WORLD_SIZE_Y] = { false };//�������Ӯy�Ц�����
int Map::sx = 0;//�w�]�ù����W���b�a�Ϯy�Ъ�0,0 
int Map::sy = 0;//�w�]�ù����W���b�a�Ϯy�Ъ�0,0 

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
	if(x >= 0 && x + SIZE_X < WORLD_SIZE_X)//�T�O�ù��b�C���e����
		sx = x;
	else
	{

	}
}

void Map::SetSY(int y)
{
	if (y >= 0 && y + SIZE_Y < WORLD_SIZE_Y)//�T�O�ù��b�C���e����
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

void Map::SetStaticObject()//�]�w���|���ʪ�����y�СA�u�|�b�C���@�}�l�I�s
{
	for (auto& i : GameSystem::GetAllGameObject())
	{
		if (i->GetTag() == "Floor")//���O���|�ʪ�����
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