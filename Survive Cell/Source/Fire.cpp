#include "StdAfx.h"
#include "Fire.h"
#include "Monster.h"
#include "GameSystem.h"
#include "Player.h"
#include <vector>
Fire::Fire(string tag, int x, int y, int width, int height, int pictureID):GameObject(tag, x, y, width, height, pictureID) {
	tag = "Fire";
	LoadAni();
}

void Fire::SetBitMapPosition ()
{
	for (auto& i : ani)
	{
		i->SetTopLeft(this->x - Map::GetSX(), this->y - Map::GetSY());
	}
}


void Fire::ShowBitMap() {
	vector<Monster*> allMonsters = GameSystem::GetGameObjectsWithTag<Monster>("Monster");
	Player * player = GameSystem::GetGameObjectWithTag<Player>("Player");
	
 	for (auto& i : allMonsters) {
		if (i->PlaceRelativePlayer(player) == LEFT && i->GetAttackAniNumber() >= 6) { //2是攻擊狀態
			currentAni = ANI_FIRE_LEFT;
			x = i->GetX()+145;
			y = i->GetY()+100;
			ani[currentAni]->OnShow();
		}
		else if (i->PlaceRelativePlayer(player) == RIGHT && i->GetAttackAniNumber() >= 6) {
			x = i->GetX()+145;
			y = i->GetY()+100;
			currentAni = ANI_FIRE_RIGHT;
			ani[currentAni]->OnShow();
		}
	}
}


void Fire::AddAniBitMaps(char * pic[], int aniType, int picCount)
{
	for (int i = 0; i < picCount; i++)
	{
		AddAniBitMap(pic[i], aniType);
	}
}

void Fire::AddAniBitMap(char* pic, int aniType)
{
	while ((int)ani.size() <= aniType)//vector的大小不夠大
		ani.push_back(new CAnimation);//增加大小

	ani[aniType]->AddBitmap(pic, RGB(255, 255, 255));
}


void Fire::LoadAni() {

	char* aniFire_left[5] = { ".\\res\\fire0.bmp", ".\\res\\fire1.bmp", ".\\res\\fire2.bmp" , ".\\res\\fire3.bmp" , ".\\res\\fire4.bmp" };
	AddAniBitMaps(aniFire_left, ANI_FIRE_LEFT, 5);

	char* aniFire_right[5] = { ".\\res\\fire0.bmp", ".\\res\\fire1.bmp", ".\\res\\fire2.bmp" , ".\\res\\fire3.bmp" , ".\\res\\fire4.bmp" };
	AddAniBitMaps(aniFire_right, ANI_FIRE_RIGHT, 5);
}

