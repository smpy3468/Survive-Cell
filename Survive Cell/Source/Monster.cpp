#include "StdAfx.h"
#include "Monster.h"

Monster::Monster()
{
	tag = "Monster";
}


void Monster::SetDefenseRange(int range) {
	this->defenseRange;
}

int Monster::GetDefenseRange() {
	return defenseRange;
}

void Monster::SetdX() {
	this->dX[0] = x - defenseRange; //����
	this->dX[1] = x + defenseRange;	//�k��
}

void Monster::SetLR(int lr) {
	this->lr = lr;
}

int Monster::GetLR() {
	return lr;
}

int* Monster::GetdX() {
	return dX;
}

void Monster::SetdY() {
	this->dY[0] = y - defenseRange; //�U
	this->dY[1] = y + defenseRange;	//�W
}