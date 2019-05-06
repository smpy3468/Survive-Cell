#include "StdAfx.h"
#include "ItemWeapon.h"

ItemWeapon::ItemWeapon()
{
	tag = "ItemWeapon";
}

ItemWeapon::~ItemWeapon()
{
}

ItemWeapon::ItemWeapon(string tag, int x, int y, int width, int height):Item(tag, x, y, width, height){
	tag = "ItemWeapon";
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
