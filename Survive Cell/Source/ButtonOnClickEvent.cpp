#include "StdAfx.h"
#include "ButtonOnClickEvent.h"

map<int, void(*)(CGame*)> ButtonOnClickEvent::onClickEventList =
{
	{ON_CLICK_START,&OnClickStart},
	{ON_CLICK_EXIT,&OnClickExit}
};

ButtonOnClickEvent::ButtonOnClickEvent()
{

}

ButtonOnClickEvent::~ButtonOnClickEvent()
{

}

void ButtonOnClickEvent::OnClickStart(CGame* c)
{
	c->Instance()->SetGameState(GAME_STATE_RUN);//���U�}�l�A������GAME_STATE_RUN
}

void ButtonOnClickEvent::OnClickExit(CGame* c)
{
	//exit(0);
	::PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, NULL, NULL);//�௫�g��
}