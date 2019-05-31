#pragma once

#include "UInterface.h"
#include "ButtonOnClickEvent.h"

//Button
//按鈕

class Button :public UInterface
{
public:
	Button();
	Button(string tag, int x, int y, int width, int height, int onClickEvent);
	~Button();

	void Dead();
	bool (*OnClick)(CGame* c);//按下的事件
	void SetBitMapPosition();
	void ShowBitMap();

private:
	virtual void LoadAni();

	int myOnClickEvent;//這顆按鈕的OnClick事件是哪一個
};