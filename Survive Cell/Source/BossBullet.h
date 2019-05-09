#pragma once

#include "GameObject.h"

//BossBullet
//Boss�o�g���l�u

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

	int targetX, targetY;//�ؼЮy��
	int distanceX, distanceY;//�P�ؼЪ��Z��
	int moveSpeed;//���ʳt��

	CAnimation * ani;
	void LoadAni();
};