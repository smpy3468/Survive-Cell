#include "StdAfx.h"
#include "Goal.h"
Goal::Goal(string tag, int x, int y, int width, int height):GameObject(tag, x, y, width, height)
{
	LoadBitMap(".\\res\\goal.bmp");
	layer = GameSystem::LAYER::LAYER_FLOOR;
	SetBitMapPosition();
}

Goal::~Goal()
{
}

void Goal::Picked()
{
	if (GameSystem::GetNowStage() <= 1)//只有第一關的終點有作用
	{
		GameSystem::SetIsNextStage(true);
		GameSystem::StagePlusOne();
	}
}