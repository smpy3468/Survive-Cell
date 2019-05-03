#include "StdAfx.h"
#include "Boss.h"

Boss::Boss(string tag, int x, int y, int width, int height) :Monster(tag, x, y, width, height)
{
	tag = "Monster";
	HP = 10000;
	aniSpeed = 10;
	LoadAni();
}

void Boss::Act()
{
	if (faceLR == FACE_LEFT)
	{
		currentAni = ANI_LEFT;
		Move(-1, 0);
	}
	else
	{
		currentAni = ANI_RIGHT;
		Move(1, 0);
	}

	Attack();
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
	GameSystem::ShowText(to_string(GetHP()), x - Map::GetSX(), y - Map::GetSY() - 30, x + width - Map::GetSX(), y + height - Map::GetSY(), "CENTER", "TOP", 16, RGB(0, 0, 0));
	ani[currentAni]->OnMove();
	ani[currentAni]->OnShow();
}

void Boss::LoadAni()
{
	char* aniIdle = ".\\res\\boss_idle.bmp";
	AddAniBitMap(aniIdle, ANI::ANI_IDLE);

	char* aniLeft[2] = {".\\res\\boss_left_0.bmp", ".\\res\\boss_left_1.bmp" };
	AddAniBitMaps(aniLeft,ANI_LEFT,2,aniSpeed);

	char* aniRight[2] = { ".\\res\\boss_right_0.bmp", ".\\res\\boss_right_1.bmp" };
	AddAniBitMaps(aniRight, ANI_RIGHT, 2, aniSpeed);
}
