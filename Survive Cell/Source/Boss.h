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
	int GetPhase();//�ثe���q

private:

	void Jump();//���D
	void Fall(int perDisplacement);//����
	void Move(int dx, int dy)override;

	bool isShoot = false;//�O�_�o�g�F�l�u

	int originJumpDisplacement = 30, jumpDisplacement = originJumpDisplacement;//���D�첾�q

	void ShowBitMap()override;

	void NearSlash();//��
	void JumpBack();//�����
	void JumpFront();//���e��
	const int JUMP_FRONT = 0, JUMP_BACK = 1;
	int jumpMode;//���D�Ҧ�
	void FarShoot();//���{����
	void InstantDeath();//�Y���ޯ�

	int RandomState();//�M�w�H�����A
	int currentState = 0;//�ثe���A
	int nearAttackRange = width;//������Z��
	int farAttackRange = SIZE_X * 2 / 3;//�������Z��
	int playerDistanceX, playerDistanceY;//���a��BOSS���Z��

	enum STATE
	{
		STATE_IDLE = 0,
		STATE_MOVE,
		STATE_NEAR_SLASH,
		STATE_FAR_SHOOT,
		STATE_JUMP,
		STATE_LENGTH
	};

	unsigned int currentStateProb[STATE_LENGTH];//�ثe�U�ت��A�����v�A�|�ھڪ��a���Z���BBOSS����q���]�����ܤ�
	unsigned int cumStateProb[STATE_LENGTH] = { 0 };//�U�����A���֭p���v�A�ΨӧP�O�üƥΪ�
	void ChangeStateProb(unsigned int newStateProb[]);//���ܦU�����A���v
	//�U�ت��A�����v�A�Ʀr�V�j���v�V��

	unsigned int originStateProb[STATE_LENGTH] = { 1,30,0,0,0 };//��l���v�A���a���b�����d�򤺮ɮM��
	unsigned int farStateProb[STATE_LENGTH] = { 0,0,0,30,10 };//���Z���ɪ����v
	unsigned int nearStateProb[STATE_LENGTH] = { 0,0,30,0,10 };//��Z���ɪ����v
	bool InNear();//�b��Z�����d��
	bool InFar();//�b���Z�����d��

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
		/*ANI_GET_HIT_LEFT,
		ANI_GET_HIT_RIGHT,*/
		ANI_LENGTH
	};

	int phase = 1;//���q

	void LoadAni()override;
};