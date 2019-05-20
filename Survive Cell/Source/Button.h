#pragma once

#include "UInterface.h"

//Button
//«ö¶s

class Button:public UInterface
{
public:
	Button();
	Button(string tag, int x, int y, int width, int height);
	~Button();

	void Dead();
	virtual void OnClick();
	void SetBitMapPosition();
	void ShowBitMap();

private:
	virtual void LoadAni();
};