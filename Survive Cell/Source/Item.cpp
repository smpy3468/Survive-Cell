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
	while (Map::HasObject(this->x, this->y + height))//�Y�D���b�a�O��
		this->y--;//�N�D�㩹�W���ܦa�O�~
	while (!Map::HasObject(this->x, this->y + height + 1))//�Y�D��b�Ť�
		this->y++;//�N�D�㩹�U���ܦa�O�~
	perDisplacement =1;
}

Item::Item(string tag, int x, int y, int width, int height) :GameObject(tag, x, y, width, height)
{
	tag = "Item";
	layer = GameSystem::LAYER::LAYER_ITEM;
	while (Map::HasObject(this->x, this->y + height))//�Y�D���b�a�O��
		this->y--;//�N�D�㩹�W���ܦa�O�~
	//while (!Map::HasObject(this->x, this->y + height + 1))//�Y�D��b�Ť�
		//this->y++;//�N�D�㩹�U���ܦa�O�~

	ani.push_back(new CAnimation());//�[�J�@�Ӱʵe
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
	while ((int)ani.size() <= aniType)//vector���j�p�����j
		ani.push_back(new CAnimation);//�W�[�j�p

	ani[aniType]->AddBitmap(pic, RGB(255, 255, 255));
}

void Item::LoadAni(){}

void Item::ShowBitMap() {
	ani[currentAni]->OnShow();
}
void Item::Fall(int perDisplacement)
{	
	int k = GetY();
	if (CanMoveDown(perDisplacement))//�p�G�}�U�S�F��
	{
		SetY(GetY() +perDisplacement);
		this->perDisplacement++;
	}
	else
	{
		while (CanMoveDown(1))//�A�~��ΤU���첾�q�U���A�N�|�d�i�a�O�A�ҥH�@���V�U�첾1�i��L��0
			SetY(GetY()+1);
	}
}

bool Item::CanMoveDown(int perDisplacement)
{
	bool canMoveDown = true;
	for (int i = x; i < x + width; i++)
	{
		if (Map::HasObject(i, y + height + perDisplacement))//�U�����F��
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
	GameSystem::DeleteGameObject(this);//�R��������
}