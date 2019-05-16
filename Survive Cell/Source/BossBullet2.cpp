#include "StdAfx.h"
#include "BossBullet2.h"
#include "GameSystem.h"
#include <math.h>

#define M_PI   3.14159265358979323846264338327950288

BossBullet2::BossBullet2()
{
	
}

BossBullet2::BossBullet2(string tag, int x, int y, int width, int height,double angle) :GameObject(tag, x, y, width, height)
{
	layer = GameSystem::LAYER_MONSTER;
	ani = new CAnimation(5);
	LoadAni();

	moveSpeed = 10;
	attackDamage = 10;

	Player* player = GameSystem::GetGameObjectWithType<Player>();

	normalX = cos(angle * M_PI / 180.0);
	normalY = sin(angle * M_PI / 180.0);
}

BossBullet2::~BossBullet2()
{
	delete ani;
}

void BossBullet2::Dead()
{
	player->DecreaseHP(attackDamage);
	GameObject::Dead();
}

void BossBullet2::Act()
{
	x += static_cast<int>(normalX * moveSpeed);
	y += static_cast<int>(normalY * moveSpeed);

	if (x + width < 0 || x >= Map::WORLD_SIZE_X || y + height < 0 || y >= Map::WORLD_SIZE_Y)//飛出邊界
		GameObject::Dead();//直接刪除

	else if (x + width > player->GetX() && x < player->GetX() + player->GetWidth()
		&& y + height > player->GetY() && y < player->GetY() + player->GetHeight())//打中玩家
	{
		Dead();//先攻擊玩家再刪除
	}
}

void BossBullet2::SetBitMapPosition()
{
	ani->SetTopLeft(x - Map::GetSX(), y - Map::GetSY());
}

void BossBullet2::ShowBitMap()
{
	ani->OnMove();
	ani->OnShow();
}

void BossBullet2::LoadAni()
{
	for (int i = 0; i < 8; i++)
	{
		//將檔名串接底線+編號+副檔名
		string sPic = ".\\res\\boss_bullet";
		sPic += "_" + to_string(i) + ".bmp";

		//轉成c-string
		char* cPic = new char[sPic.length() + 1];
		strcpy(cPic, sPic.c_str());

		ani->AddBitmap(cPic, RGB(255, 255, 255));//加入圖片
		delete cPic;//delete new
	}
}
