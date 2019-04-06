#pragma once
#include "StdAfx.h"
#include "Weapon.h"
#include "SwordWave.h"
#include "Player.h"
#include "EquipedSlot.h"

class TraditionalSword:public Weapon{
	public:
		TraditionalSword();
		TraditionalSword(string tag, int x, int y, int width, int height, int pictureID);
	private:
		void LoadAni()override;							//���J�ʵe
		void ShowBitMap()override;						//��ܰʵe
		void Picked()override;							//�X�o�ĪG
		void SetXY(int hostX, int hostY, int playerCurrentAni, int  palyerAniNumber)override;	//��D�������ɧ��ܪZ������m �]���|�޷Q��S�Ī���m

		//TraditionalSword GetThisEquipment(); //����Class:Equipment��
		
		SwordWave* wave = new SwordWave("SwordWave", x, y, 77, 70, IDB_0);
		enum ANI {
			ANI_IDLE = 0,
			ANI_LEFT,
			ANI_RIGHT
		};
};