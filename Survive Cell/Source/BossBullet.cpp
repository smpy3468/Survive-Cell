#include "StdAfx.h"
#include "BossBullet.h"
#include "GameSystem.h"
#include "Player.h"

BossBullet::BossBullet()
{
}

BossBullet::BossBullet(string tag, int x, int y, int width, int height) :GameObject(tag, x, y, width, height)
{
	layer = GameSystem::LAYER_MONSTER;
	ani = new CAnimation();
	LoadAni();

	moveSpeed = 10;

	Player* player = GameSystem::GetGameObjectWithType<Player>();
	targetX = player->GetX();
	targetY = player->GetY();
	distanceX = (targetX - x);
	distanceY = (targetY - y);
}

BossBullet::~BossBullet()
{
	delete ani;
}

void BossBullet::Act()
{
	x += distanceX / GAME_CYCLE_TIME ;
	y += distanceY / GAME_CYCLE_TIME ;
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

		ani->AddBitmap(cPic,RGB(255,255,255));//加入圖片
		delete cPic;//delete new
	}
}
