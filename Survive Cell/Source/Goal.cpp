#include "StdAfx.h"
#include "Goal.h"
Goal::Goal(string tag, int x, int y, int width, int height):GameObject(tag, x, y, width, height)
{
	LoadBitMap(".\\res\\goal.bmp");
	layer = GameSystem::LAYER::LAYER_FLOOR;
	SetBitMapPosition();
}

void Goal::Picked()
{
	GameSystem::SetIsNextStage(true);
	GameSystem::StagePlusOne();
}

/*void Goal::ShowBitMap()
{
	SetBitMapPosition();
	objectPic.ShowBitmap();
}

void Goal::SetBitMapPosition()
{
	objectPic.SetTopLeft(x - Map::GetSX(), y - Map::GetSY());
}*/