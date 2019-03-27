#pragma once

//GameObject
//遊戲物件
//場上所有物件的Base Class

#include "StdAfx.h"
#include <string>
using namespace std;
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

	void LoadBitMap(char* pictureAddress);//用路徑載入圖片
	void LoadBitMap(int pictureID);//用編號載入圖片
	virtual void SetBitMapPosition();//設定圖片位置
	virtual void ShowBitMap();//顯示圖片

	bool IsAnthorObjectInRange(GameObject* object); //object是否與此物件有重疊

protected:
	string tag;//物件標籤
	int x, y;//x,y座標
	int width;//寬度
	int height;//高度

	virtual void Dead();//消滅時呼叫

	CMovingBitmap objectPic;//物件圖片
	int pictureID;//圖片編號
};