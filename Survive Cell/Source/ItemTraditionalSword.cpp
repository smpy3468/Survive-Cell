#include"StdAfx.h"
#include "ItemTraditionalSword.h"
#include "PlayerTradationalSword.h"

ItemTraditionalSword::ItemTraditionalSword() {
	tag = "ItemWeapon";
}

ItemTraditionalSword::~ItemTraditionalSword()
{
}



ItemTraditionalSword::ItemTraditionalSword(string tag, int x, int y, int width, int height) :ItemWeapon(tag, x, y, width, height) {
	tag = "ItemWeapon";
	attackDamage = 100;
	attackRange = 100;
	defense = 2;
	LoadAni();
	LoadBitMap(".\\res\\sword_01d.bmp");
}

ItemTraditionalSword::ItemTraditionalSword(string tag, int x, int y, int width, int height,int damage, int defense) :ItemWeapon(tag, x, y, width, height) {
	tag = "ItemWeapon";
	attackDamage = damage;
	SetY(y); //不加這行Y軸會在某個地方被改到
	attackRange = 100;
	defense = defense;
	LoadAni();
	LoadBitMap(".\\res\\sword_01d.bmp");
}


void ItemTraditionalSword::LoadAni() {
	char* aniIdle[1] = { ".\\res\\sword_01d.bmp" };
	AddAniBitMaps(aniIdle, ANI_IDLE, 1);
}


void ItemTraditionalSword::Picked() {
	Player* player = GameSystem::GetGameObjectWithTag<Player>("Player");

	//家佑測試的
	player->AddEquipment<PlayerTraditionalSword>(new PlayerTraditionalSword(this));

	//--------------UI設定--------------------------//
	vector<EquipedSlot*> equipedSlots = GameSystem::GetUInterfacesWithTag<EquipedSlot>("EquipedSlot");


	for (auto& i : equipedSlots)
	{
		if (i->GetIsEquipmentPicSet() == false)
		{
			i->SetEquipmentPicture(".\\res\\sword_01d.bmp", i->GetX() + 15, i->GetY() + 8);
			break;
		}
		//還有後續
	}

	Dead();
}



