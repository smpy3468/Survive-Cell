#pragma once

#include "Character.h"
#include "Monster.h"

//Boss
//��

class Boss:public Monster
{
public:
	Boss(string tag, int x, int y, int width, int height);
	void Act();//���
	
	void Attack()override;
	void Move(int dx, int dy)override;
	
private:

	void ShowBitMap()override;

	void NearSlash();//��
	void JumpBack();//�����
	void JumpFront();//���e��
	void FarSlash();//���{�C�i
	void InstantDeath();//�Y���ޯ�

	enum ATTACK_MODE
	{
		ATTACK_NEAR = 0,
		ATTACK_FAR
	};
	int attackMode=ATTACK_NEAR;//�����Ҧ�

	const bool FACE_LEFT = true;//���V����
	const bool FACE_RIGHT = false;//���V�k��
	bool faceLR = FACE_RIGHT;//���V����έ��V�k��

	int currentAni = 0;//�ثe�ʵe
	enum ANI
	{
		ANI_IDLE = 0,
		ANI_LEFT,
		ANI_RIGHT,
		ANI_ATTACK_LEFT,
		ANI_ATTACK_RIGHT,
		ANI_GET_HIT_LEFT,
		ANI_GET_HIT_RIGHT,
	};

	void LoadAni()override;
};