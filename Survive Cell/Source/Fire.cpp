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

Fire::~Fire()
{
}


void Fire::SetXY(int hostX, int hostY, int hostCurrentAni) {
	if (hostCurrentAni == ANI_ATTACK_RIGHT) {       //3¬O¥ª§ðÀ»ª¬ºA
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

	if (attackAniNumber >= 6 && hostCurrentAni == ANI_ATTACK_LEFT) { //3¬O¥ª§ðÀ»ª¬ºA
		currentAni = ANI_FIRE_LEFT;
		SetBitMapPosition();
		ani[currentAni]->OnMove();
		ani[currentAni]->OnShow();
		if (IsObjectInRange(player, 0, 0, 15, 25) && ani[currentAni]->GetCurrentBitmapNumber()>=2 && isHit ==0){
			player->DecreaseHP(10);
			isHit = 1;
		}
			
	}
	else if (attackAniNumber >= 6 && hostCurrentAni == ANI_ATTACK_RIGHT) {//4¬O¥k§ðÀ»ª¬ºA
		currentAni = ANI_FIRE_RIGHT;
		SetBitMapPosition();
		ani[currentAni]->OnMove();
		ani[currentAni]->OnShow();
		if (IsObjectInRange(player,0,0, 15, 25) && ani[currentAni]->GetCurrentBitmapNumber() >= 2 && isHit ==0){
			player->DecreaseHP(10);
			isHit = 1;
		}
	}
	else isHit = 0;
}

void Fire::LoadAni() {

	char* aniFire_left[5] = { ".\\res\\fire_left_0.bmp", ".\\res\\fire_left_1.bmp",
							".\\res\\fire_left_2.bmp" , ".\\res\\fire_left_3.bmp" , ".\\res\\fire_left_4.bmp" };
	AddAniBitMaps(aniFire_left, ANI_FIRE_LEFT, 5);

	char* aniFire_right[5] = { ".\\res\\fire_right_0.bmp", ".\\res\\fire_right_1.bmp", 
						".\\res\\fire_right_2.bmp" , ".\\res\\fire_right_3.bmp" , ".\\res\\fire_right_4.bmp" };

	AddAniBitMaps(aniFire_right, ANI_FIRE_RIGHT, 5);
}