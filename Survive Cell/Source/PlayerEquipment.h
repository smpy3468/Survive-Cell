#pragma once

//PlayerEquipment
//主角穿著的裝備

#include "Item.h"
#include "Weapon.h"

class PlayerEquipment
{
public:
	PlayerEquipment();
	PlayerEquipment(Weapon* rhs);
	PlayerEquipment* operator=(Weapon* rhs);//增加裝備時可直接轉換  
private:
	int attack;
};