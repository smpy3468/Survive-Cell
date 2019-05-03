#include "StdAfx.h"
#include "Boss.h"

Boss::Boss(string tag, int x, int y, int width, int height) :Monster(tag, x, y, width, height)
{
	tag = "Monster";
	HP = 10000;
	LoadAni();
}

void Boss::Act()
{
	if (faceLR == FACE_LEFT)
	{
		Move(-1, 0);
	}
	else
	{
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
	ani[currentAni]->OnShow();
}

void Boss::LoadAni()
{
	char* aniBoss = ".\\res\\boss.bmp";
	AddAniBitMap(aniBoss, ANI::ANI_IDLE);
}
