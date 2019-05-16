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
	int nearAttackRange = 50;//近攻擊距離
	int farAttackRange = SIZE_X / 2;//遠攻擊距離
	int playerDistanceX, playerDistanceY;//玩家跟BOSS的距離

	enum STATE
	{
		STATE_IDLE = 0,
		STATE_MOVE,
		STATE_NEAR_SLASH,
		STATE_FAR_SHOOT,
		STATE_JUMP,
		STATE_LENGTH
	};

	unsigned int currentStateProb[STATE_LENGTH];//目前各種狀態的機率，會根據玩家的距離、BOSS的血量等因素而變化
	unsigned int cumStateProb[STATE_LENGTH] = { 0 };//各項狀態的累計機率，用來判別亂數用的
	void ChangeStateProb(unsigned int newStateProb[]);//改變各項狀態機率
	//各種狀態的機率，數字越大機率越高

	unsigned int originStateProb[STATE_LENGTH] = { 1,30,0,0,10 };//原始機率，玩家不在攻擊範圍內時套用
	unsigned int farStateProb[STATE_LENGTH] = { 1,5,0,30,10 };//遠距離時的機率
	unsigned int nearStateProb[STATE_LENGTH] = { 1,5,30,5,10 };//近距離時的機率
	bool InNear();//在近距攻擊範圍內
	bool InFar();//在遠距攻擊範圍內

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