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

	bool isShoot = false;//�O�_�o�g�F�l�u

	int originJumpDisplacement = 30, jumpDisplacement = originJumpDisplacement;//���D�첾�q

	void ShowBitMap()override;

	void NearSlash();//��
	void JumpBack();//�����
	void JumpFront();//���e��
	void FarShoot();//���{����
	void InstantDeath();//�Y���ޯ�

	int RandomState();//�M�w�H�����A
	int currentState = 0;//�ثe���A
	enum STATE
	{
		STATE_IDLE = 0,
		STATE_MOVE,
		STATE_NEAR_SLASH,
		STATE_FAR_SHOOT,
		STATE_JUMP,
		STATE_LENGTH
	};

	unsigned int stateProb[STATE_LENGTH] = { 10,20,15,15,30 };//�U�ت��A�����v�A�Ʀr�V�j���v�V��
	unsigned int cumProb[STATE_LENGTH] = {0};//�֭p���v

	const bool FACE_LEFT = true;//���V����
	const bool FACE_RIGHT = false;//���V�k��
	bool faceLR = FACE_LEFT;//���V����έ��V�k��

	int currentAni = 0;//�ثe�ʵe
	enum ANI
	{
		ANI_IDLE = 0,
		ANI_LEFT,
		ANI_RIGHT,
		ANI_NEAR_SLASH_LEFT,
		ANI_NEAR_SLASH_RIGHT,
		ANI_JUMP,
		ANI_FAR_SHOOT_LEFT,
		ANI_FAR_SHOOT_RIGHT,
		ANI_GET_HIT_LEFT,
		ANI_GET_HIT_RIGHT
	};

	void LoadAni()override;
};