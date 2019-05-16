#pragma once
#include "StdAfx.h"
#include "ItemWeapon.h"
#include "SwordWave.h"
#include "Player.h"
#include "EquipedSlot.h"

class ItemTraditionalSword:public ItemWeapon {
	public:
		ItemTraditionalSword();
		~ItemTraditionalSword();
		ItemTraditionalSword(string tag, int x, int y, int width, int height);
		ItemTraditionalSword(string tag, int x, int y, int width, int height,int damage, int defense);
	private:
		void LoadAni()override;							//���J�ʵe
		//void ShowBitMap()override;						//��ܰʵe
		void Picked()override;							//�X�o�ĪG
		//void SetXY(int hostX, int hostY, int playerCurrentAni, int  palyerAniNumber)override;	//��D�������ɧ��ܪZ������m �]���|�޷Q��S�Ī���m

		//TraditionalSword GetThisEquipment(); //����Class:Equipment��
		
		//SwordWave* wave = new SwordWave("SwordWave", x, y, 77, 70, IDB_0);
		
};