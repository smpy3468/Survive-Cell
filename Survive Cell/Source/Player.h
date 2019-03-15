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

	void SetIsMoveUp(bool isMoveUp);//設定是否向上移動
	void SetIsMoveDown(bool isMoveDown);//設定是否向下移動
	void SetIsMoveLeft(bool isMoveLeft);//設定是否向左移動
	void SetIsMoveRight(bool isMoveRight);//設定是否向右移動
	void Move();//移動方向
private:
	bool isMoveUp;//是否向上移動
	bool isMoveDown;//是否向下移動
	bool isMoveLeft;//是否向左移動
	bool isMoveRight;//是否向右移動
};