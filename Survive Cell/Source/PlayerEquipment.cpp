#include "StdAfx.h"
#include "PlayerEquipment.h"

PlayerEquipment::PlayerEquipment()
{
	attack = 0;
}

PlayerEquipment::PlayerEquipment(Weapon rhs)
{
	operator=(rhs);
}

PlayerEquipment* PlayerEquipment::operator=(Weapon rhs)
{
	attack = rhs.GetAttackDamage();
	pic = rhs.objectPic;
	return this;
}

void PlayerEquipment::SetXY(int hostX, int hostY, int playerCurrentAni, int  playerAniNumber) {

	this->x = hostX;
	this->y = hostY;
}

void PlayerEquipment::ShowBitMap()
{
	pic.SetTopLeft(x - Map::GetSX(), y - Map::GetSY());
	pic.ShowBitmap();
}
