#include "StdAfx.h"
#include "ButtonOnClickEvent.h"
#include "GameSystem.h"

CAnimation ButtonOnClickEvent::ani;
bool ButtonOnClickEvent::isAniLoaded = false;

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
	GameSystem::ShowText("遊戲說明:\n打贏BOSS或死亡即結束。\n\n操作說明:\n方向鍵:移動\nZ:翻滾\nX:攻擊\nC:互動(開寶箱、撿東西、使用傳送門等)\n空白鍵:跳躍\n下+空白鍵:下跳\n1:切換到武器1\n2:切換到武器2\n\n密技:\nF:回血100\nG:Boss扣血1000\n\n(再次按下滑鼠左鍵回主選單)"
		, SIZE_X / 10, 0, SIZE_X, SIZE_Y, GameSystem::ALIGN_LEFT, GameSystem::ALIGN_CENTER
		, 12);

	ani.SetTopLeft(SIZE_X * 3 / 5, 200);
	ani.OnMove();
	ani.OnShow();

	return true;
}

void ButtonOnClickEvent::LoadOptionAni()
{
	if (isAniLoaded == false)
	{
		ani.AddBitmap(".\\res\\boss_boss_0.bmp", RGB(255, 255, 255));
		ani.AddBitmap(".\\res\\boss_boss_1.bmp", RGB(255, 255, 255));
		ani.AddBitmap(".\\res\\boss_boss_2.bmp", RGB(255, 255, 255));
		ani.AddBitmap(".\\res\\boss_boss_3.bmp", RGB(255, 255, 255));

		isAniLoaded = true;
	}
}
