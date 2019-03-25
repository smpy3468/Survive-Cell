#pragma once

//Player
//玩家
//繼承Character

#include "Character.h"

class Player :public Character
{
public:
	Player();
	Player(string tag, int x, int y, int width, int height, int pictureID);
	void Move(int dx, int dy)override;//移動特定距離

	void SetIsMoveLeft(bool isMoveLeft);//設定是否向左移動
	void SetIsMoveRight(bool isMoveRight);//設定是否向右移動
	void SetIsGrounded(bool isGrounded);//設定是否在地上
	void SetIsJump(bool isJump);//設定是否按下跳躍
	void Move();//按下按鍵移動
	void Fall();//下降
	void Jump();//跳躍

	void ShowBitMap()override;//顯示動畫

	void Attack()override;//攻擊
private:
	bool isMoveLeft;//是否向左移動
	bool isMoveRight;//是否向右移動
	bool isJumpKeyDown;//是否按下跳躍
	bool isJump;//是否正在跳躍
	bool isFall;//是否正在下降

	int fallDisplacement;//下降位移量(移動到沒有地板的位置會用到)
	int originJumpDisplacement, jumpDisplacement;//跳躍位移量
	bool isGrounded;//是否在地上

	void Dead()override;//死亡時呼叫

	void LoadAni()override;//載入動畫
	int currentAni = 0;//目前動畫

	const unsigned int ANI_IDLE = 0;
	const unsigned int ANI_LEFT = 1;//左動畫
	const unsigned int ANI_RIGHT = 2;//右動畫
	const unsigned int ANI_JUMP_LEFT = 3;//左跳動畫
	const unsigned int ANI_JUMP_RIGHT = 4;//右跳動畫
};