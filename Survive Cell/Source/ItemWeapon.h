#pragma once

//Weapon
//場上的武器道具
//繼承Item

//目前virtual funtion(LoadAni、Picked、ShowBitMap、SetXY)
#include "Item.h"

class ItemWeapon :public Item
{
	friend class PlayerEquipment;
	public:
		ItemWeapon();
		~ItemWeapon();
		ItemWeapon(string tag, int x, int y, int width, int height);
		int GetAttackDamage();
		int GetAttackRange();
		int GetDefense();
	protected:
		int attackDamage;		//攻擊力
		int attackRange;		//攻擊範圍
		int defense;			//防禦力
		int haveEffect;         //是否 有特效;
};