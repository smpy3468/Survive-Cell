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
	c->Instance()->SetGameState(GAME_STATE_RUN);//按下開始，切換到GAME_STATE_RUN

	return true;
}

bool ButtonOnClickEvent::OnClickExit(CGame* c)
{
	//exit(0);
	::PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, NULL, NULL);//賴神寫的
	return true;
}

bool ButtonOnClickEvent::OnClickOption(CGame * c)
{
	GameSystem::DrawRectangle(0, 0, SIZE_X, SIZE_Y, RGB(240, 240, 240));
	GameSystem::ShowText("操作說明:\n方向鍵:移動\nZ:翻滾\nX:攻擊\nC:互動(開寶箱、撿東西、進入門)\n空白鍵:跳躍\n\n密技:\nF:回血100\nG:Boss扣血1000"
		, SIZE_X / 4, SIZE_Y / 4, SIZE_X * 3 / 4, SIZE_Y * 3 / 4, GameSystem::ALIGN_LEFT, GameSystem::ALIGN_CENTER);
	return true;
}
