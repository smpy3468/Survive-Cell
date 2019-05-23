#include "StdAfx.h"
#include"PlayerBow.h"

PlayerBow::~PlayerBow()
{

}

PlayerBow::PlayerBow(ItemWeapon* rhs) :PlayerWeapon(rhs)
{
	SetX(player->GetX());
	SetY(player->GetY());
	LoadAni();
	haveEffect = true;
	isShoot = false;
}

void PlayerBow::SetXY(int hostX, int hostY, int playerCurrentAni, int  playerAniNumber)
{
	SetX(hostX);
	SetY(hostY);
	this->playerCurrentAni = playerCurrentAni;
	this->playerAniNumber = playerAniNumber;
}

void PlayerBow::ShowBitMap()
{	
	if((playerCurrentAni == ANI_ATTACK_LEFT || playerCurrentAni == ANI_ATTACK_RIGHT) && playerAniNumber==2 && isShoot == false){		//增加arrow物件
		isShoot = true;
		GameSystem::AddGameObject(new Arrow("Arrow", x, y, 48, 48, 300, playerCurrentAni));
	}
	else if (playerAniNumber == 0 && isShoot == true)
	{
		isShoot = false;
	}

	SetXY(player->GetX(), player->GetY(), playerCurrentAni, playerAniNumber);
	SetBitMapPosition();
	ani[currentAni]->OnShow();
}



void PlayerBow::LoadAni()
{
	char* aniIdle[1] = { ".\\res\\bow.bmp" };
	AddAniBitMaps(aniIdle, ANI_IDLE, 1);
}
