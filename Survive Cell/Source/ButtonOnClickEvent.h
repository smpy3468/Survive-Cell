#pragma once

#include "UInterface.h"

//ButtonOnClickEvent
//按鈕事件

class ButtonOnClickEvent
{
public:
	ButtonOnClickEvent();
	~ButtonOnClickEvent();

	static void OnClickStart(CGame* c);//開始按鈕
	static void OnClickExit(CGame* c);//結束按鈕

	enum OnClickEvent
	{
		ON_CLICK_START = 0,
		ON_CLICK_EXIT,
		ON_CLICK_LENGTH
	};

	static vector<void(*)(CGame*)> onClickEventList;//儲存按鈕事件的函數指標
private:
	
};