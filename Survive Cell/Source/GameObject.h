#pragma once

//GameObject
//�C������
//���W�Ҧ�����Base Class

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
	string tag;//�������
	int x, y;//x,y�y��
	int width;//�e��
	int height;//����

	CMovingBitmap objectPic;//����Ϥ�
	
};