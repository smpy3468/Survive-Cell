#include "StdAfx.h"
#include "GameSystem.h"
#include "Player.h"
#include "Map.h"

Player::Player()
{
	tag = "Player";
}

Player::Player(string tag, int x, int y, int width, int height, int pictureID):Character(tag, x, y, width, height, pictureID)
{
	tag = "Player";
}

void Player::Move(int dx, int dy)
{
	if (!Map::HasObject(x + dx, y + dy))
	{
		GameSystem::MoveScreenTopLeft(dx, dy);
		this->x += dx;
		this->y += dy;
	}
}
