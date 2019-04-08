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

		void SetX(int x);													//設定UI的X座標
		void SetY(int y);													//設定UI的Y座標
		void SetWidth(int width);											//設定UI的width
		void SetHeight(int height);											//設定UI的Height

		string GetTag();													//回傳Tag
		int GetX();															//回傳UI的X座標
		int GetY();															//回傳UI的Y座標
		int GetWidth();													    //回傳UI的width
		int GetHeight();												    //回傳UI的height

		virtual void ShowBitMap();													//顯示UI圖片

	protected:
		CMovingBitmap UIpicture;											//儲存UI圖片
		vector<string> UItexts;												//儲存UI文字
		string tag;															//分類tag
		int x, y;															//座標	
		int width, height;													//寬、高
		
		vector<CAnimation*> ani;											//儲存動畫(有必要的話)
		void AddAniBitMaps(char* pic[], int aniType, int picCount);			//增加多張動畫圖片(有必要的話)
		void AddAniBitMap(char* pic, int aniType);							//增加動畫圖片(有必要的話)
		void LoadBitMap(int pictureID);										//加入UI圖片-方法1
		void LoadBitMap(char* picAddress);									//加入UI圖片-方法
		
		virtual void LoadAni();												//載入動畫
		
};

