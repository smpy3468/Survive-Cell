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
	isMoveUp = false;
	isMoveDown = false;
	isMoveLeft = false;
	isMoveRight = false;
}

void Player::Move(int dx, int dy)
{
	if (!Map::HasObject(x + dx, y + dy))//�p�G�Ӯy�ШS������
	{
		GameSystem::MoveScreenTopLeft(dx, dy);//�ù�����
		this->x += dx;//���ax����
		this->y += dy;//���ay����
	}
}

void Player::SetIsMoveUp(bool isMoveUp)
{
	this->isMoveUp = isMoveUp;
}

void Player::SetIsMoveDown(bool isMoveDown)
{
	this->isMoveDown = isMoveDown;
}

void Player::SetIsMoveLeft(bool isMoveLeft)
{
	this->isMoveLeft = isMoveLeft;
}

void Player::SetIsMoveRight(bool isMoveRight)
{
	this->isMoveRight = isMoveRight;
}

void Player::Move()//���ʤ�V
{
	if (this->isMoveUp)
	{
		Move(0, -moveSpeed);
	}

	if (this->isMoveDown)
	{
		Move(0, moveSpeed);
	}

	if (this->isMoveLeft)
	{
		Move(-moveSpeed, 0);
	}

	if (this->isMoveRight)
	{
		Move(moveSpeed, 0);
	}
}
