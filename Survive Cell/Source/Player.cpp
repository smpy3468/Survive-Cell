#include "StdAfx.h"
#include "Player.h"

Player::Player()
{
	tag = "Player";
}

Player::Player(string tag, int x, int y, int width, int height, int pictureID):Character(tag, x, y, width, height, pictureID)
{
	tag = "Player";
}
