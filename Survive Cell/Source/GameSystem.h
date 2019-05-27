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
	static void Exit();//離開遊戲

	enum OVER_MODE
	{
		OVER_WIN,
		OVER_LOSE
	};

	static int GetOverMode();//取得哪種結束模式
	static bool IsGameOver();//是否遊戲結束
	static void SetGameOver(int setOverMode);//設定遊戲結束
	static bool IsNextStage();
	static void SetIsNextStage(bool nextStage);
	static void StagePlusOne();
	static int GetNowStage();

	static vector<GameObject*>& GetAllGameObject();//取得所有遊戲物件
	static void AddGameObject(GameObject* obj);//加入遊戲物件
	static void AddUserInterface(UInterface* ui); //加入UI物件
	static void DeleteGameObject(GameObject* obj);//刪除遊戲物件
	static void DeleteUInterface(UInterface* ui);//刪除UI物件
	static void DeleteAllGameObject();//刪除所有遊戲物件
	static void DeleteAllGameObjectExceptPlayer(); //刪除所有遊戲物件(player除外)
	static void DeleteAllUI();//刪除所有UI物件
	static void CreateFloor(int x, int y, int width, int height);//拼地板，傳入座標與寬高
	static void ChangeToNextStage();

	static double Rand(double maxValue);//亂數
	static double Rand(double minValue, double maxValue);//亂數
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

	template <class T> static vector<T*> GetGameObjectsWithType()//取得特定標籤的遊戲物件(多個)
	{
		vector<T*> targetObjects;
		for (auto& i : gameObjectList)
		{
			if(dynamic_cast<T*>(i)!=NULL)
				targetObjects.push_back(static_cast<T*>(i));
		}

		return targetObjects;
	}

	template <class T> static T* GetGameObjectWithType()//取得特定標籤的遊戲物件(多個)
	{
		for (auto& i : gameObjectList)
		{
			if (dynamic_cast<T*>(i) != NULL)
				return dynamic_cast<T*>(i);
		}
		return NULL;
	}

	template <class T>static T* GetUInterfaceWithType() //取得特定類別的UI(單一個)
	{
		for (auto& i : gameUIList)
		{
			if (dynamic_cast<T*>(i) != NULL)
				return dynamic_cast<T*>(i);
		}
		return NULL;
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

	static void AllObjectAct();//所有物件動作
	static void SetAllObjectBitMapPosition();//設定所有物件的圖片位置
	static void ShowAllObject();//顯示所有物件
	static void ShowAllUI();//顯示所有UI物件

	//------------顯示文字-------------//
	enum ALIGN
	{
		ALIGN_TOP = 0,
		ALIGN_BOTTOM,
		ALIGN_LEFT,
		ALIGN_RIGHT,
		ALIGN_CENTER
	};

	static void ShowText(string text
		, int left = 0, int top = 0, int right = SIZE_X, int bottom = SIZE_Y//矩形的四個點座標
		, int alignHor = ALIGN_LEFT, int alignVer = ALIGN_TOP//顯示文字,對齊方式
		, int fontSize = 16, COLORREF textColor = RGB(0, 0, 0)//字體大小,字體顏色
		, int bkMode = 1, COLORREF bkColor = RGB(255, 255, 255));//背景模式(OPAQUE:不透明, TRANSPARENT:透明),背景顏色

	static void DrawRectangle(int x,int y,int width,int height,COLORREF color);//畫矩形

	//------------音訊相關-------------//
	enum AUDIO
	{
		AUDIO_GAME_INIT = 0,
		AUDIO_GAME_RUN_1,
		AUDIO_GAME_RUN_2,
		AUDIO_GAME_OVER_LOSE,
		AUDIO_GAME_OVER_WIN
	};
	static void PlayAudio(AUDIO id);//播放音樂
	static void StopAudio(AUDIO id);//停止音樂

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

	const static int FLOOR_WIDTH = 20, FLOOR_HEIGHT = 20;

	static int overMode;//以哪種模式結束(玩家死掉?打贏BOSS?)
	static bool isGameOver;//遊戲是否結束
	static bool isNextStage;
	static int  nowStage;

	static const int stage1FloorCount = 35;//第一關地板數量
	static int stage1Floor[stage1FloorCount][4];//第一關的地板，x,y,width,height四個數字

	static bool isLoaded;//是否已載入

};