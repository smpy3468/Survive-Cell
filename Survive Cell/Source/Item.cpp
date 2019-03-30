#include "StdAfx.h"
#include "Item.h"

Item::Item()
{
	tag = "Item";
}

Item::Item(string tag, int x, int y, int width, int height, int pictureID) :GameObject(tag, x, y, width, height, pictureID)
{
	layer = GameSystem::LAYER::LAYER_ITEM;

	while (Map::HasObject(this->x, this->y + height))//�Y�D���b�a�O��
		this->y--;//�N�D�㩹�W���ܦa�O�~
}

void Item::Picked()
{
	Dead();
}

void Item::Dead()
{
	GameSystem::DeleteGameObject(this);//�R��������
}
