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
	if (currentAni == ANI_ATTACK_RIGHT) {       //3�O���������A
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
	if (attackAniNumber >= 6 && currentAni == ANI_ATTACK_LEFT) { //3�O���������A
		currentAni = ANI_FIRE_LEFT;
		SetBitMapPosition();
		ani[currentAni]->OnMove();
		ani[currentAni]->OnShow();
		if (IsPlayerInRange(0,0,0,0) && ani[currentAni]->GetCurrentBitmapNumber()>=2 && hit ==0){
			player->DecreaseHP(1);
			hit = 1;
		}
			
	}
	else if (attackAniNumber >= 6 && currentAni == ANI_ATTACK_RIGHT) {//4�O�k�������A
		currentAni = ANI_FIRE_RIGHT;
		SetBitMapPosition();
		ani[currentAni]->OnMove();
		ani[currentAni]->OnShow();
		if (IsPlayerInRange(0,0,0,0) && ani[currentAni]->GetCurrentBitmapNumber() >= 2 && hit ==0){
			player->DecreaseHP(1);
			hit = 1;
		}
	}
	else hit = 0;
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
	while ((int)ani.size() <= aniType)//vector���j�p�����j
		ani.push_back(new CAnimation);//�W�[�j�p

	ani[aniType]->AddBitmap(pic, RGB(255, 255, 255));
}

bool Fire::IsPlayerInRange(int right_fix, int left_fix, int up_fix, int down_fix) {
	int RIGHT_EDGE = x + width / 2 + right_fix, LEFT_EDGE = x - width / 2 - left_fix,
		UP_EDGE = y - height / 2 - up_fix, DOWN_EDGE = y + height / 2 + down_fix;

	int OB_X = player->GetX(), OB_Y = player->GetY(), OB_WIDTH = player->GetWidth(), OB_HEIGHT = player->GetHeight();

	int OB_RIGHT_EDGE = OB_X + OB_WIDTH / 2, OB_LEFT_EDGE = OB_X - OB_WIDTH / 2,
		OB_UP_EDGE = OB_Y - OB_HEIGHT / 2, OB_DOWN_EDGE = OB_Y + OB_HEIGHT / 2;

	if (OB_RIGHT_EDGE >= LEFT_EDGE )        //�H�b��, �Ǫ��b�k
		return true;
	else if (OB_LEFT_EDGE <= RIGHT_EDGE)  //�H�b�k, �Ǫ��b��
		return true;
	/*else if (OB_DOWN_EDGE > UP_EDGE)       //�H�b�U, �Ǫ��b�W
			return true;
	else if (OB_UP_EDGE < DOWN_EDGE)	   //�H�b�W, �Ǫ��b�U
			return true;*/
	return false;
}

void Fire::LoadAni() {

	char* aniFire_left[5] = { ".\\res\\fire_left_0.bmp", ".\\res\\fire_left_1.bmp",
							".\\res\\fire_left_2.bmp" , ".\\res\\fire_left_3.bmp" , ".\\res\\fire_left_4.bmp" };
	AddAniBitMaps(aniFire_left, ANI_FIRE_LEFT, 5);

	char* aniFire_right[5] = { ".\\res\\fire_right_0.bmp", ".\\res\\fire_right_1.bmp", 
						".\\res\\fire_right_2.bmp" , ".\\res\\fire_right_3.bmp" , ".\\res\\fire_right_4.bmp" };
	AddAniBitMaps(aniFire_right, ANI_FIRE_RIGHT, 5);
}
