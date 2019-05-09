#pragma once

#include "GameObject.h"

//BossBullet
//Bossµo®gªº¤l¼u

class BossBullet :public GameObject
{
public:
	BossBullet();
	BossBullet(string tag, int x, int y, int width, int height);
	~BossBullet();
private:
	CAnimation * ani;
	void LoadAni();
};