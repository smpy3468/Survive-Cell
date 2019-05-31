#pragma once
#include "UInterface.h"
#include "Player.h"
#include "GameSystem.h"
class UIBlood : public UInterface
{
	public:
		UIBlood(string tag, int x, int y, int width, int height);
		~UIBlood();
		void ShowBitMap();
	private:
		void RefreshTargetWidth();//更新目標寬度
		void OnShow();
		

		Player* player = GameSystem::GetGameObjectWithTag<Player>("Player");
		int targetWidth;//目標寬度
		int maxWidth;//最大寬度
};