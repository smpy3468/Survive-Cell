#pragma once

//Potion
//���W���ɫ~�D��
//�~��Item

#include "Item.h"

class Potion :public Item
{
public:
	Potion();
	Potion(string tag, int x, int y, int width, int height, int pictureID);
private:
};