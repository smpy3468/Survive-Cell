#pragma once

#include "GameObject.h"
#include "Player.h"
#include "Boss.h"

//BossBullet
//Boss發射的子彈

class BossBullet :public GameObject
{
public:
	BossBullet();
	BossBullet(string tag, int x, int y, int width, int height);
	~BossBullet();

	void Dead()override;
	void Act()override;
	void SetBitMapPosition()override;
	void ShowBitMap()override;
private:

	Player * player = GameSystem::GetGameObjectWithType<Player>();//玩家

	int targetX, targetY;//目標座標
	int distanceX, distanceY;//與目標的距離
	int moveSpeed;//移動速度

	int attackDamage;//攻擊傷害

	Boss* boss = GameSystem::GetGameObjectWithType<Boss>();//boss
	CAnimation * ani;
	void LoadAni();
};