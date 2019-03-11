#include"Stdafx.h"
#include <iostream>
#include "GameSystem.h"

vector<GameObject> GameSystem::gameObjectList;//��l�ƪ���C��

GameSystem::GameSystem()
{
}

vector<GameObject>& GameSystem::GetAllGameObject()//���o�Ҧ�����
{
	return gameObjectList;
}

void GameSystem::AddGameObject(GameObject& obj)//�W�[�C������
{
	gameObjectList.push_back(obj);
}

GameObject* GameSystem::GetGameObjectWithTag(string tag)//���o�S�w���Ҫ��C������(��@��)
{
	for (auto i = gameObjectList.begin(); i != gameObjectList.end(); i++)
	{
		if (i->GetTag() == tag)
		{
			return &*i;
		}
	}
	return NULL;
}

vector<GameObject*> GameSystem::GetGameObjectsWithTag(string tag)//���o�S�w���Ҫ��C������(�h��)
{
	vector<GameObject*> targetObjects;
	for (auto i = gameObjectList.begin(); i != gameObjectList.end(); i++)
	{
		if (i->GetTag() == tag)
		{
			targetObjects.push_back(&*i);
		}
	}

	return targetObjects;
}

void GameSystem::MoveScreenTopLeft(int dx, int dy)
{
	Map::SetSX(Map::GetSX() + dx);
	Map::SetSY(Map::GetSY() + dy);
}

void GameSystem::SetAllObjectBitMapPosition()//�]�w�Ҧ�����Ϥ���m
{
	for (auto i = gameObjectList.begin(); i != gameObjectList.end(); i++)
	{
		i->SetBitMapPosition();
	}
}

void GameSystem::ShowAllObject()//��ܩҦ�����
{
	for (auto i = gameObjectList.begin(); i != gameObjectList.end(); i++)
	{
		i->ShowBitMap();
	}
}
