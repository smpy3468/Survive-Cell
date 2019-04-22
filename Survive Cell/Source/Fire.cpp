#include "StdAfx.h"
#include "Fire.h"
#include "Monster.h"
#include "GameSystem.h"
#include "Player.h"
#include <vector>

Fire::Fire(string tag, int x, int y, int width, int height):Effect(tag, x, y, width, height) {
	tag = "Fire";
	LoadAni();
}


void Fire::SetXY(int hostX, int hostY, int hostCurrentAni) {
	if (hostCurrentAni == ANI_ATTACK_RIGHT) {       //3是左攻擊狀態
		this->x = hostX + 80;
		this->y = hostY + 85;
	}
	else if (hostCurrentAni == ANI_ATTACK_LEFT) {
		this->x = hostX - 95;
		this->y = hostY + 85;
	}

}


//---------------------------------------------------------------------------------------

void Fire::ShowBitMap(int hostX, int hostY, int hostCurrentAni, int attackAniNumber) {
	SetXY(hostX, hostY, hostCurrentAni);

	if (attackAniNumber >= 6 && hostCurrentAni == ANI_ATTACK_LEFT) { //3是左攻擊狀態
		currentAni = ANI_FIRE_LEFT;
		SetBitMapPosition();
		ani[currentAni]->OnMove();
		ani[currentAni]->OnShow();
		if (IsObjectInRange(player , 0, 0, 0, 0) && ani[currentAni]->GetCurrentBitmapNumber()>=2 && isHit ==0){
			player->DecreaseHP(10);
			isHit = 1;
		}
			
	}
	else if (attackAniNumber >= 6 && hostCurrentAni == ANI_ATTACK_RIGHT) {//4是右攻擊狀態
		currentAni = ANI_FIRE_RIGHT;
		SetBitMapPosition();
		ani[currentAni]->OnMove();
		ani[currentAni]->OnShow();
		if (IsObjectInRange(player,0,0,0,0) && ani[currentAni]->GetCurrentBitmapNumber() >= 2 && isHit ==0){
			player->DecreaseHP(10);
			isHit = 1;
		}
	}
	else isHit = 0;
}


/*void Fire::AddAniBitMaps(char * pic[], int aniType, int picCount)
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
}*/

/*bool Fire::IsPlayerInRange(int right_fix, int left_fix, int up_fix, int down_fix) {
	int RIGHT_EDGE = x + width + right_fix, LEFT_EDGE = x - left_fix,
		UP_EDGE = y - up_fix, DOWN_EDGE = y + height + down_fix;

	int OB_X = player->GetX(), OB_Y = player->GetY(), OB_WIDTH = player->GetWidth(), OB_HEIGHT = player->GetHeight();

	int OB_RIGHT_EDGE = OB_X + OB_WIDTH, OB_LEFT_EDGE = OB_X,
		OB_UP_EDGE = OB_Y, OB_DOWN_EDGE = OB_Y + OB_HEIGHT;

	if (OB_RIGHT_EDGE >= LEFT_EDGE && OB_RIGHT_EDGE <= RIGHT_EDGE)        //人在左, 火焰在右
		return true;
	else if (OB_LEFT_EDGE <= RIGHT_EDGE && OB_LEFT_EDGE >= LEFT_EDGE)  //人在右, 火焰在左
		return true;
	/*else if (OB_DOWN_EDGE > UP_EDGE)       //人在下, 怪物在上
			return true;
	else if (OB_UP_EDGE < DOWN_EDGE)	   //人在上, 怪物在下
			return true;
	return false;
}*/

void Fire::LoadAni() {

	char* aniFire_left[5] = { ".\\res\\fire_left_0.bmp", ".\\res\\fire_left_1.bmp",
							".\\res\\fire_left_2.bmp" , ".\\res\\fire_left_3.bmp" , ".\\res\\fire_left_4.bmp" };
	AddAniBitMaps(aniFire_left, ANI_FIRE_LEFT, 5);

	char* aniFire_right[5] = { ".\\res\\fire_right_0.bmp", ".\\res\\fire_right_1.bmp", 
						".\\res\\fire_right_2.bmp" , ".\\res\\fire_right_3.bmp" , ".\\res\\fire_right_4.bmp" };

	AddAniBitMaps(aniFire_right, ANI_FIRE_RIGHT, 5);
}

