#pragma once

#include "Button.h"

//ButtonStart
//�}�l���s

class ButtonStart:public Button
{
public:
	ButtonStart();
	ButtonStart(string tag, int x, int y, int width, int height);
	~ButtonStart();

	void OnClick()override;

private:
	void LoadAni()override;
};