#include "StdAfx.h"
#include "Item.h"

Item::Item()
{
	tag = "Item";
}

Item::~Item()
{
	for (unsigned int i = 0; i < ani.size(); i++)
	{
		delete ani[i];
	}
	ani.clear();
}

Item::Item(string tag, int x, int y, int width, int height, int pictureID) :GameObject(tag, x, y, width, height, pictureID)
{	
	tag = "Item";
	layer = GameSystem::LAYER::LAYER_ITEM;
	while (Map::HasObject(this->x, this->y + height))//若道具位在地板中
		this->y--;//將道具往上移至地板外
	while (!Map::HasObject(this->x, this->y + height + 1))//若道具在空中
		this->y++;//將道具往下移至地板外
	perDisplacement =1;
}

Item::Item(string tag, int x, int y, int width, int height) :GameObject(tag, x, y, width, height)
{
	tag = "Item";
	layer = GameSystem::LAYER::LAYER_ITEM;
	while (Map::HasObject(this->x, this->y + height))//若道具位在地板中
		this->y--;//將道具往上移至地板外
	//while (!Map::HasObject(this->x, this->y + height + 1))//若道具在空中
		//this->y++;//將道具往下移至地板外

	ani.push_back(new CAnimation());//加入一個動畫
	perDisplacement = -4;
}

void Item::AddAniBitMaps(char * pic[], int aniType, int picCount)
{
	for (int i = 0; i < picCount; i++)
	{
		AddAniBitMap(pic[i], aniType);
	}
}

void Item::AddAniBitMap(char* pic, int aniType)
{
	while ((int)ani.size() <= aniType)//vector的大小不夠大
		ani.push_back(new CAnimation);//增加大小

	ani[aniType]->AddBitmap(pic, RGB(255, 255, 255));
}

void Item::LoadAni(){}

void Item::ShowBitMap() {
	ani[currentAni]->OnShow();
}
void Item::Fall(int perDisplacement)
{	
	int k = GetY();
	if (CanMoveDown(perDisplacement))//如果腳下沒東西
	{
		SetY(GetY() +perDisplacement);
		this->perDisplacement++;
	}
	else
	{
		while (CanMoveDown(1))//再繼續用下降位移量下降，將會卡進地板，所以一次向下位移1進行微調0
			SetY(GetY()+1);
	}
}

bool Item::CanMoveDown(int perDisplacement)
{
	bool canMoveDown = true;
	for (int i = x; i < x + width; i++)
	{
		if (Map::HasObject(i, y + height + perDisplacement))//下面有東西
		{
			canMoveDown = false;
			return canMoveDown;
		}
	}
	return canMoveDown;
}

void Item::SetBitMapPosition()
{
	for (auto& i : ani)
	{
		i->SetTopLeft(this->x - Map::GetSX(), this->y - Map::GetSY());
	}
}

void Item::Act() 
{
	Fall(this->perDisplacement);
}

void Item::Picked()
{
	Dead();
}

void Item::Dead()
{
	GameSystem::DeleteGameObject(this);//刪除此物件
}