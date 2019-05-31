#pragma once

#include "UInterface.h"
#include "ButtonOnClickEvent.h"

//Button
//���s

class Button :public UInterface
{
public:
	Button();
	Button(string tag, int x, int y, int width, int height, int onClickEvent);
	~Button();

	void Dead();
	bool (*OnClick)(CGame* c);//���U���ƥ�
	void SetBitMapPosition();
	void ShowBitMap();

private:
	virtual void LoadAni();

	int myOnClickEvent;//�o�����s��OnClick�ƥ�O���@��
};