#include "StdAfx.h"
#include "Potion.h"

Potion::Potion()
{
	tag = "Potion";
}

Potion::Potion(string tag, int x, int y, int width, int height, int pictureID) :Item(tag, x, y, width, height, pictureID)
{

}
