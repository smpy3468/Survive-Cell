#pragma once
#include"GameObject.h"
#include"GameSystem.h"
#include"Player.h"
class Fire :public GameObject {
	public:
		Fire(string tag, int x, int y, int width, int height, int pictureID);		//Constructor
		void ShowBitMap(int attackAniNumber, int curentAni);						//顯示動畫(有條件)
		void SetXY(int demonX, int dmonY, int placeRelativePlayer);					//隨著Demon更新火焰位置

		bool Fire::IsPlayerInRange(int right_fix, int left_fix, int up_fix, int down_fix);	//兩者的圖形是否有觸碰到
	private:
		void LoadAni();								
		void AddAniBitMaps(char* pic[], int aniType, int picCount);					//增加多張動畫圖片
		void AddAniBitMap(char* pic, int aniType);									//增加動畫圖片

		void SetBitMapPosition()override;											//設定動畫左上角
		vector<CAnimation*> ani;													//動畫集
		Player* player = GameSystem::GetGameObjectWithTag<Player>("Player");
		int currentAni=0;															//現在執行哪個動畫	(左邊火焰:0, 右邊火焰版:1)
		int hit = 0;																//每一次的火焰只能造成一次傷害
		const int ANI_FIRE_LEFT = 0;												//左邊火焰版
		const int ANI_FIRE_RIGHT = 1;												//右邊火焰版
		const int ANI_ATTACK_LEFT = 3, ANI_ATTACK_RIGHT = 4;						//Demon攻擊動畫

}; 