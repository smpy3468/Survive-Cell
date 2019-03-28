#pragma once
#include"GameObject.h"


class Fire :public GameObject {
	public:
		Fire(string tag, int x, int y, int width, int height, int pictureID);
		void ShowBitMap(int attackAniNumber0, int curentAni);
		void SetXY(int demonX, int dmonY, int placeRelativePlayer);
	private:
		void LoadAni();
		void AddAniBitMaps(char* pic[], int aniType, int picCount);//增加多張動畫圖片
		void AddAniBitMap(char* pic, int aniType);//增加動畫圖片

		void SetBitMapPosition()override; //設定動畫左上角
		vector<CAnimation*> ani;//動畫
		int currentAni=0;

		const int ANI_FIRE_LEFT = 0;
		const int ANI_FIRE_RIGHT = 1;
		const int ANI_ATTACK_LEFT = 3, ANI_ATTACK_RIGHT = 4; 
		const int LEFT = 1, RIGHT = 2;
}; 