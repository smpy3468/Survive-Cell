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

	bool isShoot = false;//是否發射了子彈

	int originJumpDisplacement = 30, jumpDisplacement = originJumpDisplacement;//跳躍位移量

	void ShowBitMap()override;

	void NearSlash();//砍
	void JumpBack();//往後跳
	void JumpFront();//往前跳
	void FarShoot();//遠程攻擊
	void InstantDeath();//即死技能

	int RandomState();//決定隨機狀態
	int currentState = 0;//目前狀態
	enum STATE
	{
		STATE_IDLE = 0,
		STATE_MOVE,
		STATE_NEAR_SLASH,
		STATE_FAR_SHOOT,
		STATE_JUMP,
		STATE_LENGTH
	};

	unsigned int stateProb[STATE_LENGTH] = { 10,20,15,15,30 };//各種狀態的機率，數字越大機率越高
	unsigned int cumProb[STATE_LENGTH] = {0};//累計機率

	const bool FACE_LEFT = true;//面向左邊
	const bool FACE_RIGHT = false;//面向右邊
	bool faceLR = FACE_LEFT;//面向左邊或面向右邊

	int currentAni = 0;//目前動畫
	enum ANI
	{
		ANI_IDLE = 0,
		ANI_LEFT,
		ANI_RIGHT,
		ANI_NEAR_SLASH_LEFT,
		ANI_NEAR_SLASH_RIGHT,
		ANI_JUMP,
		ANI_FAR_SHOOT_LEFT,
		ANI_FAR_SHOOT_RIGHT,
		ANI_GET_HIT_LEFT,
		ANI_GET_HIT_RIGHT
	};

	void LoadAni()override;
};