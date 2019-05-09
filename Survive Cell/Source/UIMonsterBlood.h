#pragma once
#include "UInterface.h"
#include "Monster.h"
#include "Map.h"
class UIMonsterBlood :public UInterface
{
public:
	UIMonsterBlood(string tag, int x, int y, int width, int height);
	~UIMonsterBlood();
	void ShowBitMap()
	{
		vector<Monster*> allMonster = GameSystem::GetGameObjectsWithTag<Monster>("Monster");
		for (auto& i : allMonster)
		{
			if (i->GetStatus() == ISATTACK && i->GetHP() > 0)
				OnShow(i->GetX(), i->GetY(),i->GetWidth(),i->GetHeight(), i->GetHP(), i->GetMaxHP());
		}
	}
private:
	const int ISATTACK = 5;
	void OnShow(int x, int y, int width, int height, int hp, int maxHP);
};
