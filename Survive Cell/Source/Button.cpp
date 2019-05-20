#include "StdAfx.h"
#include "Button.h"

Button::Button()
{
}

Button::Button(string tag, int x, int y, int width, int height) :UInterface(tag, x, y, width, height)
{
	LoadAni();
}

Button::~Button()
{

}

void Button::Dead()
{

}

void Button::OnClick()
{
}

void Button::SetBitMapPosition()
{
	UIpicture.SetTopLeft(x,y);
}

void Button::ShowBitMap()
{
	UIpicture.ShowBitmap();
}

void Button::LoadAni()
{
	
}
