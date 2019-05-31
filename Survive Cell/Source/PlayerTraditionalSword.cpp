#include "StdAfx.h"
#include "PlayerTradationalSword.h"

PlayerTraditionalSword::PlayerTraditionalSword() 
{
	
}

PlayerTraditionalSword::~PlayerTraditionalSword()
{
	delete wave;
}

PlayerTraditionalSword::PlayerTraditionalSword(ItemWeapon* rhs):PlayerWeapon(rhs)
{
	SetX(player->GetX());
	SetY(player->GetY());
	LoadAni();
	wave = new SwordWave("SwordWave", x, y, 77, 70);
	haveEffect = true;
}

void PlayerTraditionalSword::SetXY(int hostX, int hostY, int playerCurrentAni, int  playerAniNumber)
{
	SetX(hostX);
	SetY(hostY);
	this->playerCurrentAni = playerCurrentAni;
	this->playerAniNumber = playerAniNumber;
}

void PlayerTraditionalSword::ShowBitMap()
{
	wave->ShowBitMap(x, y, playerCurrentAni, playerAniNumber);  //int hostX, int hostY, int hostCurrentAni, int attackAniNumber
	//SetXY(player->GetX(), player->GetY(), playerCurrentAni, playerAniNumber);
	SetBitMapPosition();
	ani[currentAni]->OnShow();
}

void PlayerTraditionalSword::LoadAni()
{
	char* aniIdle[1] = { ".\\res\\sword_01d.bmp" };
	AddAniBitMaps(aniIdle, ANI_IDLE, 1);
}