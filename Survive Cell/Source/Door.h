#pragma once

//Door
//��
//�~��GameObject

#include "GameObject.h"
#include "GameSystem.h"
#include "Monster.h"
#include "Player.h"
class Door :public GameObject
{
public:
	Door();
	Door(string tag, int x, int y, int width, int height);
	void Kicked();//�Q��
	bool GetRuin();


	void SetBitMapPosition()override;
private:
	const int LEFT = 1, RIGHT = 2;
	void Dead()override;
	void DazeMonster();
	void ShowBitMap()override;
	void LoadAni();//���J�Ϥ�
	bool isRuin;//�O�_�Q�}�a
	int lr; //�Q�}�a�ɪ����X�h����V
	CAnimation* ani;

	int stunRangeX, stunRangeY;
};