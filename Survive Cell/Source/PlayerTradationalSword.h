#pragma once
#include "PlayerWeapon.h"
#include "SwordWave.h"
class PlayerTraditionalSword:public PlayerWeapon
{
public:
	PlayerTraditionalSword();
	~PlayerTraditionalSword();
	PlayerTraditionalSword(ItemWeapon* rhs);

	void SetXY(int hostX, int hostY, int playerCurrentAni, int  playerAniNumber)override;
	void ShowBitMap()override;
private:
	void LoadAni()override;
	

	SwordWave* wave;//¼Cªi
	enum ANI {
		ANI_IDLE = 0,
		ANI_LEFT,
		ANI_RIGHT
	};
};