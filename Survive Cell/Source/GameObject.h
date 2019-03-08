#pragma once

//GameObject
//�C������
//���W�Ҧ�����Base Class

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
	string tag;//�������
	int width;
	int length;

	CMovingBitmap objectPic;
	
};