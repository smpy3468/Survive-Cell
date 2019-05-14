#pragma once

//Potion
//場上的補品道具
//繼承Item

#include "GameSystem.h"
#include "Item.h"
#include "Player.h"

class Potion :public Item
{
public:
	Potion();
	~Potion();
	Potion(string tag, int x, int y, int width, int height);

	void Picked()override;//被撿取

private:
	virtual void Dead()override;

	int recoverHP;//HP回復量
};