#pragma once
#include "Monster.h"
#include "Fire.h"
#include "Player.h"
//DefenseRange
class Demon:public Monster {
	public:
		Demon();																			//BaseConstructor
		~Demon();
		Demon::Demon(string tag, int x, int y, int width, int height);		//Constructor
		void Attack()override;																//����
		void IsAttack();
		void AutoMove()override;															//����
		void ShowBitMap()override;															//��ܰʵe
		void Act()override;																	//�զX�U�ذʧ@(ISATTACK, AUTOMOVE, ATTACK)
	private:
		void LoadAni()override;																//���J�Ҧ��ʵe


		Fire* fire;																			//�۱a���K�S��
		int currentBitMapNumber;
		bool aniFix=false;
		bool isBreak;																		//�����O�_�Q���_
};
