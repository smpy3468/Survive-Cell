#pragma once

//Map
//地圖
//座標系統管理

#include "gamelib.h"
using namespace game_framework;

class Map
{
public:
	Map();

	static void Init();//初始化
	static void Load();//載入地圖
	static void ShowStartMenu();//顯示開始選單
	static void ShowBackgroundPic();//顯示背景圖片

	static int GetSX();//取得螢幕左上角X座標
	static int GetSY();//取得螢幕左上角Y座標

	static void SetSX(int x);//設定螢幕左上角X座標
	static void SetSY(int y);//設定螢幕左上角Y座標

	static void MoveScreenTopLeft(int dx, int dy);//移動螢幕左上角位置

	static void SetStaticObject();//設定不會移動的物件座標，只會在遊戲一開始呼叫
	static bool HasObject(int x, int y);//該座標是否有物件

	static const int WORLD_SIZE_X = 6 * 640, WORLD_SIZE_Y = 4 * 480;//整個遊戲地圖的長寬
private:
	static bool coordinate[WORLD_SIZE_X][WORLD_SIZE_Y];//紀錄哪個座標有物件
	static int sx, sy;//螢幕左上角的座標在地圖座標的哪裡
	static CMovingBitmap startMenu;//開始選單
	static CMovingBitmap backgroundPic;//背景圖片
};