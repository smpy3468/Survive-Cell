#pragma once
#include "PlayerEquipment.h"
#include "Player.h"

class PlayerWeapon :public PlayerEquipment
{
public:
	PlayerWeapon();
	virtual ~PlayerWeapon();
	PlayerWeapon(ItemWeapon* rhs);
protected:
	bool haveEffect = false;         //使否 有特效;
	int playerCurrentAni = 0, playerAniNumber = 0; //用來判斷玩家攻擊動畫進行到哪個階段，進而顯示Effect


	const int ANI_ATTACK_LEFT = 3, ANI_ATTACK_RIGHT = 4;						//攻擊動編碼
};