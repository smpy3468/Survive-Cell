#pragma once

//Door
//��
//�~��GameObject

#include "GameObject.h"

class Door :public GameObject
{
public:
	Door();
	Door(string tag, int x, int y, int width, int height);
	void Kicked();//�Q��
private:
	void Dead()override;
	void ShowBitMap()override;

	bool isRuin;//�O�_�Q�}�a
	CAnimation* ani;
};