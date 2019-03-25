#pragma once

//Potion
//場上的補品道具
//繼承Item

#include "Item.h"

class Potion :public Item
{
public:
	Potion();
	Potion(string tag, int x, int y, int width, int height, int pictureID);
private:
};