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
	this->attackDamage = damage;
	attackRange = 100;
	this->defense = defense;
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
		else if (i->GetIsEquipmentPicSet() == true && player->GetPickCount() > 2
			&& 
			((player->CurrentWeapon() == 1 && i->GetID() == 0)
			||
			(player->CurrentWeapon() == 2 && i->GetID() == 1))
			)
		{	
			i->SetEquipmentPicture(".\\res\\sword_01d.bmp", i->GetX() + 15, i->GetY() + 8);
			break;
		}
	}

	Dead();
}