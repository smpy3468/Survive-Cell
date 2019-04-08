#include "StdAfx.h"
#include "ItemWeapon.h"

ItemWeapon::ItemWeapon()
{
	tag = "Weapon";
}

ItemWeapon::ItemWeapon(string tag, int x, int y, int width, int height, int pictureID):Item(tag, x, y, width, height, pictureID){
	tag = "Weapon";
}

int ItemWeapon::GetAttackDamage()
{
	return attackDamage;
}

int ItemWeapon::GetAttackRange()
{
	return attackRange;
}

int ItemWeapon::GetDefense()
{
	return defense;
}
