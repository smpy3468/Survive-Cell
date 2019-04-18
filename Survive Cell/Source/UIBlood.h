#pragma once
#include "UInterface.h"
#include "GameSystem.h"
#include "Player.h"
class UIBlood : public UInterface
{
	public:
		UIBlood(string tag, int x, int y, int width, int height);
		void ShowBitMap();
	private:
		void RefreshTargetWidth();
		void OnShow();
		

		Player* player = GameSystem::GetGameObjectWithTag<Player>("Player");
		int targetWidth;
};