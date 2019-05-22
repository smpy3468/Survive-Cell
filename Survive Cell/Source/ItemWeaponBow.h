#pragma once
#include"ItemWeapon.h"
#include "EquipedSlot.h"
class ItemWeaponBow :public ItemWeapon
{
public:
	ItemWeaponBow(string tag, int x, int y, int width, int hegiht);
	ItemWeaponBow(string tag, int x, int y, int width, int hegiht,int damage, int defense);
	~ItemWeaponBow();

private:
	void Picked()override;							//出發效果
	void LoadAni()override;							//載入動畫
};