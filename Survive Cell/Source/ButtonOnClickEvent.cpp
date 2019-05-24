#include "StdAfx.h"
#include "ButtonOnClickEvent.h"
#include "GameSystem.h"

map<int, bool(*)(CGame*)> ButtonOnClickEvent::onClickEventList =
{
	{ON_CLICK_START,&OnClickStart},
	{ON_CLICK_EXIT,&OnClickExit},
	{ON_CLICK_OPTION,&OnClickOption}
};

ButtonOnClickEvent::ButtonOnClickEvent()
{

}

ButtonOnClickEvent::~ButtonOnClickEvent()
{

}

bool ButtonOnClickEvent::OnClickStart(CGame* c)
{
	c->Instance()->SetGameState(GAME_STATE_RUN);//���U�}�l�A������GAME_STATE_RUN

	return true;
}

bool ButtonOnClickEvent::OnClickExit(CGame* c)
{
	//exit(0);
	::PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, NULL, NULL);//�௫�g��
	return true;
}

bool ButtonOnClickEvent::OnClickOption(CGame * c)
{
	GameSystem::DrawRectangle(0, 0, SIZE_X, SIZE_Y, RGB(240, 240, 240));
	GameSystem::ShowText("�ާ@����:\n��V��:����\nZ:½�u\nX:����\nC:����(�}�_�c�B�ߪF��B�i�J��)\n�ť���:���D\n\n�K��:\nF:�^��100\nG:Boss����1000"
		, SIZE_X / 4, SIZE_Y / 4, SIZE_X * 3 / 4, SIZE_Y * 3 / 4, GameSystem::ALIGN_LEFT, GameSystem::ALIGN_CENTER);
	return true;
}
