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
	if (!Map::HasObject(x + dx, y + dy))//�p�G�Ӯy�ШS������
	{
		this->x += dx;//���ax����
		this->y += dy;//���ay����

		if (dx > 0 && this->x + this->width / 2 >= Map::GetSX() + SIZE_X / 2)
			Map::MoveScreenTopLeft(dx, 0);//�ù�����
		else if (dx < 0 && this->x + this->width / 2 < Map::GetSX() + SIZE_X / 2)
			Map::MoveScreenTopLeft(dx, 0);//�ù�����

		if (dy > 0 && this->y + this->height / 2 >= Map::GetSY() + SIZE_Y * 3 / 4)
			Map::MoveScreenTopLeft(0, dy);//�ù�����
		else if (dy < 0 && this->y + this->height / 2 < Map::GetSY() + SIZE_Y / 4)
			Map::MoveScreenTopLeft(0, dy);//�ù�����
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

void Player::Move()//���ʤ�V
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

	if (this->isJumpKeyDown)//�p�G���U���D
	{
		if (isGrounded)//�p�G�b�a�W
		{
			isJump = true;//���b���D
			isGrounded = false;//�S�b�a�W
		}
	}

	if (isJump)
		Jump();//���D
	else
		Fall();//�U��
}

void Player::Fall()
{
	//�p�G�}�U�S�F��
	if (!Map::HasObject(this->x + this->width / 10, this->y + this->height + fallDisplacement)//�H�����䪺�U��
		&& !Map::HasObject(this->x + this->width - this->width / 10, this->y + this->height + fallDisplacement)//�H���k�䪺�U��
		&& !Map::HasObject(this->x + this->width / 2, this->y + this->height + fallDisplacement))//�H���������U��													 
	{
		isFall = true;//���b�U��
		isGrounded = false;//���b�a�W
		fallDisplacement++;
		Move(0, fallDisplacement);
	}
	else
	{
		fallDisplacement = 0;
		isGrounded = true;//�b�a�W
		isFall = false;//�S�b�U��

		if (currentAni == ANI_JUMP_LEFT)//�N���D�ʵe�٭�
			currentAni = ANI_LEFT;
		else if (currentAni == ANI_JUMP_RIGHT)
			currentAni = ANI_RIGHT;
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
			isFall = true;
			jumpDisplacement = originJumpDisplacement;//���D�첾�q�٭�
		}
	}
}

void Player::Interact()
{
	for (auto& i : GameSystem::GetAllGameObject())//�磌�󤬰�
	{
		if (i->GetTag() == "Item" || i->GetTag() == "Potion")//�O���~
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

	for (auto& i : monsters)//��Ǫ�����
	{
		if (i->GetX() + i->GetWidth() > this->x - attackRange && i->GetX() < this->x + this->width + attackRange
			&& i->GetY() + i->GetHeight() > this->y && i->GetY() < this->y + this->height)//�Ǫ��b�����d��
		{
			i->DecreaseHP(attackDamage);
		}
	}
}

void Player::ShowBitMap()
{
	if (isJump || isFall)//���D�ʵe
	{
		if (currentAni == ANI_LEFT)
		{
			currentAni = ANI_JUMP_LEFT;
		}
		else if (currentAni == ANI_RIGHT)
		{
			currentAni = ANI_JUMP_RIGHT;
		}
		else if (currentAni == ANI_JUMP_LEFT && isMoveRight)//���V������D�ɫ��U�k��n���V�k��
		{
			currentAni = ANI_JUMP_RIGHT;
		}
		else if (currentAni == ANI_JUMP_RIGHT && isMoveLeft)//���V�k����D�ɫ��U����n���V����
		{
			currentAni = ANI_JUMP_LEFT;
		}
	}
	else if (isMoveLeft)//�����ʵe
	{
		currentAni = ANI_LEFT;
		ani[ANI_LEFT]->OnMove();

	}
	else if (isMoveRight)//�k���ʵe
	{
		currentAni = ANI_RIGHT;
		ani[ANI_RIGHT]->OnMove();
	}
	else
	{
		for (auto& i : ani)
		{
			i->Reset();//���m�Ҧ��ʵe
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
