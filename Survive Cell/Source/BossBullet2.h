#pragma once

#include "GameObject.h"
#include "Player.h"

//BossBullet
//Boss發射的子彈

class BossBullet2 :public GameObject
{
public:
	BossBullet2();
	BossBullet2(string tag, int x, int y, int width, int height, double angle);//飛向的角度
	~BossBullet2();

	void Dead()override;
	void Act()override;
	void SetBitMapPosition()override;
	void ShowBitMap()override;
private:

	Player * player = GameSystem::GetGameObjectWithType<Player>();//玩家

	double normalX, normalY;//x,y單位位移量
	int moveSpeed;//移動速度

	int attackDamage;//攻擊傷害

	CAnimation * ani;
	void LoadAni();
};