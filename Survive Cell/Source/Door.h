#pragma once

//Door
//門
//繼承GameObject

#include "GameObject.h"

class Door :public GameObject
{
public:
	Door();
	Door(string tag, int x, int y, int width, int height);
	void Kicked();//被踢
private:
	void Dead()override;
	void ShowBitMap()override;

	bool isRuin;//是否被破壞
	CAnimation* ani;
};