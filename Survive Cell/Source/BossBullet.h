#pragma once

#include "GameObject.h"

//BossBullet
//Boss發射的子彈

class BossBullet :public GameObject
{
public:
	BossBullet();
	BossBullet(string tag, int x, int y, int width, int height);
	~BossBullet();
	
	void Act()override;
	void SetBitMapPosition()override;
	void ShowBitMap()override;
private:

	int targetX, targetY;//目標座標
	int distanceX, distanceY;//與目標的距離
	int moveSpeed;//移動速度

	CAnimation * ani;
	void LoadAni();
};