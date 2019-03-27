#pragma once

//Monster
//怪物
//繼承Character

#include "Character.h"
#include "GameSystem.h"
#include "Player.h"
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
	bool IsInAttackField(int playerX, int playerY,int right_fix, int left_fix, int up_fix, int down_fix);   //是的話，衝向主角 #和IsPlayerInRange一樣之後要virtual
	int  PlaceRelativePlayer(Player* player); //怪物相對於腳色的位置
	void Attack()override;//當Player進入防守區，攻擊他


	void ShowBitMap()override;

private:	
	int defenseRange, attackField; //defenseRange 來回走動的範圍, attackfield衝過去攻擊主角的範圍
	int dX[2] ,dY[2]; //左右、上下
	int rl,status;
	static const int LEFT = 1, RIGHT = 2, STANDBY = 0, ALERTNESS = 1, ATTACK = 2; //目前怪物的狀態

	void Dead()override;

	bool IsPlayerInRange(Player* player, int right_fix, int left_fix, int up_fix, int down_fix); //進入攻擊距離就停下來  #Attackfild要夠大這個設定了才有用
	//之後要virtual 應應不同的怪做出攻擊範圍的平衡
	void LoadAni()override; //載入動畫
	int currentAni = 0; //現在執行得動畫

	const int ANI_IDLE = 0; //原地
	const int ANI_LEFT = 1; //左動畫
	const int ANI_RIGHT = 2; //右動畫
};