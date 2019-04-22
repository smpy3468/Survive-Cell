#pragma once
#include "UInterface.h"
#include "GameSystem.h"
#include "Monster.h"
class UIMonsterBlood :public UInterface
{
public:
	UIMonsterBlood(string tag, int x, int y, int width, int height);
private:
	vector<Monster*> allMonster = GameSystem::GetGameObjectsWithTag<Monster>("Monster");
};
