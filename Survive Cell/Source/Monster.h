#pragma once

//Monster
//�Ǫ�
//�~��Character

#include "Character.h"

class Monster :public Character
{
public:
	Monster();
	void SetDefenseRange(int Rnage);
	void SetLR(int lr);

	int GetDefenseRange();
	int GetLR();
	int* GetdX();


private:	
	void SetdX();
	void SetdY();
	int defenseRange = 20;
	int lr=0;
	int dX[2], dY[2]; //���k�B�W�U
};