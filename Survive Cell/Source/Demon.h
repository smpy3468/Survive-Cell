#pragma once
#include "Monster.h"
#include "Fire.h"
#include "Player.h"
//DefenseRange
class Demon:public Monster {
	public:
		Demon();																			//BaseConstructor
		Demon::Demon(string tag, int x, int y, int width, int height, int pictureID);		//Constructor
		void Attack()override;																//����
		void AutoMove()override;															//����
		void ShowBitMap()override;															//��ܰʵe
	private:
		void LoadAni()override;																//���J�Ҧ��ʵe
		Player* player = GameSystem::GetGameObjectWithTag<Player>("Player");				//�`�Ψ�N���O���U��
		Fire* fire;																			//�۱a���K�S��
		int currentBitMapNumber;
};
