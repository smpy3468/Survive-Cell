#include"StdAfx.h"
#include"Arrow.h"

Arrow::Arrow(string tag, int x, int y, int width, int height) :Effect(tag, x, y, width, height) {
	tag = "Arrow";
	LoadAni();
	SetBitMapPosition();
	currentAni = ANI_ARROW_IDLE;
	this->direction = ANI_ATTACK_LEFT;
	LoadBitMap(".\\res\\arrow.bmp");
	targetX = x + 300;
	targetY = y + 20;
	dX = 25;
	dY = 5;
}

Arrow::Arrow(string tag, int x, int y, int width, int height, int attackRange, int direction) :Effect(tag, x, y, width, height) {
	tag = "Arrow";
	LoadAni();
	SetBitMapPosition();
	currentAni = ANI_ARROW_IDLE;
	LoadBitMap(".\\res\\arrow.bmp");
	this->targetX = 0;
	this->targetY = 0;
	this->direction = direction;
	this->dX = 25;
	this->dY = 5;
}

Arrow::~Arrow()
{
}

void Arrow::ShowBitMap() {
	if (direction == ANI_ATTACK_LEFT&& CanMoveLeft(dX)&& CanMoveDown(dY))
	{
		currentAni = ANI_ARROW_LEFT;
		x = x - dX;
		y = y + dY;
		SetBitMapPosition();
		ani[currentAni]->OnShow();
	}
	else if (direction == ANI_ATTACK_RIGHT && CanMoveRight(dX) && CanMoveDown(dY))
	{
		currentAni = ANI_ARROW_RIGHT;
		x = x + dX;
		y = y + dY;
		SetBitMapPosition();
		ani[currentAni]->OnShow();
	}
	else if((x >= targetX && y >= targetY)|| (CanMoveRight(dX) || CanMoveDown(dY))){
		Dead();
	}
	//SetBitMapPosition();
	//ani[currentAni]->OnShow();
	EffectAttackMonster(player->GetAttackDamage());
}

void Arrow::LoadAni() {
	char* aniArrow_idle[1] = { ".\\res\\arrow.bmp" };
	AddAniBitMaps(aniArrow_idle, ANI_ARROW_IDLE, 1);

	char* aniArrow_left[3] = { ".\\res\\arrow.bmp", ".\\res\\arrow.bmp", ".\\res\\arrow.bmp" };
	AddAniBitMaps(aniArrow_left, ANI_ARROW_LEFT, 3);

	char* aniArrow_right[3] = { ".\\res\\arrow.bmp", ".\\res\\arrow.bmp",".\\res\\arrow.bmp" };
	AddAniBitMaps(aniArrow_right, ANI_ARROW_RIGHT, 3);
}
