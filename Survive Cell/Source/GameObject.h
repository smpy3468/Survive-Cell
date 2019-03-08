#pragma once

//GameObject
//�C������
//���W�Ҧ�����Base Class

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
	string tag;//�������
	int width;
	int length;

	CMovingBitmap objectPic;
	
};