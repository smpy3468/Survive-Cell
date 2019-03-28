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

void Fire::SetXY(int demonX, int demonY, int currentAni) {
	if (currentAni == ANI_ATTACK_RIGHT) {       //3是左攻擊狀態
		this->x = demonX + 80;
		this->y = demonY + 85;
	}
	else if (currentAni == ANI_ATTACK_LEFT) {
		this->x = demonX - 50;
		this->y = demonY + 85;
	}

}

//---------------------------------------------------------------------------------------

void Fire::ShowBitMap(int attackAniNumber, int currentAni) {
	if (attackAniNumber >= 6 && currentAni == ANI_ATTACK_LEFT) { //3是左攻擊狀態
		currentAni = ANI_FIRE_LEFT;
		SetBitMapPosition();
		ani[currentAni]->OnMove();
		ani[currentAni]->OnShow();
	}
	else if (attackAniNumber >= 6 && currentAni == ANI_ATTACK_RIGHT) {//4是右攻擊狀態
		currentAni = ANI_FIRE_RIGHT;
		SetBitMapPosition();
		ani[currentAni]->OnMove();
		ani[currentAni]->OnShow();
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

	char* aniFire_left[5] = { ".\\res\\fire_left_0.bmp", ".\\res\\fire_left_1.bmp",
							".\\res\\fire_left_2.bmp" , ".\\res\\fire_left_3.bmp" , ".\\res\\fire_left_4.bmp" };
	AddAniBitMaps(aniFire_left, ANI_FIRE_LEFT, 5);

	char* aniFire_right[5] = { ".\\res\\fire_right_0.bmp", ".\\res\\fire_right_1.bmp", 
						".\\res\\fire_right_2.bmp" , ".\\res\\fire_right_3.bmp" , ".\\res\\fire_right_4.bmp" };
	AddAniBitMaps(aniFire_right, ANI_FIRE_RIGHT, 5);
}

