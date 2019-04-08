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
	virtual void Picked();														//被撿起
    virtual void ShowBitMap();													//顯示動畫
	//virtual void SetXY(int hostX, int hostY, int playerCurrentAni, int  playerAniNumber);	//隨著擁有者移動 設定XY
				
protected:	
	//bool IsPlayerInRange(GameObject* obj, int right_fix, int left_fix, int up_fix, int down_fix);//判斷動畫是否即擊中
	void AddAniBitMaps(char* pic[], int aniType, int picCount);					//增加多張動畫圖片
	void AddAniBitMap(char* pic, int aniType);									//增加動畫圖片
	virtual void LoadAni();

	virtual void Dead()override;
	
	void SetBitMapPosition()override;

	
	int currentAni = ANI_IDLE;     //IDLE 動畫
	vector<CAnimation*> ani;//動畫
	enum ANI {
		ANI_IDLE = 0,
	};
};