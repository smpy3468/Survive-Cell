#pragma once

#include <Map>
#include "UInterface.h"

//ButtonOnClickEvent
//按鈕事件

class ButtonOnClickEvent
{
public:
	ButtonOnClickEvent();
	~ButtonOnClickEvent();

	static bool OnClickStart(CGame* c);//開始按鈕
	static bool OnClickExit(CGame* c);//結束按鈕
	static bool OnClickOption(CGame* c);//選項按鈕

	enum OnClickEvent
	{
		ON_CLICK_START = 0,
		ON_CLICK_EXIT,
		ON_CLICK_OPTION,
		ON_CLICK_LENGTH
	};

	static map<int, bool(*)(CGame*)> onClickEventList;//儲存按鈕事件的函數指標
private:
	
};