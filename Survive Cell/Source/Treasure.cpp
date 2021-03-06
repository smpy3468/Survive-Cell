#include"StdAfx.h"
#include "Treasure.h"

Treasure::Treasure(string tag, int x, int y, int width, int height, int damageMin, int damageMax, int defenseMin, int defenseMax) :Item(tag, x, y, width, height)
{
	tag = "Treasure";
	//SetY(y); //不加這行Y軸會在某個地方被改到
	LoadAni();
	this->damageMin = damageMin;
	this->damageMax = damageMax;
	this->defenseMin = defenseMin;
	this->defenseMax = defenseMax;
	//LoadBitMap(".\\res\\Treasure_Idle.bmp");
}

void Treasure::Picked()
{
	GenWeapon(damageMin, damageMax, defenseMin, defenseMax);
	//GameSystem::AddGameObject(new ItemTraditionalSword("ItemWeapon", x, y, 32, 32, 0, 0));
	Dead();
}

void Treasure::LoadAni()
{
	char* aniIdle[1] = { ".\\res\\Treasure_Idle.bmp" };
	AddAniBitMaps(aniIdle, ANI_IDLE, 1);
};

void Treasure::GenWeapon(int damageMin, int damageMax, int defenseMin, int defenseMax)
{
	int amount = 0;
		amount = static_cast<int>( GameSystem::Rand(4));
		
	for (int i = 0; i <= amount; i++)
	{
		int type = static_cast<int>(GameSystem::Rand(10));

		if (type <= 2)
		{
			GameSystem::AddGameObject(new Potion("Potion", x + 10 * i, y, 48, 48)); 
		}
		else if (type <= 5)
		{
			int damage = static_cast<int>(GameSystem::Rand(damageMin, damageMax));
			int defense = static_cast<int>(GameSystem::Rand(defenseMin, defenseMax));
			GameSystem::AddGameObject(new ItemTraditionalSword("ItemWeapon", x + 16* i, y, 32, 32, damage, defense));
		}
		else if (type <= 10)
		{
			int damage = static_cast<int>(GameSystem::Rand(damageMin, damageMax));
			int defense = static_cast<int>(GameSystem::Rand(defenseMin, defenseMax));
			GameSystem::AddGameObject(new ItemWeaponBow("ItemWeapon", x + 10 * i, y, 48, 48, damage, defense));
		}
	}
}