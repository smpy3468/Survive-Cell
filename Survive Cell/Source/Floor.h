#pragma once

//Floor
//¦aªO
//Ä~©ÓGameObject

#include "GameObject.h"

class Floor :public GameObject
{
public:
	Floor();
	Floor(string tag, int x, int y, int width, int height, int pictureID);
private:
};