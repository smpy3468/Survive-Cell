#pragma once

#include "Button.h"

//ButtonExit
//���}���s

class ButtonExit:public Button
{
public:
	ButtonExit();
	ButtonExit(string tag, int x, int y, int width, int height);
	~ButtonExit()override;

	void OnClick()override;

private:
	void LoadAni()override;
};