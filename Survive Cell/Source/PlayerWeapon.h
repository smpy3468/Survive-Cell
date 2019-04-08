#pragma once
#include "PlayerEquipment.h"

class PlayerWeapon :public PlayerEquipment
{
public:
	PlayerWeapon();
	PlayerWeapon(ItemWeapon rhs);
protected:
	bool haveEffect = false;         //�ϧ_ ���S��;
	int playerCurrentAni = 0, playerAniNumber = 0; //�ΨӧP�_���a�����ʵe�i�����Ӷ��q�A�i�����Effect

	const int ANI_ATTACK_LEFT = 3, ANI_ATTACK_RIGHT = 4;						//�����ʽs�X
};