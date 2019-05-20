#include "StdAfx.h"
#include "ButtonStart.h"

ButtonStart::ButtonStart()
{
}

ButtonStart::ButtonStart(string tag, int x, int y, int width, int height) :Button(tag, x, y, width, height)
{
	LoadAni();
}

ButtonStart::~ButtonStart()
{
}

void ButtonStart::OnClick()
{
	
}

void ButtonStart::LoadAni()
{
	UIpicture.LoadBitmap(".\\res\\button_start.bmp");
}
