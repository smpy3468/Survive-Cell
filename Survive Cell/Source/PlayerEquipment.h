#pragma once

//PlayerEquipment
//主角穿著的裝備

#include "Item.h"
#include "Weapon.h"

class PlayerEquipment
{
public:
	PlayerEquipment();
	PlayerEquipment(Weapon rhs);
	PlayerEquipment* operator=(Weapon rhs);//增加裝備時可直接轉換

	void SetXY(int hostX, int hostY, int playerCurrentAni, int  palyerAniNumber);
	void ShowBitMap();//顯示圖片
private:
	int x, y;
	int attack;
	CMovingBitmap pic;
};