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
	originX = x;
	originY = y;
	targetX = player->GetX() + player->GetWidth() / 2;
	targetY = player->GetY() + player->GetHeight() / 2;
	distanceX = (targetX - (x + width / 2));
	distanceY = (targetY - (y + height / 2));
	int r = static_cast<int>(sqrt(pow(distanceX, 2) + pow(distanceY, 2)));//x,y畫成直角三角形後的斜邊
	dx = static_cast<int>(static_cast<float>(distanceX) / r * moveSpeed);
	dy = static_cast<int>(static_cast<float>(distanceY) / r * moveSpeed);
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
	x += dx;//移動
	y += dy;//移動

	if (x + width < 0 || x >= Map::WORLD_SIZE_X || y + height < 0 || y >= Map::WORLD_SIZE_Y)//飛出邊界
		GameObject::Dead();//直接刪除

	else if (x + width > player->GetX() && x < player->GetX() + player->GetWidth()
		&& y + height > player->GetY() && y < player->GetY() + player->GetHeight())//打中玩家
	{
		Dead();//先攻擊玩家再刪除
	}
	else if (boss->GetPhase() == 2)//Boss目前在第二階段，有散射功能
	{
		if (/*(x + width > targetX && x < targetX
			&& y + height > targetY && y < targetY
			&& sqrt(pow(x - originX, 2) + pow(y - originY, 2)) >= sqrt(pow(SIZE_X, 2) + pow(SIZE_Y, 2)) / 4)
			//到達玩家原始位置，且移動的距離要超過螢幕斜邊的1/4
			||*/ 
			sqrt(pow(x - originX, 2) + pow(y - originY, 2)) >= sqrt(pow(SIZE_X, 2) + pow(SIZE_Y, 2)) / 2)
			//或者移動的距離超過螢幕斜邊的1/2，就散射子彈
		{
			//製造八顆子彈
			for (int i = 0; i < 8; i++)
			{
				GameSystem::AddGameObject(new BossBullet2("BossBullet", x, y, width, height, 30 + 45 * i));
			}

			GameObject::Dead();
		}
	}
	else if (boss->GetPhase() == 3)//Boss目前在第三階段，散射所需距離變短
	{
		if (sqrt(pow(x - originX, 2) + pow(y - originY, 2)) >= sqrt(pow(SIZE_X, 2) + pow(SIZE_Y, 2)) / 3)
			//或者移動的距離超過螢幕斜邊的1/3，就散射子彈
		{
			//製造八顆子彈
			for (int i = 0; i < 8; i++)
			{
				GameSystem::AddGameObject(new BossBullet2("BossBullet", x, y, width, height, 30 + 45 * i));
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

		string sPic = "";
		
		if (boss->GetPhase() == 1)//第一階段的圖
			sPic = ".\\res\\boss_bullet";
		else if (boss->GetPhase() == 2)//第二階段的圖
			sPic = ".\\res\\boss_bullet2";
		else if (boss->GetPhase() == 3)//第三階段的圖(跟二階一樣)
			sPic = ".\\res\\boss_bullet2";

		sPic += "_" + to_string(i) + ".bmp";

		//轉成c-string
		char* cPic = new char[sPic.length() + 1];
		strcpy(cPic, sPic.c_str());

		ani->AddBitmap(cPic, RGB(255, 255, 255));//加入圖片
		delete cPic;//delete new
	}
}
