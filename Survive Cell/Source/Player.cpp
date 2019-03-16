#include "StdAfx.h"
#include "GameSystem.h"
#include "Player.h"
#include "Map.h"

Player::Player()
{
	tag = "Player";
}

Player::Player(string tag, int x, int y, int width, int height, int pictureID) :Character(tag, x, y, width, height, pictureID)
{
	tag = "Player";

	originMoveSpeed = 5;
	moveSpeed = originMoveSpeed;

	fallDisplacement = 0;

	originJumpDisplacement = 10;
	jumpDisplacement = originJumpDisplacement;

	//isMoveUp = false;
	//isMoveDown = false;
	isMoveLeft = false;
	isMoveRight = false;

	isJump = false;
	isGrounded = true;
}

void Player::Move(int dx, int dy)
{
	if (!Map::HasObject(x + dx, y + dy))//�p�G�Ӯy�ШS������
	{
		Map::MoveScreenTopLeft(dx, dy);//�ù�����
		this->x += dx;//���ax����
		this->y += dy;//���ay����
	}
}

/*void Player::SetIsMoveUp(bool isMoveUp)
{
	this->isMoveUp = isMoveUp;
}*/

/*void Player::SetIsMoveDown(bool isMoveDown)
{
	this->isMoveDown = isMoveDown;
}*/

void Player::SetIsMoveLeft(bool isMoveLeft)
{
	this->isMoveLeft = isMoveLeft;
}

void Player::SetIsMoveRight(bool isMoveRight)
{
	this->isMoveRight = isMoveRight;
}

void Player::SetIsJump(bool isJump)
{
	this->isJump = isJump;
}

void Player::SetIsGrounded(bool isGrounded)
{
	this->isGrounded = isGrounded;
}

void Player::Move()//���ʤ�V
{
	/*if (this->isMoveUp)
	{
		Move(0, -moveSpeed);
	}*/

	/*if (this->isMoveDown)
	{
		Move(0, moveSpeed);
	}*/


	if (this->isMoveLeft)
	{
		Move(-moveSpeed, 0);
	}

	if (this->isMoveRight)
	{
		Move(moveSpeed, 0);
	}

	if (this->isJump)//�p�G���U���D
	{
		if (isGrounded)//�p�G�b�a�W
		{
			isGrounded = false;
		}
	}

	Jump();//���D
	Fall();//�U��
}

void Player::Fall()
{
	if (!Map::HasObject(this->x, this->y + this->height))//�p�G�}�U�S�F��
	{
		if (isGrounded == true)//�쥻�b�a�W
		{
			fallDisplacement++;
			this->y += fallDisplacement;
			Map::MoveScreenTopLeft(0, fallDisplacement);
		}
	}
	else
	{
		fallDisplacement = 0;
	}
}

void Player::Jump()
{
	if (isGrounded == false)//�p�G�S�b�a�W(���D��)
	{
		if (jumpDisplacement > -5 * originJumpDisplacement)//���D�Y�ƥ��p��̤p��
			jumpDisplacement--;//�첾�q�H�ۮɶ�����

		if (jumpDisplacement >= 0)//���W��
		{
			this->y -= jumpDisplacement;//����y�b�y��
			Map::MoveScreenTopLeft(0, -jumpDisplacement);//�ù����W����ۨ��Ⲿ��
		}
		if (jumpDisplacement < 0)//���U��
		{
			if (!Map::HasObject(this->x, this->y + this->height))//�U��S���a�O
			{
				this->y -= jumpDisplacement;//����y�b�y��
				Map::MoveScreenTopLeft(0, -jumpDisplacement);//�ù����W����ۨ��Ⲿ��
			}
			else
			{
				isGrounded = true;//�I��a�O
				jumpDisplacement = originJumpDisplacement;//���D�첾�q�٭�
			}
		}
	}
}