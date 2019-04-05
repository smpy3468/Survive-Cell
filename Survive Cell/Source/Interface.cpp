#include "StdAfx.h"
#include"Interface.h"

Interface::Interface(string tag, int x, int y, int width, int height, int pictureID) :GameObject(tag, x, y, width, height, pictureID) {
	tag = "Interface";
}

//-----------------PROTECTED-----------------------------//
void Interface::AddAniBitMaps(char * pic[], int aniType, int picCount)
{
	for (int i = 0; i < picCount; i++)
	{
		AddAniBitMap(pic[i], aniType);
	}
}

void Interface::AddAniBitMap(char* pic, int aniType)
{
	while ((int)ani.size() <= aniType)//vector的大小不夠大
		ani.push_back(new CAnimation);//增加大小

	ani[aniType]->AddBitmap(pic, RGB(255, 255, 255));
}

void Interface::LoadAni(){}

