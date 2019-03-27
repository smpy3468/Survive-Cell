#include "StdAfx.h"
#include "GameSystem.h"
#include "Player.h"
#include "Monster.h"
#include "Map.h"
#include "Item.h"

Player::Player()
{
	tag = "Player";
}

Player::Player(string tag, int x, int y, int width, int height, int pictureID) :Character(tag, x, y, width, height, pictureID)
{
	tag = "Player";

	maxHP = 10;
	HP = maxHP;

	originMoveSpeed = 5;
	moveSpeed = originMoveSpeed;

	fallDisplacement = 0;

	originJumpDisplacement = 15;
	jumpDisplacement = originJumpDisplacement;

	attackRange = 10;
	attackDamage = 5;

	isMoveLeft = false;
	isMoveRight = false;

	isJumpKeyDown = false;
	isJump = false;
	isFall = false;
	isGrounded = false;

	currentAni = ANI_IDLE;

	LoadAni();
}

void Player::Move(int dx, int dy)
{
	if (!Map::HasObject(x + dx, y + dy))//如果該座標沒有物件
	{
		if (dx > 0)
		{
			if (!Map::HasObject(x + width + dx, y) && !Map::HasObject(x + width + dx, y + height / 2) && !Map::HasObject(x + width + dx, y + height - 1))//右邊沒東西
			{
				this->x += dx;//玩家x移動
			}
		}
		else if (dx < 0)
		{
			if (!Map::HasObject(x + dx, y) && !Map::HasObject(x + dx, y + height / 2) && !Map::HasObject(x + dx, y + height - 1))//左邊沒東西
			{
				this->x += dx;//玩家x移動
			}
		}
	
		this->y += dy;//玩家y移動

		if (dx > 0 && this->x + this->width / 2 >= Map::GetSX() + SIZE_X / 2)
			Map::MoveScreenTopLeft(dx, 0);//螢幕移動
		else if (dx < 0 && this->x + this->width / 2 < Map::GetSX() + SIZE_X / 2)
			Map::MoveScreenTopLeft(dx, 0);//螢幕移動

		if (dy > 0 && this->y + this->height / 2 >= Map::GetSY() + SIZE_Y * 3 / 4)
			Map::MoveScreenTopLeft(0, dy);//螢幕移動
		else if (dy < 0 && this->y + this->height / 2 < Map::GetSY() + SIZE_Y / 4)
			Map::MoveScreenTopLeft(0, dy);//螢幕移動
	}
}

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

	if (isJump)
		Jump();//跳躍
	else
		Fall();//下降
}

void Player::Fall()
{
	//如果腳下沒東西
	if (!Map::HasObject(this->x + this->width / 10, this->y + this->height + fallDisplacement)//人物左邊的下方
		&& !Map::HasObject(this->x + this->width - this->width / 10, this->y + this->height + fallDisplacement)//人物右邊的下方
		&& !Map::HasObject(this->x + this->width / 2, this->y + this->height + fallDisplacement))//人物中間的下方													 
	{
		isFall = true;//正在下降
		isGrounded = false;//不在地上
		fallDisplacement++;
		Move(0, fallDisplacement);
	}
	else
	{
		while (!Map::HasObject(this->x + this->width / 10, this->y + this->height + 1)
			&& !Map::HasObject(this->x + this->width - this->width / 10, this->y + this->height + 1)//人物右邊的下方
			&& !Map::HasObject(this->x + this->width / 2, this->y + this->height + 1))
			Move(0,1);

		fallDisplacement = 0;
		isGrounded = true;//在地上
		isFall = false;//沒在下降

		if (currentAni == ANI_JUMP_LEFT)//將跳躍動畫還原
			currentAni = ANI_LEFT;
		else if (currentAni == ANI_JUMP_RIGHT)
			currentAni = ANI_RIGHT;
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
			isFall = true;
			jumpDisplacement = originJumpDisplacement;//跳躍位移量還原
		}
	}
}

void Player::Interact()
{
	for (auto& i : GameSystem::GetAllGameObject())//對物件互動
	{
		if (i->GetTag() == "Item" || i->GetTag() == "Potion")//是物品
		{
			if(i->GetX() > this->x && i->GetX() < this->x + this->width
				&& i->GetY() > this->y && i->GetY() < this->y + this->height)
				static_cast<Item*>(i)->Picked();
		}
	}
}

void Player::Attack()
{
	vector<Monster*> monsters = GameSystem::GetGameObjectsWithTag<Monster>("Monster");

	for (auto& i : monsters)//對怪物攻擊
	{
		if (i->GetX() + i->GetWidth() > this->x - attackRange && i->GetX() < this->x + this->width + attackRange
			&& i->GetY() + i->GetHeight() > this->y && i->GetY() < this->y + this->height)//怪物在攻擊範圍內
		{
			i->DecreaseHP(attackDamage);
		}
	}
}

void Player::ShowBitMap()
{
	if (isJump || isFall)//跳躍動畫
	{
		if (currentAni == ANI_LEFT)
		{
			currentAni = ANI_JUMP_LEFT;
		}
		else if (currentAni == ANI_RIGHT)
		{
			currentAni = ANI_JUMP_RIGHT;
		}
		else if (currentAni == ANI_JUMP_LEFT && isMoveRight)//面向左邊跳躍時按下右鍵要面向右邊
		{
			currentAni = ANI_JUMP_RIGHT;
		}
		else if (currentAni == ANI_JUMP_RIGHT && isMoveLeft)//面向右邊跳躍時按下左鍵要面向左邊
		{
			currentAni = ANI_JUMP_LEFT;
		}
	}
	else if (isMoveLeft)//左移動畫
	{
		currentAni = ANI_LEFT;
		ani[ANI_LEFT]->OnMove();

	}
	else if (isMoveRight)//右移動畫
	{
		currentAni = ANI_RIGHT;
		ani[ANI_RIGHT]->OnMove();
	}
	else
	{
		for (auto& i : ani)
		{
			i->Reset();//重置所有動畫
		}
	}

	ani[currentAni]->OnShow();
}

void Player::Dead()
{


	GameSystem::DeleteGameObject(this);
}

void Player::LoadAni()
{
	char* aniIdle[1] = { ".\\res\\player_idle.bmp" };
	AddAniBitMaps(aniIdle, ANI_IDLE, 1);

	char* aniLeft[4] = { ".\\res\\player_left_0.bmp", ".\\res\\player_left_1.bmp", ".\\res\\player_left_2.bmp", ".\\res\\player_left_3.bmp" };
	AddAniBitMaps(aniLeft, ANI_LEFT, 4);

	char* aniRight[4] = { ".\\res\\player_right_0.bmp", ".\\res\\player_right_1.bmp", ".\\res\\player_right_2.bmp", ".\\res\\player_right_3.bmp" };
	AddAniBitMaps(aniRight, ANI_RIGHT, 4);

	char* aniJumpLeft = ".\\res\\player_jump_left.bmp";
	AddAniBitMap(aniJumpLeft, ANI_JUMP_LEFT);

	char* aniJumpRight = ".\\res\\player_jump_right.bmp";
	AddAniBitMap(aniJumpRight, ANI_JUMP_RIGHT);
}
