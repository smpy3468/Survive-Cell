#include "StdAfx.h"
#include "Button.h"

Button::Button()
{
}

Button::Button(string tag, int x, int y, int width, int height,int onClickEvent) :UInterface(tag, x, y, width, height)
{
	this->myOnClickEvent = onClickEvent;
	OnClick = ButtonOnClickEvent::onClickEventList[myOnClickEvent];//指向對應的函數
	LoadAni();
}

Button::~Button()
{

}

void Button::Dead()
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
	switch (myOnClickEvent)
	{
	case ButtonOnClickEvent::ON_CLICK_START:
		LoadBitMap(".\\res\\button_start.bmp");
		break;
	case ButtonOnClickEvent::ON_CLICK_EXIT:
		LoadBitMap(".\\res\\button_exit.bmp");
		break;
	case ButtonOnClickEvent::ON_CLICK_OPTION:
		LoadBitMap(".\\res\\button_option.bmp");
		break;
	}
}
