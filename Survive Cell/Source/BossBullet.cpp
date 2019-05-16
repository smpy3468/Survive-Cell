#include "StdAfx.h"
#include "BossBullet.h"
#include "GameSystem.h"
#include "BossBullet2.h"
#include <math.h>

BossBullet::BossBullet()
{
}

BossBullet::BossBullet(string tag, int x, int y, int width, int height) :GameObject(tag, x, y, width, height)
{
	layer = GameSystem::LAYER_MONSTER;
	ani = new CAnimation(5);
	LoadAni();

	moveSpeed = 10;
	attackDamage = 50;

	Player* player = GameSystem::GetGameObjectWithType<Player>();
	targetX = player->GetX() + player->GetWidth() / 2;
	targetY = player->GetY() + player->GetHeight() / 2;
	distanceX = (targetX - (x + width / 2));
	distanceY = (targetY - (y + height / 2));
}

BossBullet::~BossBullet()
{
	delete ani;
}

void BossBullet::Dead()
{
	player->DecreaseHP(attackDamage);
	GameObject::Dead();
}

void BossBullet::Act()
{
	int r = static_cast<int>(sqrt(pow(distanceX, 2) + pow(distanceY, 2)));//x,y畫成直角三角形後的斜邊

	x += static_cast<int>(static_cast<float>(distanceX) / r * moveSpeed);
	y += static_cast<int>(static_cast<float>(distanceY) / r * moveSpeed);

	if (x + width < 0 || x >= Map::WORLD_SIZE_X || y + height < 0 || y >= Map::WORLD_SIZE_Y)//飛出邊界
		GameObject::Dead();//直接刪除

	else if (x + width > player->GetX() && x < player->GetX() + player->GetWidth()
		&& y + height > player->GetY() && y < player->GetY() + player->GetHeight())//打中玩家
	{
		Dead();//先攻擊玩家再刪除
	}

	if (x + width > targetX && x < targetX
		&& y + height > targetY && y < targetY)
	{
		if (boss->GetPhase() == 2)//Boss目前在第二階段
		{
			//製造八顆子彈
			for (int i = 0; i < 8; i++)
			{
				GameSystem::AddGameObject(new BossBullet2("BossBullet", x, y, width, height, 15 + 45 * i));
			}

			GameObject::Dead();
		}
	}
}

void BossBullet::SetBitMapPosition()
{
	ani->SetTopLeft(x - Map::GetSX(), y - Map::GetSY());
}

void BossBullet::ShowBitMap()
{
	ani->OnMove();
	ani->OnShow();
}

void BossBullet::LoadAni()
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
