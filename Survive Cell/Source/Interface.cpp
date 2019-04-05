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
	while ((int)ani.size() <= aniType)//vector���j�p�����j
		ani.push_back(new CAnimation);//�W�[�j�p

	ani[aniType]->AddBitmap(pic, RGB(255, 255, 255));
}

void Interface::LoadAni(){}

