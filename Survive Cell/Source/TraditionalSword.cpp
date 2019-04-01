#include"StdAfx.h"
#include "TraditionalSword.h"

TraditionalSword::TraditionalSword() {
	tag = "TraditionalSword";
}



TraditionalSword::TraditionalSword(string tag, int x, int y, int width, int height, int pictureID):Item(tag, x, y, width, height, pictureID) {
	tag = "TraditionalSword";
	attackDamage = 10;
	attackRange = 10;
	defense = 2;
	LoadAni();
}

void TraditionalSword::LoadAni() {
	char* aniIdle[1] = { ".\\res\\sword_01d.bmp" };
	AddAniBitMaps(aniIdle, ANI_IDLE, 1);
}

void TraditionalSword::ShowBitMap() {
	ani[currentAni]->OnShow();
}