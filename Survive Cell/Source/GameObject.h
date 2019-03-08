#pragma once

//GameObject
//遊戲物件
//場上所有物件的Base Class

#include "StdAfx.h"
#include <string>
using namespace std;
using namespace game_frame;

class GameObject
{
public:
	GameObject();
	string GetTag();
	//-----------------Set each of private--------------------//
	void SetTag(string tag);
	void SetWidth(int width);
	void SetLength(int width);
	void LoadBitMap(string pictureAddress);
	//-----------------get each of prive----------------------//

	int GetTag();
	int GetWidth();
	int GetLength();
protected:
	string tag;//物件標籤
	int width;
	int length;

	CMovingBitmap objectPic;
	
};