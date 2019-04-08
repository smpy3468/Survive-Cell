#pragma once
#include "PlayerEquipment.h"

class PlayerWeapon :public PlayerEquipment
{
public:
	PlayerWeapon();
	PlayerWeapon(ItemWeapon rhs);
private:
	int attackDamage;		//攻擊力
	int attackRange;		//攻擊範圍
	int defense;			//防禦力
	int haveEffect;         //使否 有特效;
	//int playerCurrentAni = 0, playerAniNumber = 0; //用來判斷玩家攻擊動畫進行到哪個階段，進而顯示Effect
	const int ANI_ATTACK_LEFT = 3, ANI_ATTACK_RIGHT = 4;						//攻擊動編碼
};