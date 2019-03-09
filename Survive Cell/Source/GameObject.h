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
#include "resource.h"

class GameObject
{
public:
	GameObject();
	GameObject(string tag, int x, int y, int width, int height, int pictureID);

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

	void LoadBitMap(char* pictureAddress);//�θ��|���J�Ϥ�
	void LoadBitMap(int pictureID);//�νs�����J�Ϥ�
	void SetBitMapPosition();//�]�w�Ϥ���m
	void ShowBitMap();//��ܹϤ�

protected:
	string tag;//�������
	int x, y;//x,y�y��
	int width;//�e��
	int height;//����

	CMovingBitmap objectPic;//����Ϥ�
	int pictureID;//�Ϥ��s��
};