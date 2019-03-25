#include "StdAfx.h"
#include "Item.h"

Item::Item()
{
	tag = "Item";
}

Item::Item(string tag, int x, int y, int width, int height, int pictureID) :GameObject(tag, x, y, width, height, pictureID)
{

}
