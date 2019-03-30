#include"Stdafx.h"
#include <iostream>
#include "GameSystem.h"
#include "Monster.h"

vector<GameObject*> GameSystem::gameObjectList;//��l�ƪ���C��
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

vector<GameObject*>& GameSystem::GetAllGameObject()//���o�Ҧ�����
{
	return gameObjectList;
}

void GameSystem::AddGameObject(GameObject* obj)//�W�[�C������
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

/*GameObject* GameSystem::GetGameObjectWithTag(string tag)//���o�S�w���Ҫ��C������(��@��)
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
vector<T*> GameSystem::GetGameObjectsWithTag(string tag)//���o�S�w���Ҫ��C������(�h��)
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

void GameSystem::SetAllObjectBitMapPosition()//�]�w�Ҧ�����Ϥ���m
{
	for (auto& i : gameObjectList)
	{
		i->SetBitMapPosition();
	}
}

void GameSystem::ShowAllObject()//��ܩҦ�����
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

