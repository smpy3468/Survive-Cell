#pragma once

#include "Character.h"
#include "Monster.h"

//Boss
//��

class Boss :public Monster
{
public:
	Boss();
	~Boss();
	Boss(string tag, int x, int y, int width, int height);
	void Act();//���
	
	void Attack()override;
	void Jump();//���D
	void Fall(int perDisplacement);//����
	void Move(int dx, int dy)override;

private:

	int originJumpDisplacement = 30, jumpDisplacement = originJumpDisplacement;//���D�첾�q

	void ShowBitMap()override;

	void NearSlash();//��
	void JumpBack();//�����
	void JumpFront();//���e��
	void FarSlash();//���{�C�i
	void InstantDeath();//�Y���ޯ�

	int currentState = 0;//�ثe���A
	enum STATE
	{
		STATE_IDLE = 0,
		STATE_MOVE,
		STATE_ATTACK,
		STATE_JUMP,
		STATE_LENGTH
	};
	int attackMode = 0;//�����Ҧ�

	const bool FACE_LEFT = true;//���V����
	const bool FACE_RIGHT = false;//���V�k��
	bool faceLR = FACE_LEFT;//���V����έ��V�k��

	int currentAni = 0;//�ثe�ʵe
	enum ANI
	{
		ANI_IDLE = 0,
		ANI_LEFT,
		ANI_RIGHT,
		ANI_ATTACK_LEFT,
		ANI_ATTACK_RIGHT,
		ANI_JUMP,
		ANI_GET_HIT_LEFT,
		ANI_GET_HIT_RIGHT
	};

	void LoadAni()override;
};