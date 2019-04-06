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
#include "UInterface.h"

class GameSystem
{
public:
	GameSystem();
	static void Load();//載入
	static void Init();//初始化

	static bool IsGameOver();//是否遊戲結束
	static void SetGameOver();//設定遊戲結束

	static vector<GameObject*>& GetAllGameObject();//取得所有遊戲物件
	static void AddGameObject(GameObject* obj);//加入遊戲物件
	static void AddUserInterface(UInterface* ui); //加入UI物件
	static void DeleteGameObject(GameObject* obj);//刪除遊戲物件
	static void DeleteAllGameObject();//刪除所有物件
	
	template <class T> static T* GetGameObjectWithTag(string tag)//取得特定標籤的遊戲物件(單一個)
	{
		for (auto& i : gameObjectList)
		{
			if (i->GetTag() == tag)
			{
				return static_cast<T*>(i);
			}
		}
		return NULL;
	}

	template <class T> static vector<T*> GetGameObjectsWithTag(string tag)//取得特定標籤的遊戲物件(多個)
	{
		vector<T*> targetObjects;
		for (auto& i : gameObjectList)
		{
			if (typeid(T) == typeid(GameObject))
			{

			}
			if (i->GetTag() == tag)
			{
				targetObjects.push_back(static_cast<T*>(i));
			}
		}

		return targetObjects;
	}

	static void SetAllObjectBitMapPosition();//設定所有物件的圖片位置
	static void ShowAllObject();//顯示所有物件
	static void ShowAllUI();//顯示所有UI物件
	
	//------------音訊相關-------------//
	enum AUDIO
	{
		AUDIO_GAME_INIT = 0,
		AUDIO_GAME_RUN,
		AUDIO_GAME_OVER
	};
	static void PlayAudio(AUDIO id);//播放音樂
	static void StopAudio(AUDIO id);//停止音樂

	static void MonstersAutoMove();    //全部怪物在defenseRange內移動
	static void MonstersAttackPlayer();//全部怪物在Player進入attackField時會追Player


	//------------圖層相關------------//
	enum LAYER//圖層編號
	{
		LAYER_FLOOR = 0,
		LAYER_ITEM,
		LAYER_MONSTER,
		LAYER_PLAYER
	};
private:
	static vector<GameObject*> gameObjectList;//存放所有遊戲物件的列表
	static vector<UInterface*> gameUIList;//存放所有遊戲UI物件列表

	static bool isGameOver;//遊戲是否結束
};