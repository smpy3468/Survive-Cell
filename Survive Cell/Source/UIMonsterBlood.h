#pragma once
#include "UInterface.h"
#include "Monster.h"
#include "Map.h"
class UIMonsterBlood :public UInterface
{
public:
	UIMonsterBlood(string tag, int x, int y, int width, int height);
	void ShowBitMap();
private:
	const int ISATTACK = 5;
	void OnShow(int x, int y, int hp);
	vector<Monster*> allMonster = GameSystem::GetGameObjectsWithTag<Monster>("Monster");
};
