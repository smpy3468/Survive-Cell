#pragma once

#include "UInterface.h"

//ButtonOnClickEvent
//���s�ƥ�

class ButtonOnClickEvent
{
public:
	ButtonOnClickEvent();
	~ButtonOnClickEvent();

	static void OnClickStart(CGame* c);//�}�l���s
	static void OnClickExit(CGame* c);//�������s

	enum OnClickEvent
	{
		ON_CLICK_START = 0,
		ON_CLICK_EXIT,
		ON_CLICK_LENGTH
	};

	static vector<void(*)(CGame*)> onClickEventList;//�x�s���s�ƥ󪺨�ƫ���
private:
	
};