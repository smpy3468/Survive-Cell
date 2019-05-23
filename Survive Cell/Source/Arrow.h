#pragma once
#include "Effect.h"
class Arrow :public Effect
{
public:
	Arrow(string tag, int x, int y, int width, int height);
	Arrow::Arrow(string tag, int x, int y, int width, int height, int attackRange, int direction);
	~Arrow();
	void ShowBitMap()override;	//顯示動畫

private:
	void LoadAni()override;
	void Fall(); //讓箭有落下的效果
	int initX, initY;   //箭初始的位置
	int dX, dY;				//每次下降多往前多少
	int direction;			//方向

	enum ANI {
		ANI_ARROW_IDLE = 0,
		ANI_ARROW_LEFT,
		ANI_ARROW_RIGHT
	};
};