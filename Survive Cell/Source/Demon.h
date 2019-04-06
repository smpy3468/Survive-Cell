#pragma once
#include "Monster.h"
#include "Fire.h"
#include "Player.h"
//DefenseRange
class Demon:public Monster {
	public:
		Demon();																			//BaseConstructor
		Demon::Demon(string tag, int x, int y, int width, int height, int pictureID);		//Constructor
		void Attack()override;																//攻擊
		void AutoMove()override;															//移動
		void ShowBitMap()override;															//顯示動畫
	private:
		void LoadAni()override;																//載入所有動畫
		Player* player = GameSystem::GetGameObjectWithTag<Player>("Player");				//常用到就先記錄下來
		Fire* fire;																			//自帶火焰特效
		int currentBitMapNumber;
};
