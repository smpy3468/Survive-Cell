#pragma once

//Map
//地圖
//座標系統管理

#include "gamelib.h"

class Map
{
public:
	Map();
	static void SetStaticObject();//設定不會移動的物件座標，只會在遊戲一開始呼叫
	static void SetDynamicObject();//設定會移動的物件座標(玩家、怪物)
	static bool HasObject(int x, int y);//該座標是否有物件
private:
	static bool coordinate[SIZE_X][SIZE_Y];//紀錄哪個座標有物件
};