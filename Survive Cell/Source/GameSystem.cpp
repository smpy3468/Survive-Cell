#include"Stdafx.h"
#include <iostream>
#include "GameSystem.h"
#include "Monster.h"

vector<GameObject*> GameSystem::gameObjectList;//初始化物件列表
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
	gameObjectList.push_back(obj);
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

