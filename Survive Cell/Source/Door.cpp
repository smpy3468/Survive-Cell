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
	//攻擊怪物

	GameSystem::DeleteGameObject(this);//刪除物件
}

void Door::ShowBitMap()
{
	if (isRuin)//被破壞的話
		ani->OnMove();//播放破壞動畫
	ani->OnShow();

	if (ani->IsEnd())//播完破壞動畫後
		Dead();//刪除物件
}

void Door::LoadAni()
{
	char* pic = ".\\res\\door.bmp";
	ani->AddBitmap(pic);
}