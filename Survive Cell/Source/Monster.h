#pragma once

//Monster
//怪物
//繼承Character

#include "Character.h"
#include "GameSystem.h"
class Monster :public Character
{
public:
	Monster();
	Monster::Monster(string tag, int x, int y, int width, int height, int pictureID);
	void SetDefenseRange(int Rnage);
	void SetRL(int rl);

	int GetDefenseRange();
    int GetRL();
	int GetdX(int point);

	void SetdX();
	void SetdY();

	void Move(int dx, int dy) {}

	void AutoMove(); //在防守區域內來回走動
	bool IsInAttackField(int playerX, int playerY);   //是的話，衝向主角
	void Attack()override;//當Player進入防守區，攻擊他

	void ShowBitMap()override;

private:	
	int defenseRange, attackField; //defenseRange 來回走動的範圍, attackfield衝過去攻擊主角的範圍
	int dX[2] ,dY[2]; //左右、上下
	int rl,status;
	static const int LEFT = 1, RIGHT = 2, STANDBY = 0, ALERTNESS = 1, ATTACK = 2;

	void LoadAni()override;

	int currentAni = 0;
	const int ANI_LEFT = 0;
};