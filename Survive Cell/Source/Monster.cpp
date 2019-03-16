#include "StdAfx.h"
#include "Monster.h"

Monster::Monster()
{
	tag = "Monster";
}


Monster::Monster(string tag, int x, int y, int width, int height, int pictureID) :Character(tag, x, y, width, height, pictureID)
{
	tag = "Monster";
	defenseRange = 10;
	dX[0] = x - defenseRange; //左邊
	dX[1] = x + defenseRange;	//右邊
	rl = 1;
}

void Monster::SetDefenseRange(int defenseRange) {
	this -> defenseRange = defenseRange;
}

int Monster::GetDefenseRange() {
	return defenseRange;
}

void Monster::SetdX() {
	dX[0] = x - defenseRange; //左邊
	dX[1] = x + defenseRange;	//右邊
}

void Monster::SetRL(int rl) {
	this ->rl = rl;
}

int Monster::GetRL() {
	return rl;
}

int Monster::GetdX(int point) {
	if (point == 0)
		return dX[0];
	else
		return dX[1];
}

void Monster::SetdY() {
	this->dY[0] = y - defenseRange; //下
	this->dY[1] = y + defenseRange;	//上
}

void Monster::AutoMove() {
	if (rl == LEFT)							//如果GetLR == 0 , X 往左移動
		this->x = x - 1;

	else if (rl == RIGHT)
		this->x = x + 1;					//如果GetLR == 1 , X 往右移動


	if (x <= dX[0])       //GetdX[0]左邊警戒範圍，如果超過左邊 改右邊移動
		this->rl = RIGHT;

	else if (x >= dX[1]) //GetdX[1]右邊警戒範圍，如果超過右邊 改左邊移動
		this->rl = LEFT;
}

