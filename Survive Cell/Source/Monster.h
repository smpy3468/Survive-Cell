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
	void SetDefenseRange(int defenseRange);
	void SetRL(int rl);
	void SetdX();
	void SetdY();
	void SetAttackField(int attackField);
	void SetAttackRange(int attackRange);


	int GetDefenseRange();
    int GetRL();
	int GetdX(int point);
	int GetStatus();


	void Move(int dx, int dy) {}

	//----------------移動相關---------------------//
	virtual void AutoMove(); //在防守區域內來回走動

	//----------------攻擊相關---------------------//
	bool IsInAttackField(int playerX, int playerY,int right_fix, int left_fix, int up_fix, int down_fix);   //是的話，衝向主角 #和IsPlayerInRange一樣之後要virtual
	bool IsPlayerInRange(Player* player, int right_fix, int left_fix, int up_fix, int down_fix);
	int  PlaceRelativePlayer(Player* player); //怪物相對於腳色的位置

	virtual void Attack();//當Player進入防守區，攻擊他
	
	//-----------------Animation------------------///
	void ShowBitMap()override;
	int GetAttackAniNumber();

protected:
	static const int LEFT = 1, RIGHT = 2, STANDBY = 0, ALERTNESS = 1, ATTACK = 2; //目前怪物的狀態
	int status;
	int currentAni = 0; //現在執行得動畫

	const int ANI_IDLE = 0; //原地
	const int ANI_LEFT = 1; //左移動動畫
	const int ANI_RIGHT = 2; //右移動動畫
	const int ANI_ATTACK_LEFT = 3;  //左邊攻擊動畫
	const int ANI_ATTACK_RIGHT = 4; //右邊攻擊動畫
private:	
	//defenseRange 來回走動的範圍, attackfield衝過去攻擊主角的範圍
	int dX[2] ,dY[2]; //左右、上下
	int rl;
	int defenseRange, attackField;

	void Dead()override;

	//void LoadAni()override; //載入動畫
	
};