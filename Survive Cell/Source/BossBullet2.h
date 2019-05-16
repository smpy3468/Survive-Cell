#pragma once

#include "GameObject.h"
#include "Player.h"

//BossBullet
//Boss�o�g���l�u

class BossBullet2 :public GameObject
{
public:
	BossBullet2();
	BossBullet2(string tag, int x, int y, int width, int height, double angle);//���V������
	~BossBullet2();

	void Dead()override;
	void Act()override;
	void SetBitMapPosition()override;
	void ShowBitMap()override;
private:

	Player * player = GameSystem::GetGameObjectWithType<Player>();//���a

	double normalX, normalY;//x,y���첾�q
	int moveSpeed;//���ʳt��

	int attackDamage;//�����ˮ`

	CAnimation * ani;
	void LoadAni();
};