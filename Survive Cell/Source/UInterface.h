#pragma once
#include "StdAfx.h"

#include <string>
using namespace std;
#include "gamelib.h"
using namespace game_framework;
#include "resource.h"

class UInterface{
	public:
		UInterface();
		UInterface(string tag, int x, int y, int width, int height);

		void SetX(int x);
		void SetY(int y);
		void SetWidth(int width);
		void SetHeight(int height);

		int GetX();
		int GetY();
		int GetWidth();
		int GetHeight();

		void ShowBitMap();

	protected:
		CMovingBitmap UIpicture;
		vector<string> UItext;
		string tag;
		int x, y;
		int width, height; 
		
		vector<CAnimation*> ani;
		void AddAniBitMaps(char* pic[], int aniType, int picCount);					//增加多張動畫圖片
		void AddAniBitMap(char* pic, int aniType);									//增加動畫圖片
		void LoadBitMap(int pictureID);
		void LoadBitMap(char* picAddress);
		

		virtual void LoadAni();														//載入動畫
		
};

