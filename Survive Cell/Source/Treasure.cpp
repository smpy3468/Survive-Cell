#include"StdAfx.h"
#include "Treasure.h"
Treasure::Treasure(string tag, int x, int y, int width, int height):Item(tag,x, y, width, height)
{	
	SetY(y);
	LoadAni();
	//LoadBitMap(".\\res\\Treasure_Idle.bmp");
}

void Treasure::LoadAni()
{

	char* aniIdle[1] = { ".\\res\\Treasure_Idle.bmp" };
	AddAniBitMaps(aniIdle, ANI_IDLE, 1);
};
