#pragma once

//Weapon
//���W���Z���D��
//�~��Item

//�ثevirtual funtion(LoadAni�BPicked�BShowBitMap�BSetXY)
#include "Item.h"

class ItemWeapon :public Item
{
	friend class PlayerEquipment;
	public:
		ItemWeapon();
		~ItemWeapon();
		ItemWeapon(string tag, int x, int y, int width, int height);
		int GetAttackDamage();
		int GetAttackRange();
		int GetDefense();
	protected:
		int attackDamage;		//�����O
		int attackRange;		//�����d��
		int defense;			//���m�O
		int haveEffect;         //�O�_ ���S��;
};