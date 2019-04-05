#pragma once

//Item
//道具
//繼承GameObject

#include "GameSystem.h"
#include "GameObject.h"

class Item :public GameObject
{
public:
	Item();
	Item(string tag, int x, int y, int width, int height, int pictureID);
	virtual void Picked();//被撿起
    virtual void ShowBitMap();
	virtual void SetXY(int hostX, int hostY, int playerCurrentAni, int  playerAniNumber);	//隨著擁有者移動 設定XY
				
protected:	
	bool IsPlayerInRange(GameObject* obj, int right_fix, int left_fix, int up_fix, int down_fix);//判斷動畫是否即擊中
	void AddAniBitMaps(char* pic[], int aniType, int picCount);					//增加多張動畫圖片
	void AddAniBitMap(char* pic, int aniType);									//增加動畫圖片

	virtual void Dead()override;
	virtual void LoadAni();

	void SetBitMapPosition()override;
	const int ANI_ATTACK_LEFT = 3, ANI_ATTACK_RIGHT = 4;						//攻擊動編碼


	int currentAni = ANI_IDLE;     //IDLE 動畫
	vector<CAnimation*> ani;//動畫
	enum ANI {
		ANI_IDLE = 0,
	};
};