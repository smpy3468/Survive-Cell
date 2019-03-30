#include "StdAfx.h"
#include "Floor.h"
#include "GameSystem.h"

Floor::Floor()
{
	tag = "Floor";
}

Floor::Floor(string tag, int x, int y, int width, int height, int pictureID) :GameObject(tag, x, y, width, height, pictureID)
{
	layer = GameSystem::LAYER::LAYER_FLOOR;
}
