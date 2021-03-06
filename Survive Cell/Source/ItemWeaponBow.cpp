#include "StdAfx.h"
#include "ItemWeaponBow.h"
#include "PlayerBow.h"
ItemWeaponBow::ItemWeaponBow(string tag, int x, int y, int width, int height) :ItemWeapon(tag, x, y, width, height)
{
	tag = "ItemWeapon";
	attackRange = 100;
	this->attackDamage = 50;
	this->defense = 0;
	LoadAni();
	LoadBitMap(".\\res\\bow.bmp");
}

ItemWeaponBow::ItemWeaponBow(string tag, int x, int y, int width, int height, int damage, int defense) :ItemWeapon(tag, x, y, width, height)
{
	tag = "ItemWeapon";
	attackRange = 100;
	this->attackDamage = damage;
	this->defense = defense;
	LoadAni();
	LoadBitMap(".\\res\\bow.bmp");
}

ItemWeaponBow::~ItemWeaponBow()
{

}

void ItemWeaponBow::Picked() {
	Player* player = GameSystem::GetGameObjectWithTag<Player>("Player");

	//家佑測試的
	player->AddEquipment<PlayerBow>(new PlayerBow(this));

	//--------------UI設定--------------------------//
	vector<EquipedSlot*> equipedSlots = GameSystem::GetUInterfacesWithTag<EquipedSlot>("EquipedSlot");

	for (auto& i : equipedSlots)
	{
		if (i->GetIsEquipmentPicSet() == false)
		{
			i->SetEquipmentPicture(".\\res\\bow.bmp", i->GetX() + 15, i->GetY() + 8);
			break;
		}
		else if (i->GetIsEquipmentPicSet() == true && player->GetPickCount() > 2
			&& 
			((player->CurrentWeapon() == 1 && i->GetID() == 0)
			||
			(player->CurrentWeapon() == 2 && i->GetID() == 1))
			)
		{		
			i->SetEquipmentPicture(".\\res\\bow.bmp", i->GetX() + 15, i->GetY() + 8);
			break;
		}
	}

	Dead();
}

void ItemWeaponBow::LoadAni()
{
	char* aniIdle[1] = { ".\\res\\bow.bmp" };
	AddAniBitMaps(aniIdle, ANI_IDLE, 1);
}