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

	//void SetIsMoveUp(bool isMoveUp);//�]�w�O�_�V�W����
	//void SetIsMoveDown(bool isMoveDown);//�]�w�O�_�V�U����
	void SetIsMoveLeft(bool isMoveLeft);//�]�w�O�_�V������
	void SetIsMoveRight(bool isMoveRight);//�]�w�O�_�V�k����
	void SetIsGrounded(bool isGrounded);//�]�w�O�_�b�a�W
	void SetIsJump(bool isJump);//�]�w�O�_���U���D
	void Move();//���U���䲾��
	void Fall();//�U��
	void Jump();//���D
private:
	//bool isMoveUp;//�O�_�V�W����
	//bool isMoveDown;//�O�_�V�U����
	bool isMoveLeft;//�O�_�V������
	bool isMoveRight;//�O�_�V�k����
	bool isJump;//�O�_���U���D

	int fallDisplacement;//�U���첾�q(���ʨ�S���a�O����m�|�Ψ�)
	int originJumpDisplacement, jumpDisplacement;//���D�첾�q
	bool isGrounded;//�O�_�b�a�W
};