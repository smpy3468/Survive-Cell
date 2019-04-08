#pragma once

//Weapon
//���W���Z���D��
//�~��Item

//�ثevirtual funtion(LoadAni�BPicked�BShowBitMap�BSetXY)
#include "Item.h"

class Weapon :public Item
{
	friend class PlayerEquipment;
	public:
		Weapon();
		Weapon(string tag, int x, int y, int width, int height, int pictureID);
		int GetAttackDamage();

	protected:
		int attackDamage;		//�����O
		int attackRange;		//�����d��
		int defense;			//���m�O
		int haveEffect;         //�ϧ_ ���S��;
		int playerCurrentAni = 0, playerAniNumber = 0; //�ΨӧP�_���a�����ʵe�i�����Ӷ��q�A�i�����Effect
		const int ANI_ATTACK_LEFT = 3, ANI_ATTACK_RIGHT = 4;						//�����ʽs�X
};