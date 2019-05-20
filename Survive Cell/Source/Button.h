#pragma once

#include "UInterface.h"

//Button
//按鈕

class Button :public UInterface
{
public:
	Button();
	Button(string tag, int x, int y, int width, int height, int onClickEvent);
	virtual ~Button();

	void Dead();
	virtual void OnClick(CGame* c);
	void SetBitMapPosition();
	void ShowBitMap();

	enum OnClickEvent
	{
		ON_CLICK_START = 0,
		ON_CLICK_EXIT,
		ON_CLICK_LENGTH
	};

private:
	virtual void LoadAni();

	int myOnClickEvent;//這顆按鈕的OnClick事件是哪一個

	static vector<void(*)(CGame*)> onClickEventList;//儲存按鈕事件的函數指標
	static void OnClickStart(CGame* c);//開始按鈕
	static void OnClickExit(CGame* c);//結束按鈕
};