#include "StdAfx.h"
#include"PlayerBow.h"

PlayerBow::~PlayerBow()
{
	CleanArrowList();
}

PlayerBow::PlayerBow(ItemWeapon* rhs) :PlayerWeapon(rhs)
{
	SetX(player->GetX());
	SetY(player->GetY());
	LoadAni();
	haveEffect = true;
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
	if((playerCurrentAni == ANI_ATTACK_LEFT || playerCurrentAni == ANI_ATTACK_RIGHT) ){
		arrowList.push_back(new Arrow("Arrow", x, y, 48, 48));
	}
	ShowArrow();
		 //int hostX, int hostY, int hostCurrentAni, int attackAniNumber
	SetXY(player->GetX(), player->GetY(), playerCurrentAni, playerAniNumber);
	SetBitMapPosition();
	ani[currentAni]->OnShow();
}

void PlayerBow :: ShowArrow()
{
	for (auto &i : arrowList)
	{
		i->ShowBitMap();
	}
}

void PlayerBow::CleanArrow(Arrow* arrow)
{
	delete arrow;
};

void PlayerBow::CleanArrowList()
{
	for (auto &i : arrowList)
	{
		CleanArrow(i);
	}
}

void PlayerBow::LoadAni()
{
	char* aniIdle[1] = { ".\\res\\bow.bmp" };
	AddAniBitMaps(aniIdle, ANI_IDLE, 1);
}
