#include"StdAfx.h"
#include"Arrow.h"

Arrow::Arrow(string tag, int x, int y, int width, int height) :Effect(tag, x, y, width, height) {
	tag = "Arrow";
	LoadAni();
	SetBitMapPosition();
	currentAni = ANI_ARROW_IDLE;
	this->direction = ANI_ATTACK_LEFT;
	LoadBitMap(".\\res\\arrow.bmp");
	initX = x + 300;
	initY = y + 20;
	dX = 25;
	dY =  0;
}

Arrow::Arrow(string tag, int x, int y, int width, int height, int attackRange, int direction) :Effect(tag, x, y, width, height) {
	tag = "Arrow";
	LoadAni();
	SetBitMapPosition();
	currentAni = ANI_ARROW_IDLE;
	LoadBitMap(".\\res\\arrow.bmp");
	this->initX = x;
	this->initY = y;
	this->direction = direction;
	this->dX = 25;
	this->dY = 0;
}

Arrow::~Arrow()
{
}



void Arrow::ShowBitMap() {
	Fall();
	if (direction == ANI_ATTACK_LEFT&& CanMoveLeft(dX)&& CanMoveDown(dY) && isHit == false)
	{
		currentAni = ANI_ARROW_LEFT;
		x = x - dX;
		y = y + dY;
		SetBitMapPosition();
		ani[currentAni]->OnShow();
		EffectAttackMonster(player->GetAttackDamage());
	}
	else if (direction == ANI_ATTACK_RIGHT && CanMoveRight(dX) && CanMoveDown(dY) && isHit == false)
	{
		currentAni = ANI_ARROW_RIGHT;
		x = x + dX;
		y = y + dY;
		SetBitMapPosition();
		ani[currentAni]->OnShow();
		EffectAttackMonster(player->GetAttackDamage());
	}
	else if((CanMoveRight(dX) || CanMoveDown(dY))){
		Dead();
	}

}

void Arrow::LoadAni() {
	char* aniArrow_idle[1] = { ".\\res\\arrow.bmp" };
	AddAniBitMaps(aniArrow_idle, ANI_ARROW_IDLE, 1);

	char* aniArrow_left[3] = { ".\\res\\arrow_left.bmp", ".\\res\\arrow_left.bmp", ".\\res\\arrow_left.bmp" };
	AddAniBitMaps(aniArrow_left, ANI_ARROW_LEFT, 3);

	char* aniArrow_right[3] = { ".\\res\\arrow_right.bmp", ".\\res\\arrow_right.bmp",".\\res\\arrow_right.bmp" };
	AddAniBitMaps(aniArrow_right, ANI_ARROW_RIGHT, 3);
}

void Arrow :: Fall()
{
	if (x - initX >= 250)		//如果箭已經飛了一段距離(250)就開始下降
		dY = dY + 1;
}