#pragma once

//PlayerEquipment
//�D����۪��˳�

#include "Item.h"
#include "Weapon.h"

class PlayerEquipment
{
public:
	PlayerEquipment();
	PlayerEquipment(Weapon rhs);
	PlayerEquipment* operator=(Weapon rhs);//�W�[�˳Ʈɥi�����ഫ

	void SetXY(int hostX, int hostY, int playerCurrentAni, int  palyerAniNumber);
	void ShowBitMap();//��ܹϤ�
private:
	int x, y;
	int attack;
	CMovingBitmap pic;
};