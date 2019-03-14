#pragma once

//GameSystem
//遊戲系統
//紀錄場上所有物件資訊

#include "StdAfx.h"
#include <vector>
using namespace std;
#include "gamelib.h"
using namespace game_framework;

#include "Map.h"
#include "GameObject.h"

class GameSystem
{
public:
	GameSystem();

	static vector<GameObject>& GetAllGameObject();//取得所有遊戲物件
	static void AddGameObject(GameObject& obj);//加入遊戲物件
	
	template <class T> static T* GetGameObjectWithTag(string tag)//取得特定標籤的遊戲物件(單一個)
	{
		for (auto& i : gameObjectList)
		{
			if (i.GetTag() == tag)
			{
				return static_cast<T*>(&i);
			}
		}
		return NULL;
	}

	template <class T> static vector<T*> GetGameObjectsWithTag(string tag)//取得特定標籤的遊戲物件(多個)
	{
		vector<T*> targetObjects;
		for (auto& i : gameObjectList)
		{
			if (i.GetTag() == tag)
			{
				targetObjects.push_back(static_cast<T*>(&i));
			}
		}

		return targetObjects;
	}

	static void MoveScreenTopLeft(int dx, int dy);//移動螢幕左上角位置
	static void SetAllObjectBitMapPosition();//設定所有物件的圖片位置
	static void ShowAllObject();//顯示所有物件
	
private:
	static vector<GameObject> gameObjectList;//存放所有遊戲物件的列表
	static CMovingBitmap backgroundPic;//背景圖片
};