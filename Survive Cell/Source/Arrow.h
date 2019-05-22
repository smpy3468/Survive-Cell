#pragma once
#include "Effect.h"
class Arrow :public Effect
{
public:
	Arrow(string tag, int x, int y, int width, int height);
	Arrow::Arrow(string tag, int x, int y, int width, int height, int attackRange, int direction);
	~Arrow();
	void ShowBitMap()override;	//��ܰʵe

private:
	void LoadAni()override;
	
	int targetX, targetY;   //�b���a����m
	int dX, dY;
	int direction;

	enum ANI {
		ANI_ARROW_IDLE = 0,
		ANI_ARROW_LEFT,
		ANI_ARROW_RIGHT
	};
};