#pragma once

//Item
//�D��
//�~��GameObject

#include "GameObject.h"

class Item :public GameObject
{
public:
	Item();
	Item(string tag, int x, int y, int width, int height, int pictureID);
private:
};