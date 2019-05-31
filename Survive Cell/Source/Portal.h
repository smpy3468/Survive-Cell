#pragma once
#include "GameObject.h"
#include "GameSystem.h"
#include "Monster.h"
#include "Player.h"
class Portal :public GameObject
{
public:
	Portal();
	~Portal();
	Portal(string tag, int x, int y, int width, int height, int number);
	int  GetConnectedNumber();
	void Used();          //���a�ϥζǰe��
	void SetBitMapPosition()override;
	void ShowBitMap()override;
	void LoadAni();
private:
	CAnimation* ani;
	Player* player;
	int connectedNumber;   //�ǰe���s��
	Portal* Connected();   //�^�ǥt�@�Ӷǰe�I(�p�G�䤣�� �N�|�^�Ǧۤv)
};