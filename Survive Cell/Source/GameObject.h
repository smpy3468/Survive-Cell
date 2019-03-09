#pragma once

//GameObject
//遊戲物件
//場上所有物件的Base Class

#include "StdAfx.h"
#include <string>
using namespace std;
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
using namespace game_framework;

class GameObject
{
public:
	GameObject();
	
	void SetTag(string tag);
	void SetX(int x);
	void SetY(int y);
	void SetWidth(int width);
	void SetHeight(int height);
	
	string GetTag();
	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();
	
	virtual void LoadBitMap(char* pictureAddress);

protected:
	string tag;//物件標籤
	int x, y;//x,y座標
	int width;//寬度
	int height;//高度

	CMovingBitmap objectPic;//物件圖片
	
};