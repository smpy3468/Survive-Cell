#pragma once

//Door
//門
//繼承GameObject

#include "GameObject.h"
#include "GameSystem.h"
#include "Monster.h"
#include "Player.h"
class Door :public GameObject
{
public:
	Door();
	Door(string tag, int x, int y, int width, int height);
	void Kicked();//被踢
	bool GetRuin();


	void SetBitMapPosition()override;
private:
	const int LEFT = 1, RIGHT = 2;
	void Dead()override;
	void DazeMonster();
	void ShowBitMap()override;
	void LoadAni();//載入圖片
	bool isRuin;//是否被破壞
	int lr; //被破壞時門飛出去的方向
	CAnimation* ani;

	int stunRangeX, stunRangeY;
};