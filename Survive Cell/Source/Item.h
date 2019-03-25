#pragma once

//Item
//¹D¨ã
//Ä~©ÓGameObject

#include "GameObject.h"

class Item :public GameObject
{
public:
	Item();
	Item(string tag, int x, int y, int width, int height, int pictureID);
private:
};