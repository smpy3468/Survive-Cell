#include "StdAfx.h"
#include "Door.h"
#include "GameSystem.h"

Door::Door() :GameObject()
{
	tag = "Door";
}

Door::Door(string tag, int x, int y, int width, int height) : GameObject(tag, x, y, width, height)
{
	isRuin = false;
	ani = new CAnimation();
	layer = GameSystem::LAYER::LAYER_DOOR;
	LoadAni();
}

void Door::Kicked()
{
	isRuin = true;
}

void Door::SetBitMapPosition()
{
	ani->SetTopLeft(x - Map::GetSX(), y - Map::GetSY());
}

void Door::Dead()
{
	//�����Ǫ�

	GameSystem::DeleteGameObject(this);//�R������
}

void Door::ShowBitMap()
{
	if (isRuin)//�Q�}�a����
		ani->OnMove();//����}�a�ʵe
	ani->OnShow();

	if (ani->IsEnd())//�����}�a�ʵe��
		Dead();//�R������
}

void Door::LoadAni()
{
	char* pic = ".\\res\\door.bmp";
	ani->AddBitmap(pic);
}