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

	player.IncreaseHP(recoverHP);//���a�^��

	Dead();
}

void Potion::Dead()
{
	GameSystem::DeleteGameObject(this);//�R��������
}
