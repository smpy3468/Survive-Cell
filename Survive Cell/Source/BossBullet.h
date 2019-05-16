#pragma once

#include "GameObject.h"
#include "Player.h"
#include "Boss.h"

//BossBullet
//Boss�o�g���l�u

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

	Player * player = GameSystem::GetGameObjectWithType<Player>();//���a

	int targetX, targetY;//�ؼЮy��
	int distanceX, distanceY;//�P�ؼЪ��Z��
	int moveSpeed;//���ʳt��

	int attackDamage;//�����ˮ`

	Boss* boss = GameSystem::GetGameObjectWithType<Boss>();//boss
	CAnimation * ani;
	void LoadAni();
};