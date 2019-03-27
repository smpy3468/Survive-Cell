#include "StdAfx.h"
#include "Potion.h"

Potion::Potion()
{
	tag = "Potion";
}

Potion::Potion(string tag, int x, int y, int width, int height, int pictureID) :Item(tag, x, y, width, height, pictureID)
{
	recoverHP = 10;
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
