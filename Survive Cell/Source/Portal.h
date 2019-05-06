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
	void Used();          //當玩家使用
	void SetBitMapPosition()override;
	void ShowBitMap()override;
	void LoadAni();
private:
	CAnimation* ani;
	Player* player;
	int connectedNumber;
	Portal* Connected();   //回傳另一個傳送點(如果找不到 就會回傳自己)
};