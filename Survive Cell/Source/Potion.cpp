#include "StdAfx.h"
#include "Potion.h"

Potion::Potion()
{
	tag = "Potion";
}

Potion::~Potion()
{

}

Potion::Potion(string tag, int x, int y, int width, int height) :Item(tag, x, y, width, height)
{	
	recoverHP = 10;
	ani[0]->AddBitmap(".\\res\\potion.bmp");
	//LoadBitMap(".\\res\\cell_green.bmp");
}

void Potion::Picked()
{
	Player& player = *(GameSystem::GetGameObjectWithTag<Player>("Player"));

	player.IncreaseHP(recoverHP);//玩家回血

	Dead();
}

void Potion::Dead()
{
	GameSystem::DeleteGameObject(this);//刪除此物件
}
