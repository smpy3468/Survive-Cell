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
	dX[0] = x - defenseRange; //����
	dX[1] = x + defenseRange;	//�k��
	rl = 1;
}

void Monster::SetDefenseRange(int defenseRange) {
	this -> defenseRange = defenseRange;
}

int Monster::GetDefenseRange() {
	return defenseRange;
}

void Monster::SetdX() {
	dX[0] = x - defenseRange; //����
	dX[1] = x + defenseRange;	//�k��
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
	this->dY[0] = y - defenseRange; //�U
	this->dY[1] = y + defenseRange;	//�W
}

void Monster::AutoMove() {
	if (rl == LEFT)							//�p�GGetLR == 0 , X ��������
		this->x = x - 1;

	else if (rl == RIGHT)
		this->x = x + 1;					//�p�GGetLR == 1 , X ���k����


	if (x <= dX[0])       //GetdX[0]����ĵ�ٽd��A�p�G�W�L���� ��k�䲾��
		this->rl = RIGHT;

	else if (x >= dX[1]) //GetdX[1]�k��ĵ�ٽd��A�p�G�W�L�k�� �索�䲾��
		this->rl = LEFT;
}

