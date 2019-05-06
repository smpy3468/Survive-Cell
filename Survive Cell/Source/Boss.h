#pragma once

#include "Character.h"
#include "Monster.h"

//Boss
//王

class Boss :public Monster
{
public:
	Boss();
	~Boss();
	Boss(string tag, int x, int y, int width, int height);
	void Act();//行動
	
	void Attack()override;
	void Jump();//跳躍
	void Fall(int perDisplacement);//掉落
	void Move(int dx, int dy)override;

private:

	int originJumpDisplacement = 30, jumpDisplacement = originJumpDisplacement;//跳躍位移量

	void ShowBitMap()override;

	void NearSlash();//砍
	void JumpBack();//往後跳
	void JumpFront();//往前跳
	void FarSlash();//遠程劍波
	void InstantDeath();//即死技能

	int currentState = 0;//目前狀態
	enum STATE
	{
		STATE_IDLE = 0,
		STATE_MOVE,
		STATE_ATTACK,
		STATE_JUMP,
		STATE_LENGTH
	};
	int attackMode = 0;//攻擊模式

	const bool FACE_LEFT = true;//面向左邊
	const bool FACE_RIGHT = false;//面向右邊
	bool faceLR = FACE_LEFT;//面向左邊或面向右邊

	int currentAni = 0;//目前動畫
	enum ANI
	{
		ANI_IDLE = 0,
		ANI_LEFT,
		ANI_RIGHT,
		ANI_ATTACK_LEFT,
		ANI_ATTACK_RIGHT,
		ANI_JUMP,
		ANI_GET_HIT_LEFT,
		ANI_GET_HIT_RIGHT
	};

	void LoadAni()override;
};