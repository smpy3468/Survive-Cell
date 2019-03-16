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
		this->x += dx;//���ax����
		this->y += dy;//���ay����
		
		if (dx > 0 && this->x >= Map::GetSX() + SIZE_X / 2)
			Map::MoveScreenTopLeft(dx, 0);//�ù�����
		else if(dx < 0 && this->x < Map::GetSX() + SIZE_X / 2)
			Map::MoveScreenTopLeft(dx, 0);//�ù�����

		if (dy > 0 && this->y >= Map::GetSY() + SIZE_Y * 3 / 4)
			Map::MoveScreenTopLeft(0, dy);//�ù�����
		else if (dy < 0 && this->y < Map::GetSY() + SIZE_Y / 4)
			Map::MoveScreenTopLeft(0, dy);//�ù�����
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
		if(this->x > 0)
			Move(-moveSpeed, 0);
	}

	if (this->isMoveRight)
	{
		if(this->x + this->width < Map::GetWorldSizeX())
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
	if (!Map::HasObject(this->x, this->y + this->height + fallDisplacement))//�p�G�}�U�S�F��
	{
		if (isGrounded == true)//�쥻�b�a�W
		{
			fallDisplacement++;
			Move(0, fallDisplacement);
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
			Move(0, -jumpDisplacement);
		}
		else if (jumpDisplacement < 0)//���U��
		{
			if (!Map::HasObject(this->x, this->y + this->height))//�U��S���a�O
			{
				Move(0, -jumpDisplacement);
			}
			else
			{
				isGrounded = true;//�I��a�O
				jumpDisplacement = originJumpDisplacement;//���D�첾�q�٭�
			}
		}
	}
}