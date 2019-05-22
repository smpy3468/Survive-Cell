#pragma once
#include "PlayerWeapon.h"
#include "Arrow.h"
#include "Player.h"
class PlayerBow :public PlayerWeapon
{
public:
	~PlayerBow();
	PlayerBow(ItemWeapon* rhs);
	//void SetXY(int hostX, int hostY, int playerCurrentAni, int  playerAniNumber)override;
	void ShowBitMap()override;
	void SetXY(int hostX, int hostY, int playerCurrentAni, int  playerAniNumber)override;
private:
	void ShowArrow();
	void CleanArrow(Arrow* arrow);
	void CleanArrowList();
	void LoadAni()override;
	vector <Arrow*> arrowList;
	enum ANI {
		ANI_IDLE = 0,
		ANI_LEFT,
		ANI_RIGHT
	};
};