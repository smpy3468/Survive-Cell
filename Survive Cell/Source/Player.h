#pragma once

//Player
//ª±®a
//Ä~©ÓCharacter

#include "Character.h"

class Player :public Character
{
public:
	Player();
	Player(string tag, int x, int y, int width, int height, int pictureID);
	void Move(int dx, int dy)override;//²¾°Ê
private:
};