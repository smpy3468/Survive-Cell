#pragma once
#include "StdAfx.h"
#include "ItemWeapon.h"
#include "SwordWave.h"
#include "Player.h"
#include "EquipedSlot.h"

class ItemTraditionalSword:public ItemWeapon {
	public:
		ItemTraditionalSword();
		~ItemTraditionalSword();
		ItemTraditionalSword(string tag, int x, int y, int width, int height);
		ItemTraditionalSword(string tag, int x, int y, int width, int height,int damage, int defense);
	private:
		void LoadAni()override;							//載入動畫
		void Picked()override;							//出發效果
};