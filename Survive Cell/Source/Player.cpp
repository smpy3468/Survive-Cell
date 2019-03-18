#include "StdAfx.h"
#include "GameSystem.h"
#include "Player.h"
#include "Monster.h"
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

	originJumpDisplacement = 15;
	jumpDisplacement = originJumpDisplacement;

	attackRange = 10;
	attackDamage = 5;

	//isMoveUp = false;
	//isMoveDown = false;
	isMoveLeft = false;
	isMoveRight = false;

	isJumpKeyDown = false;
	isJump = false;
	isFall = false;
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
		else if (dx < 0 && this->x < Map::GetSX() + SIZE_X / 2)
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
	this->isJumpKeyDown = isJump;
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
		if (this->x > 0)
			Move(-moveSpeed, 0);
	}

	if (this->isMoveRight)
	{
		if (this->x + this->width < Map::GetWorldSizeX())
			Move(moveSpeed, 0);
	}

	if (this->isJumpKeyDown)//�p�G���U���D
	{
		if (isGrounded)//�p�G�b�a�W
		{
			isJump = true;//���b���D
			isGrounded = false;//�S�b�a�W
		}
	}

	Jump();//���D
	Fall();//�U��
}

void Player::Fall()
{
	if (!Map::HasObject(this->x, this->y + this->height + fallDisplacement))//�p�G�}�U�S�F��
	{
		if (isJump == false)//�S�b���D
		{
			isFall = true;//���b�U��
			isGrounded = false;//���b�a�W
			fallDisplacement++;
			Move(0, fallDisplacement);
		}
	}
	else
	{
		fallDisplacement = 0;
		isGrounded = true;//�b�a�W
		isFall = false;//�S�b�U��
	}
}

void Player::Jump()
{
	if (isGrounded == false && isFall == false)//�p�G�S�b�a�W�B�S�b�U��
	{
		jumpDisplacement--;//�첾�q�H�ۮɶ�����

		if (jumpDisplacement >= 0)//���W��
		{
			Move(0, -jumpDisplacement);
		}
		else//���U��
		{
			isJump = false;
			jumpDisplacement = originJumpDisplacement;//���D�첾�q�٭�
		}
	}
}

void Player::Attack()
{
	vector<Monster*> monsters = GameSystem::GetGameObjectsWithTag<Monster>("Monster");

	for (auto& i : monsters)//��Ǫ�����
	{
		if (i->GetX() > this->x - attackRange && i->GetX() < this->x + attackRange 
			&& i->GetY() + i->GetHeight() > this->y && i->GetY() < this->y + this->height)//�Ǫ��b�����d��
		{
			i->DecreaseHP(attackDamage);
		}
	}
}
