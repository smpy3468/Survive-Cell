#include"Stdafx.h"
#include "audio.h"
#include "GameSystem.h"
#include "Monster.h"
#include "Floor.h"

vector<GameObject*> GameSystem::gameObjectList;//初始化物件列表
vector<UInterface*> GameSystem::gameUIList;//初始化物件列表
bool GameSystem::isGameOver = false;

GameSystem::GameSystem()
{
}

bool GameSystem::IsGameOver()
{
	return isGameOver;
}

void GameSystem::SetGameOver()
{
	isGameOver = true;
}

vector<GameObject*>& GameSystem::GetAllGameObject()//取得所有物件
{
	return gameObjectList;
}

void GameSystem::AddGameObject(GameObject* obj)//增加遊戲物件
{
	for (unsigned int i = 0; i < gameObjectList.size(); i++)//用圖層進行排序後插入
	{
		if (gameObjectList[i]->GetLayer() >= obj->GetLayer())//相同圖層 或是 更高的圖層
		{
			gameObjectList.insert(gameObjectList.begin() + i, obj);//在此位置加入物件
			return;
		}
	}

	gameObjectList.push_back(obj);//還沒有與此物件相同圖層的物件，將此物件加到最尾端
}

void GameSystem::AddUserInterface(UInterface* ui) {
	gameUIList.push_back(ui);
}


void GameSystem::DeleteGameObject(GameObject * obj)
{
	for (auto i = gameObjectList.begin(); i != gameObjectList.end(); i++)
	{
		if (*i == obj)
		{
			gameObjectList.erase(i);
			return;
		}
	}
}

void GameSystem::DeleteUInterface(UInterface* ui)
{
	for (auto i = gameUIList.begin(); i != gameUIList.end(); i++)
	{
		if (*i == ui)
		{
			gameUIList.erase(i);
			return;
		}
	}
}

void GameSystem::DeleteAllGameObject()
{
	while (!gameObjectList.empty())
	{
		DeleteGameObject(gameObjectList[0]);
	}
}



void GameSystem::DeleteAllUI()
{
	while (!gameUIList.empty())
	{
		DeleteUInterface(gameUIList[0]);
	}
}

void GameSystem::CreateFloor(int x, int y, int width, int height)
{
	for (int currentY = y; currentY < y + height; currentY += FLOOR_HEIGHT)//從y座標開始，持續往下增加地板
	{
		for (int currentX = x; currentX < x + width; currentX += FLOOR_WIDTH)//從x座標開始，持續往右增加地板
		{
			AddGameObject(new Floor("Floor", currentX, currentY, FLOOR_WIDTH, FLOOR_HEIGHT));
		}
	}
}

/*GameObject* GameSystem::GetGameObjectWithTag(string tag)//取得特定標籤的遊戲物件(單一個)
{
	for (auto& i : gameObjectList)
	{
		if (i.GetTag() == tag)
		{
			return &i;
		}
	}
	return NULL;
}*/

/*template <class T>
vector<T*> GameSystem::GetGameObjectsWithTag(string tag)//取得特定標籤的遊戲物件(多個)
{
	vector<T*> targetObjects;
	for (auto& i : gameObjectList)
	{
		if (i.GetTag() == tag)
		{
			targetObjects.push_back(&i);
		}
	}

	return targetObjects;
}*/

void GameSystem::SetAllObjectBitMapPosition()//設定所有物件圖片位置
{
	for (auto& i : gameObjectList)
	{
		i->SetBitMapPosition();
	}
}

void GameSystem::ShowAllObject()//顯示所有物件
{
	for (auto& i : gameObjectList)
	{
		i->ShowBitMap();
	}
}

void GameSystem::ShowAllUI()
{
	for (auto& i : gameUIList)
	{
		i->ShowBitMap();
	}
}

void GameSystem::Load()
{
	CAudio::Instance()->Load(AUDIO::AUDIO_GAME_INIT, ".\\res\\game_init.mp3");
	CAudio::Instance()->Load(AUDIO::AUDIO_GAME_RUN, ".\\res\\game_run.mp3");
	CAudio::Instance()->Load(AUDIO::AUDIO_GAME_OVER, ".\\res\\game_over.mp3");
}

void GameSystem::Init()
{
	isGameOver = false;//重置遊戲狀態
	Map::SetSX(0);
	Map::SetSY(0);
	DeleteAllGameObject();//刪除所有物件
	isGameOver = false;
	DeleteAllGameObject();
	DeleteAllUI();
}

void GameSystem::PlayAudio(AUDIO id)
{
	CAudio::Instance()->Play(id, true);
}

void GameSystem::StopAudio(AUDIO id)
{
	CAudio::Instance()->Stop(id);
}

void GameSystem::MonstersAutoMove() {
	vector<Monster*> allMonster = GameSystem::GetGameObjectsWithTag<Monster>("Monster");
	for (auto& i : allMonster) {
		i->AutoMove();
	}
}

void GameSystem::MonstersAttackPlayer() {
	vector<Monster*> allMonster = GameSystem::GetGameObjectsWithTag<Monster>("Monster");
	for (auto& i : allMonster) {
		i->Attack();
	}
}

void GameSystem::MonstersAct() {
	vector<Monster*> allMonster = GameSystem::GetGameObjectsWithTag<Monster>("Monster");
	for (auto& i : allMonster) {
		i->Act();
	}
}