#pragma once

//Monster
//©Çª«
//Ä~©ÓCharacter

#include "Character.h"
#include "GameSystem.h"
class Monster :public Character
{
public:
	Monster();
	Monster::Monster(string tag, int x, int y, int width, int height, int pictureID);
	void SetDefenseRange(int Rnage);
	void SetRL(int rl);

	int GetDefenseRange();
    int GetRL();
	int GetdX(int point);

	void SetdX();
	void SetdY();

	void Move(int dx, int dy) {}

	void AutoMove();

private:	
	int defenseRange; 
	int dX[2] ,dY[2]; //¥ª¥k¡B¤W¤U
	int rl;
	static const int LEFT = 1, RIGHT = 2;
};