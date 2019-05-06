#pragma once
#include"Effect.h"
#include"GameSystem.h"
#include"Player.h"
class Fire :public Effect {
	public:
		Fire(string tag, int x, int y, int width, int height);		//Constructor
		~Fire();
		void ShowBitMap(int hostX, int hostY,  int hostCurrentAni, int attackAniNumber)override;						//顯示動畫(有條件)
		

		//bool IsPlayerInRange(int right_fix, int left_fix, int up_fix, int down_fix);	//兩者的圖形是否有觸碰到
	private:
		void LoadAni()override;								
		void SetXY(int hostX, int hostY, int hostCurrentAni)override;					//隨著Demon更新火焰位置
		//void SetBitMapPosition()override;											//設定動畫左上角
		//vector<CAnimation*> ani;													//動畫集
		//Player* player = GameSystem::GetGameObjectWithTag<Player>("Player");
		///int currentAni=0;															//現在執行哪個動畫	(左邊火焰:0, 右邊火焰版:1)
		//int hit = 0;																//每一次的火焰只能造成一次傷害

		enum ANI {
			ANI_FIRE_LEFT = 0,
			ANI_FIRE_RIGHT
		};

}; 