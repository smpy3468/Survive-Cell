#include "StdAfx.h"
#include "Boss.h"

Boss::Boss(string tag, int x, int y, int width, int height) :Monster(tag, x, y, width, height)
{
	tag = "Monster";
	HP = 10000;
	aniSpeed = 10;
	moveSpeed = 3;
	LoadAni();
}

void Boss::Act()
{
	unsigned seed = (unsigned)time(NULL);
	srand(seed);
	currentState = rand() % 3;//目前狀態

	switch (currentState)//根據狀態做不同動作
	{
	case STATE_IDLE://靜止
		break;
	case STATE_MOVE://移動
		faceLR = rand() % 2;

		if (faceLR == FACE_LEFT)
		{
			Move(-moveSpeed, 0);
		}
		else
		{
			Move(moveSpeed, 0);
		}
		break;
	case STATE_ATTACK://攻擊
		Attack();
		break;
	}

	Fall(fallDisplacement);
}

void Boss::Attack()
{

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
	case STATE_IDLE://靜止
		currentAni = ANI_IDLE;
		break;
	case STATE_MOVE://移動
		if (faceLR == FACE_LEFT)
		{
			currentAni = ANI_LEFT;
		}
		else
		{
			currentAni = ANI_RIGHT;
		}
		break;
	case STATE_ATTACK://攻擊
		if (faceLR == FACE_LEFT)
		{
			currentAni = ANI_ATTACK_LEFT;
		}
		else
		{
			currentAni = ANI_ATTACK_RIGHT;
		}
		break;
	}

	GameSystem::ShowText(to_string(GetHP()), x - Map::GetSX(), y - Map::GetSY() - 30, x + width - Map::GetSX(), y + height - Map::GetSY(), "CENTER", "TOP", 16, RGB(0, 0, 0));
	ani[currentAni]->OnMove();
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
}
