#include"StdAfx.h"
#include "TraditionalSword.h"
#include "Player.h"
TraditionalSword::TraditionalSword() {
	tag = "TraditionalSword";
}



TraditionalSword::TraditionalSword(string tag, int x, int y, int width, int height, int pictureID) :Item(tag, x, y, width, height, pictureID) {
	tag = "TraditionalSword";
	attackDamage = 100;
	attackRange = 100;
	defense = 2;
	LoadAni();
}
void TraditionalSword::SetXY(int hostX, int hostY, int playerCurrentAni, int  playerAniNumber) {
	
	this->x = hostX;
	this->y = hostY;
	this->playerCurrentAni = playerCurrentAni;
	this->playerAniNumber = playerAniNumber;
	
}

void TraditionalSword::LoadAni() {
	char* aniIdle[1] = { ".\\res\\sword_01d.bmp" };
	AddAniBitMaps(aniIdle, ANI_IDLE, 1);
}

void TraditionalSword::ShowBitMap() {

	wave->ShowBitMap(x, y, playerCurrentAni, playerAniNumber);  //int hostX, int hostY, int hostCurrentAni, int attackAniNumber
	ani[currentAni]->OnShow();
}

void TraditionalSword::Picked() {
	Player* player = GameSystem::GetGameObjectWithTag<Player>("Player");

	player->SetAttackDamage(attackDamage);
	player->SetAttackRange(attackRange);
	player->SetDefense(defense);

	//Dead();
}

