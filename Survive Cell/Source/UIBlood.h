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
		void RefreshTargetWidth();//��s�ؼмe��
		void OnShow();
		

		Player* player = GameSystem::GetGameObjectWithTag<Player>("Player");
		int targetWidth;//�ؼмe��
		int maxWidth;//�̤j�e��
};