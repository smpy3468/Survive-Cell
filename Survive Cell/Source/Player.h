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

	//void SetIsMoveUp(bool isMoveUp);//設定是否向上移動
	//void SetIsMoveDown(bool isMoveDown);//設定是否向下移動
	void SetIsMoveLeft(bool isMoveLeft);//設定是否向左移動
	void SetIsMoveRight(bool isMoveRight);//設定是否向右移動
	void SetIsGrounded(bool isGrounded);//設定是否在地上
	void SetIsJump(bool isJump);//設定是否按下跳躍
	void Move();//按下按鍵移動
	void Fall();//下降
	void Jump();//跳躍
private:
	//bool isMoveUp;//是否向上移動
	//bool isMoveDown;//是否向下移動
	bool isMoveLeft;//是否向左移動
	bool isMoveRight;//是否向右移動
	bool isJump;//是否按下跳躍

	int fallDisplacement;//下降位移量(移動到沒有地板的位置會用到)
	int originJumpDisplacement, jumpDisplacement;//跳躍位移量
	bool isGrounded;//是否在地上
};