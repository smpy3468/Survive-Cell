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

	void SetBitMapPosition()override;
private:
	void Dead()override;
	
	void ShowBitMap()override;
	void LoadAni();//���J�Ϥ�
	bool isRuin;//�O�_�Q�}�a
	CAnimation* ani;
};