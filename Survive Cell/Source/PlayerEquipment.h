#pragma once

//PlayerEquipment
//�D����۪��˳�

#include "Item.h"
#include "Weapon.h"

class PlayerEquipment
{
public:
	PlayerEquipment();
	PlayerEquipment(Weapon* rhs);
	PlayerEquipment* operator=(Weapon* rhs);//�W�[�˳Ʈɥi�����ഫ  
private:
	int attack;
};