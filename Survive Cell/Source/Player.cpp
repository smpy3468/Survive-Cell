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
	if (!Map::HasObject(x + dx, y + dy))//如果該座標沒有物件
	{
		this->x += dx;//玩家x移動
		this->y += dy;//玩家y移動

		if (dx > 0 && this->x >= Map::GetSX() + SIZE_X / 2)
			Map::MoveScreenTopLeft(dx, 0);//螢幕移動
		else if (dx < 0 && this->x < Map::GetSX() + SIZE_X / 2)
			Map::MoveScreenTopLeft(dx, 0);//螢幕移動

		if (dy > 0 && this->y >= Map::GetSY() + SIZE_Y * 3 / 4)
			Map::MoveScreenTopLeft(0, dy);//螢幕移動
		else if (dy < 0 && this->y < Map::GetSY() + SIZE_Y / 4)
			Map::MoveScreenTopLeft(0, dy);//螢幕移動
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

void Player::Move()//移動方向
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

	if (this->isJumpKeyDown)//如果按下跳躍
	{
		if (isGrounded)//如果在地上
		{
			isJump = true;//正在跳躍
			isGrounded = false;//沒在地上
		}
	}

	Jump();//跳躍
	Fall();//下降
}

void Player::Fall()
{
	if (!Map::HasObject(this->x, this->y + this->height + fallDisplacement))//如果腳下沒東西
	{
		if (isJump == false)//沒在跳躍
		{
			isFall = true;//正在下降
			isGrounded = false;//不在地上
			fallDisplacement++;
			Move(0, fallDisplacement);
		}
	}
	else
	{
		fallDisplacement = 0;
		isGrounded = true;//在地上
		isFall = false;//沒在下降
	}
}

void Player::Jump()
{
	if (isGrounded == false && isFall == false)//如果沒在地上且沒在下降
	{
		jumpDisplacement--;//位移量隨著時間改變

		if (jumpDisplacement >= 0)//往上升
		{
			Move(0, -jumpDisplacement);
		}
		else//往下降
		{
			isJump = false;
			jumpDisplacement = originJumpDisplacement;//跳躍位移量還原
		}
	}
}

void Player::Attack()
{
	vector<Monster*> monsters = GameSystem::GetGameObjectsWithTag<Monster>("Monster");

	for (auto& i : monsters)//對怪物攻擊
	{
		if (i->GetX() > this->x - attackRange && i->GetX() < this->x + attackRange 
			&& i->GetY() + i->GetHeight() > this->y && i->GetY() < this->y + this->height)//怪物在攻擊範圍內
		{
			i->DecreaseHP(attackDamage);
		}
	}
}
