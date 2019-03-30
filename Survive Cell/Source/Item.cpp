#include "StdAfx.h"
#include "Item.h"

Item::Item()
{
	tag = "Item";
}

Item::Item(string tag, int x, int y, int width, int height, int pictureID) :GameObject(tag, x, y, width, height, pictureID)
{
	layer = GameSystem::LAYER::LAYER_ITEM;

	while (Map::HasObject(this->x, this->y + height))//若道具位在地板中
		this->y--;//將道具往上移至地板外
}

void Item::Picked()
{
	Dead();
}

void Item::Dead()
{
	GameSystem::DeleteGameObject(this);//刪除此物件
}
