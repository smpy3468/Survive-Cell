#include "StdAfx.h"
#include "PlayerEquipment.h"

PlayerEquipment::PlayerEquipment()
{
	attack = 0;
}

PlayerEquipment::PlayerEquipment(Weapon * rhs)
{
	operator=(rhs);
}

PlayerEquipment* PlayerEquipment::operator=(Weapon* rhs)
{
	attack = rhs->GetAttackDamage();
	return this;
}
