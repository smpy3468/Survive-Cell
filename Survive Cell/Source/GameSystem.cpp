#include"Stdafx.h"
#include <iostream>
#include "GameSystem.h"

vector<GameObject> GameSystem::gameObjectList;//初始化物件列表

GameSystem::GameSystem()
{
}

vector<GameObject>& GameSystem::GetAllGameObject()//取得所有物件
{
	return gameObjectList;
}

void GameSystem::AddGameObject(GameObject& obj)//增加遊戲物件
{
	gameObjectList.push_back(obj);
}

GameObject* GameSystem::GetGameObjectWithTag(string tag)//取得特定標籤的遊戲物件(單一個)
{
	for (auto& i : gameObjectList)
	{
		if (i.GetTag() == tag)
		{
			return &i;
		}
	}
	return NULL;
}

vector<GameObject*> GameSystem::GetGameObjectsWithTag(string tag)//取得特定標籤的遊戲物件(多個)
{
	vector<GameObject*> targetObjects;
	for (auto& i : gameObjectList)
	{
		if (i.GetTag() == tag)
		{
			targetObjects.push_back(&i);
		}
	}

	return targetObjects;
}

void GameSystem::MoveScreenTopLeft(int dx, int dy)
{
	Map::SetSX(Map::GetSX() + dx);
	Map::SetSY(Map::GetSY() + dy);
}

void GameSystem::SetAllObjectBitMapPosition()//設定所有物件圖片位置
{
	for (auto& i : gameObjectList)
	{
		i.SetBitMapPosition();
	}
}

void GameSystem::ShowAllObject()//顯示所有物件
{
	for (auto i = gameObjectList.begin(); i != gameObjectList.end(); i++)
	{
		i->ShowBitMap();
	}
}


void GameSystem::AutoMove() {
	vector<GameObject*> allMonster = GetGameObjectsWithTag("Monster");
	int monsterAmount = allMonster.size();
	for (int i = 0; i < monsterAmount; i++) {

		if (allMonster[i]->GetLR() == 0)							//如果GetLR == 0 , X 往左移動
			allMonster[i]->SetX(allMonster[i]->GetX() - (1 / 33)); 

		if (allMonster[i]->GetLR() == 1)
			allMonster[i]->SetX(allMonster[i]->GetX() + (1 / 33)); //如果GetLR == ! , X 往右移動

		if (allMonster[i]->GetX() < allMonster[i]->GetdX[0])       //GetdX[0]左邊警戒範圍，如果超過左邊 改右邊移動
			allMonster[i]->SetdX(1);
		else if (allMonster[i]->GetX() > allMonster[i]->GetdX[1]) //GetdX[1]右邊警戒範圍，如果超過右邊 改左邊移動
			allMonster[i]->SetdX(0);

		//GameSystem::GetGameObjectWithTag("Player")->SetX(GameSystem::GetGameObjectWithTag("Player")->GetX() - 10);
	}
}