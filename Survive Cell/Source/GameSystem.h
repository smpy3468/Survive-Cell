#pragma once

//GameSystem
//遊戲系統
//紀錄場上所有物件資訊

#include "StdAfx.h"
#include <vector>
using namespace std;
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
using namespace game_framework;

#include "GameObject.h"

class GameSystem
{
public:
	GameSystem();

	static vector<GameObject>& GetAllGameObject();//取得所有遊戲物件
	static void AddGameObject(GameObject& obj);//加入遊戲物件
	static GameObject* GetGameObjectWithTag(string tag);//取得特定標籤的遊戲物件(單一個)
	static vector<GameObject*> GetGameObjectsWithTag(string tag);//取得特定標籤的遊戲物件(多個)

	static void MoveAllObject(int dx, int dy);//移動所有物件

private:
	static vector<GameObject> gameObjectList;//存放所有遊戲物件的列表
	static CMovingBitmap backgroundPic;//背景圖片
};