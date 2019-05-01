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
#include "audio.h"
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
	static void DeleteUInterface(UInterface* ui);//刪除UI物件
	static void DeleteAllGameObject();//刪除所有遊戲物件
	static void DeleteAllGameObjectExcpetPlayer(); //刪除所有遊戲物件(player除外)
	static void DeleteAllUI();//刪除所有UI物件
	static void CreateFloor(int x, int y, int width, int height);//拼地板，傳入座標與寬高
	static void ChangeToStageX(int stageNumber);
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

	template <class T>static T* GetUInterfaceWithTag(string tag) //取得特定標籤的遊戲物件(單一個)
	{
		for (auto& i : gameUIList) {

			int x = i->GetX();
			if (i->GetTag() == tag)
			{
				return static_cast<T*>(i);
			}
		}

		return NULL;
	}

	template <class T>static vector<T*> GetUInterfacesWithTag(string tag) //取得特定標籤的UI物件(多個)
	{
		vector<T*> targetUIs;
		for (auto& i : gameUIList)
		{

			if (typeid(T) == typeid(UInterface))
			{

			}
			if (i->GetTag() == tag)
			{
				targetUIs.push_back(static_cast<T*>(i));
			}

		}
		return targetUIs;
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
	static void MonstersAct();
	static void CreatStage1Object();
	//------------圖層相關------------//
	enum LAYER//圖層編號
	{
		LAYER_DOOR = 0,
		LAYER_FLOOR,
		LAYER_ITEM,
		LAYER_MONSTER,
		LAYER_PLAYER
	};

	//------------裝備ID------------//
	enum EQUIPMENT_ID
	{
		EQUIPMENT_WEAPON,
		EQUIPMENT_TRADITIONAL_SWORD
	};

private:
	static void CreatStage2Object();			//創建第二關(第一關以後要保留UI和Player)


	static vector<GameObject*> gameObjectList;//存放所有遊戲物件的列表
	static vector<UInterface*> gameUIList;//存放所有遊戲UI物件列表

	const static int FLOOR_WIDTH = 80, FLOOR_HEIGHT = 50;
	static bool isGameOver;//遊戲是否結束
};