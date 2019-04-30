#pragma once

#include "Character.h"

//Boss
//��

class Boss:public Character
{
public:
	Boss(string tag, int x, int y, int width, int height);
	void Act();//���

private:
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