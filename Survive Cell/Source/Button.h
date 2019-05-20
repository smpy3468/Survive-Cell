#pragma once

#include "UInterface.h"

//Button
//���s

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

	int myOnClickEvent;//�o�����s��OnClick�ƥ�O���@��

	static vector<void(*)(CGame*)> onClickEventList;//�x�s���s�ƥ󪺨�ƫ���
	static void OnClickStart(CGame* c);//�}�l���s
	static void OnClickExit(CGame* c);//�������s
};