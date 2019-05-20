#include "StdAfx.h"
#include "ButtonExit.h"

ButtonExit::ButtonExit()
{
}

ButtonExit::ButtonExit(string tag, int x, int y, int width, int height) :Button(tag, x, y, width, height)
{
	LoadAni();
}

ButtonExit::~ButtonExit()
{
}

void ButtonExit::OnClick()
{
}

void ButtonExit::LoadAni()
{
	LoadBitMap(".\\res\\button_exit.bmp");
}
