#pragma once
#include "Item.h"
#include "GameSystem.h"
#include "Potion.h"
#include "ItemTraditionalSword.h"
#include "ItemWeaponBow.h"
class Treasure :public Item
{
public:
	Treasure(string tag, int x, int y, int width, int height, int damageMin, int damageMax, int defenseMin, int defenseMax);
	void Picked()override;
private:
	void LoadAni()override;
	void GenWeapon(int damageMin, int damageMax, int defenseMin, int denfenseMax);	//產生裝備

	int damageMin, damageMax, defenseMin, defenseMax;//用來設定這箱寶箱裝備的品質
};