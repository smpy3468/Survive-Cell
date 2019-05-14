#pragma once
#include "Item.h"

class Treasure :public Item
{
public:
	Treasure(string tag, int x, int y, int width, int height);
private:
	void LoadAni()override;
};