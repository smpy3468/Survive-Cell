#pragma once

//Player
//���a
//�~��Character

#include "Character.h"

class Player :public Character
{
public:
	Player();
	Player(string tag, int x, int y, int width, int height, int pictureID);
	void Move(int dx, int dy)override;//���ʯS�w�Z��

	void SetIsMoveLeft(bool isMoveLeft);//�]�w�O�_�V������
	void SetIsMoveRight(bool isMoveRight);//�]�w�O�_�V�k����
	void SetIsGrounded(bool isGrounded);//�]�w�O�_�b�a�W
	void SetIsJump(bool isJump);//�]�w�O�_���U���D
	void Move();//���U���䲾��
	void Fall();//�U��
	void Jump();//���D

	void ShowBitMap()override;//��ܰʵe

	void Attack()override;//����
private:
	bool isMoveLeft;//�O�_�V������
	bool isMoveRight;//�O�_�V�k����
	bool isJumpKeyDown;//�O�_���U���D
	bool isJump;//�O�_���b���D
	bool isFall;//�O�_���b�U��

	int fallDisplacement;//�U���첾�q(���ʨ�S���a�O����m�|�Ψ�)
	int originJumpDisplacement, jumpDisplacement;//���D�첾�q
	bool isGrounded;//�O�_�b�a�W

	void Dead()override;//���`�ɩI�s

	void LoadAni()override;//���J�ʵe
	int currentAni = 0;//�ثe�ʵe

	const unsigned int ANI_IDLE = 0;
	const unsigned int ANI_LEFT = 1;//���ʵe
	const unsigned int ANI_RIGHT = 2;//�k�ʵe
	const unsigned int ANI_JUMP_LEFT = 3;//�����ʵe
	const unsigned int ANI_JUMP_RIGHT = 4;//�k���ʵe
};