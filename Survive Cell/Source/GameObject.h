#pragma once

//GameObject
//遊戲物件
//場上所有物件的Base Class

#include "StdAfx.h"
#include <string>
#include "gamelib.h"
using namespace std;
using namespace game_framework;

class GameObject
{
public:
	GameObject();
	
	//-----------------Set each of private--------------------//
	void SetTag(string tag);
	void SetWidth(int width);
	void SetLength(int width);
	virtual void LoadBitMap(string pictureAddress);
	//-----------------get each of prive----------------------//
	string GetTag();
	int GetWidth();
	int GetLength();
	
protected:
	string tag;//物件標籤
	int width;
	int length;

	CMovingBitmap objectPic;
	
};