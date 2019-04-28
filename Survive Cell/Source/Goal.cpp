#include "StdAfx.h"
#include "Goal.h"
Goal::Goal(string tag, int x, int y, int width, int height):GameObject(tag, x, y,width, height)
{
	LoadBitMap("res\\goal.bmp");
}
