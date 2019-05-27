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
	GameSystem::ShowText("�C������:\n��ĹBOSS�Φ��`�Y�����C\n\n�ާ@����:\n��V��:����\nZ:½�u\nX:����\nC:����(�}�_�c�B�ߪF��B�ϥζǰe����)\n�ť���:���D\n�U+�ť���:�U��\n1:������Z��1\n2:������Z��2\n\n�K��:\nF:�^��100\nG:Boss����1000\n\n(�A�����U�ƹ�����^�D���)"
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
