#pragma once

//Monster
//©Çª«
//Ä~©ÓCharacter

#include "Character.h"

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
	
private:	
	int defenseRange; 
	int dX[2] ,dY[2]; //¥ª¥k¡B¤W¤U
	int rl;
};