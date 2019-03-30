#include "StdAfx.h"
#include "Item.h"

Item::Item()
{
	tag = "Item";
}

Item::Item(string tag, int x, int y, int width, int height, int pictureID) :GameObject(tag, x, y, width, height, pictureID)
{
	layer = GameSystem::LAYER_ITEM;
}

void Item::Picked()
{
	Dead();
}

void Item::Dead()
{
	GameSystem::DeleteGameObject(this);//刪除此物件
}
