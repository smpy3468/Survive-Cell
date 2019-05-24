#pragma once

#include <Map>
#include "UInterface.h"

//ButtonOnClickEvent
//���s�ƥ�

class ButtonOnClickEvent
{
public:
	ButtonOnClickEvent();
	~ButtonOnClickEvent();

	static bool OnClickStart(CGame* c);//�}�l���s
	static bool OnClickExit(CGame* c);//�������s
	static bool OnClickOption(CGame* c);//�ﶵ���s

	enum OnClickEvent
	{
		ON_CLICK_START = 0,
		ON_CLICK_EXIT,
		ON_CLICK_OPTION,
		ON_CLICK_LENGTH
	};

	static map<int, bool(*)(CGame*)> onClickEventList;//�x�s���s�ƥ󪺨�ƫ���
private:
	
};