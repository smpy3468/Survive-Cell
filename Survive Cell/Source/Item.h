#pragma once

//Item
//道具
//繼承GameObject

#include "GameSystem.h"
#include "GameObject.h"

class Item :public GameObject
{
public:
	Item();
	Item(string tag, int x, int y, int width, int height, int pictureID);

	virtual void Picked();//被撿起
private:
	void Dead()override;
};