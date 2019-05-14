#include"StdAfx.h"
#include "Treasure.h"

Treasure::Treasure(string tag, int x, int y, int width, int height, int damageMin, int damageMax, int defenseMin, int defenseMax) :Item(tag, x, y, width, height)
{
	tag = "Treasure";
	SetY(y);
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
		
	for (int i = -1; i < amount; i++)
	{
		int type = static_cast<int>(GameSystem::Rand(3));

		if (0 <= type && type <= 1)
		{
			//GameSystem::AddGameObject(new Potion("Potion", x + 10 * i, y, 20, 10)); 
			GameSystem::AddGameObject(new ItemTraditionalSword("ItemWeapon", x +  16* i, y + height, 32, 32, 0, 0)); // 16 = 32(width) / 2 
		}
		else if (type > 1)
		{
			//int damage = static_cast<int>(GameSystem::Rand((double)damageMin, (double)damageMax));
			//int defense = static_cast<int>(GameSystem::Rand((double)defenseMin, (double)defenseMax));
			GameSystem::AddGameObject(new ItemTraditionalSword("ItemWeapon", x + 16* i, y + height, 32, 32, 0, 0));
		}
		//GameSystem::AddGameObject(new ItemTraditionalSword("ItemWeapon", x , y, 32, 32, 0, 0));
	}
}
