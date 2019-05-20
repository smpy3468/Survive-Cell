#include "StdAfx.h"
#include "Button.h"

vector<void(*)(CGame*)> Button::onClickEventList = {&OnClickStart,&OnClickExit};

Button::Button()
{
}

Button::Button(string tag, int x, int y, int width, int height,int onClickEvent) :UInterface(tag, x, y, width, height)
{
	this->myOnClickEvent = onClickEvent;
	LoadAni();
}

Button::~Button()
{

}

void Button::Dead()
{

}

void Button::OnClick(CGame* c)
{
	switch (myOnClickEvent)
	{
	case ON_CLICK_START://¶}©l
		onClickEventList[ON_CLICK_START](c);
		break;
	case ON_CLICK_EXIT://µ²§ô
		onClickEventList[ON_CLICK_EXIT](c);
		break;
	}
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
	case ON_CLICK_START:
		LoadBitMap(".\\res\\button_start.bmp");
		break;
	case ON_CLICK_EXIT:
		LoadBitMap(".\\res\\button_exit.bmp");
		break;
	}
}

void Button::OnClickStart(CGame* c)
{
	c->Instance()->SetGameState(GAME_STATE_RUN);
}

void Button::OnClickExit(CGame* c)
{
	exit(0);
}
