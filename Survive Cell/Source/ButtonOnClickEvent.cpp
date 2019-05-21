#include "StdAfx.h"
#include "ButtonOnClickEvent.h"

vector<void(*)(CGame*)> ButtonOnClickEvent::onClickEventList = {&OnClickStart,&OnClickExit};

ButtonOnClickEvent::ButtonOnClickEvent()
{
}

ButtonOnClickEvent::~ButtonOnClickEvent()
{
}

void ButtonOnClickEvent::OnClickStart(CGame* c)
{
	c->Instance()->SetGameState(GAME_STATE_RUN);//按下開始，切換到GAME_STATE_RUN
}

void ButtonOnClickEvent::OnClickExit(CGame* c)
{
	exit(0);
}