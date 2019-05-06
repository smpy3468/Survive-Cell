#include "StdAfx.h"

#include "gamelib.h"
using namespace game_framework;
#include "GameSystem.h"
#include "Map.h"

CMovingBitmap Map::startMenu;//�}�l���
CMovingBitmap Map::backgroundPic;//�I���Ϥ�
bool Map::coordinate[WORLD_SIZE_X][WORLD_SIZE_Y] = { false };//�������Ӯy�Ц�����
int Map::sx = 0;//�w�]�ù����W���b�a�Ϯy�Ъ�0,0 
int Map::sy = 0;//�w�]�ù����W���b�a�Ϯy�Ъ�0,0 

Map::~Map()
{
}

void Map::Init()
{
	for (int i = 0; i < WORLD_SIZE_X; i++)
	{
		for (int j = 0; j < WORLD_SIZE_Y; j++)
		{
			coordinate[i][j] = false;
		}
	}
}

void Map::Load()
{
	startMenu.LoadBitmap(".\\res\\start_menu.bmp");
	backgroundPic.LoadBitmap(IDB_BACKGROUND);
}

void Map::ShowStartMenu()
{
	startMenu.SetTopLeft(0, 0);
	startMenu.ShowBitmap();
}

void Map::ShowBackgroundPic()
{
	backgroundPic.SetTopLeft(-sx, -sy);
	backgroundPic.ShowBitmap();
}

void Map::SetSX(int x)
{
	if (x < 0)//�T�O�ù��b�C���e����
		x = 0;
	if (x + SIZE_X >= WORLD_SIZE_X)//�T�O�ù��b�C���e����
		x = WORLD_SIZE_X - SIZE_X - 1;

	sx = x;
}

void Map::SetSY(int y)
{
	if (y < 0)//�T�O�ù��b�C���e����
		y = 0;
	if (y + SIZE_Y >= WORLD_SIZE_Y)//�T�O�ù��b�C���e����
		y = WORLD_SIZE_Y - SIZE_Y - 1;

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
					if (x >= 0 && x < Map::WORLD_SIZE_X && y >= 0 && y < Map::WORLD_SIZE_Y)//�b�a�Ͻd�򤺤~����
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