#include "StdAfx.h"
#include "Boss.h"

Boss::Boss()
{

}

Boss::~Boss()
{

}

Boss::Boss(string tag, int x, int y, int width, int height) :Monster(tag, x, y, width, height)
{
	tag = "Monster";

	HP = 10000;
	aniSpeed = 10;
	moveSpeed = 3;

	attackRange = 100;
	attackDamage = 50;

	LoadAni();
}

void Boss::Act()
{
	unsigned seed = (unsigned)time(NULL);
	srand(seed);

	if (currentState == STATE_IDLE)//�R��A�ɤ~���ʧ@
		currentState = rand() % STATE_LENGTH;//�ثe���A�H������

	switch (currentState)//�ھڪ��A�����P�ʧ@
	{
	case STATE_IDLE://�R��
		break;
	case STATE_MOVE://����
		faceLR = rand() % 2;

		if (faceLR == FACE_LEFT)
		{
			Move(-moveSpeed, 0);
		}
		else
		{
			Move(moveSpeed, 0);
		}

		if (ani[currentAni]->IsEnd())
			currentState = STATE_IDLE;//���ʰʵe�����A�N�^���R��A

		break;
	case STATE_ATTACK://����
		Attack();
		break;
	case STATE_JUMP:
		Jump();
		break;
	}

	Fall(fallDisplacement);
}

void Boss::Fall(int perDisplacement)
{
	if (CanMoveDown(fallDisplacement))//�p�G�}�U�S�F��
	{
		fallDisplacement++;
		Move(0, fallDisplacement);
	}
	else
	{
		while (CanMoveDown(1))//�A�~��ΤU���첾�q�U���A�N�|�d�i�a�O�A�ҥH�@���V�U�첾1�i��L��0
			Move(0, 1);
		fallDisplacement = 0;

	}
}

void Boss::Attack()
{
	if (ani[currentAni]->IsEnd())//�����P�w�u�|�X�{�@���A�]�������ʵe�����~����
	{
		int leftEdge = 0, rightEdge = 0;
		if (faceLR == FACE_LEFT)//�]�w�V�����
		{
			leftEdge = this->x - attackRange;
			rightEdge = this->x + this->width / 2;
		}
		else//�]�w�V�k���
		{
			leftEdge = this->x + this->width / 2;
			rightEdge = this->x + this->width + attackRange;
		}

		if (player->GetX() + player->GetWidth() / 2 > leftEdge
			&& player->GetX() + player->GetWidth() / 2 < rightEdge
			&& player->GetY() + player->GetHeight() > this->y
			&& player->GetY() < this->y + this->height)//���a�b�d��
		{
			player->DecreaseHP(attackDamage);//�������a
		}

		currentState = STATE_IDLE;//�^���R��A
	}
}

void Boss::Jump()
{
	if (jumpDisplacement-- > 0)//���D�첾�q�H�ɶ�����
	{
		Move(0, -jumpDisplacement);//�V�W�첾
	}
	else
	{
		jumpDisplacement = originJumpDisplacement;//���D�첾�q�٭�

		if (player->GetX() + player->GetWidth() > this->x - attackRange
			&& player->GetX() < this->x + this->width + attackRange
			&& player->GetY() + player->GetHeight() > this->y + this->height / 2
			&& player->GetY() < this->y + this->height)//���a�b�d��
		{
			player->DecreaseHP(attackDamage);//�������a
		}

		currentState = STATE_IDLE;//�^���R��A
	}

	ani[currentAni]->OnMove();
}

void Boss::Move(int dx, int dy)
{
	this->x += dx;
	this->y += dy;
}

void Boss::NearSlash()
{
}

void Boss::JumpBack()
{
}

void Boss::JumpFront()
{
}

void Boss::FarSlash()
{
}

void Boss::InstantDeath()
{
}

void Boss::ShowBitMap()
{
	switch (currentState)
	{
	case STATE_IDLE://�R��
		currentAni = ANI_IDLE;
		ani[currentAni]->OnMove();
		break;

	case STATE_MOVE://����
		if (faceLR == FACE_LEFT)
		{
			currentAni = ANI_LEFT;
		}
		else
		{
			currentAni = ANI_RIGHT;
		}
		ani[currentAni]->OnMove();
		break;

	case STATE_ATTACK://����
		if (faceLR == FACE_LEFT)
		{
			currentAni = ANI_ATTACK_LEFT;
		}
		else
		{
			currentAni = ANI_ATTACK_RIGHT;
		}
		ani[currentAni]->OnMove();

		break;

	case STATE_JUMP://���D
		currentAni = ANI_JUMP;
		break;
	}

	GameSystem::ShowText(to_string(GetHP()), x - Map::GetSX(), y - Map::GetSY() - 30, x + width - Map::GetSX(), y + height - Map::GetSY(), GameSystem::ALIGN_CENTER, GameSystem::ALIGN_TOP, 16, RGB(0, 0, 0));
	ani[currentAni]->OnShow();
}

void Boss::LoadAni()
{
	char* aniIdle[4] = { ".\\res\\boss_idle_0.bmp", ".\\res\\boss_idle_1.bmp", ".\\res\\boss_idle_2.bmp", ".\\res\\boss_idle_3.bmp" };
	AddAniBitMaps(aniIdle, ANI::ANI_IDLE, 4, aniSpeed);

	char* aniLeft[4] = { ".\\res\\boss_left_0.bmp", ".\\res\\boss_left_1.bmp", ".\\res\\boss_left_2.bmp", ".\\res\\boss_left_3.bmp" };
	AddAniBitMaps(aniLeft, ANI_LEFT, 4, aniSpeed);

	char* aniRight[4] = { ".\\res\\boss_right_0.bmp", ".\\res\\boss_right_1.bmp", ".\\res\\boss_right_2.bmp", ".\\res\\boss_right_3.bmp" };
	AddAniBitMaps(aniRight, ANI_RIGHT, 4, aniSpeed);

	char* aniAttackLeft[3] = { ".\\res\\boss_attack_left_0.bmp", ".\\res\\boss_attack_left_1.bmp", ".\\res\\boss_attack_left_2.bmp" };
	AddAniBitMaps(aniAttackLeft, ANI_ATTACK_LEFT, 3, aniSpeed);

	char* aniAttackRight[3] = { ".\\res\\boss_attack_right_0.bmp", ".\\res\\boss_attack_right_1.bmp", ".\\res\\boss_attack_right_2.bmp" };
	AddAniBitMaps(aniAttackRight, ANI_ATTACK_RIGHT, 3, aniSpeed);

	char* aniJump[3] = { ".\\res\\boss_jump_0.bmp", ".\\res\\boss_jump_1.bmp", ".\\res\\boss_jump_2.bmp" };
	AddAniBitMaps(aniJump, ANI_JUMP, 3, aniSpeed);
}
