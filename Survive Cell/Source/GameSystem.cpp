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

void GameSystem::MoveAllObject(int dx, int dy)//���ʩҦ�����(�Ω���ܿù��ݨ쪺�e��)
{
	for (auto i = gameObjectList.begin(); i != gameObjectList.end(); i++)
	{
		i->SetX(i->GetX() + dx);//���ʨ�쥻��x�y��+dx����m
		i->SetY(i->GetY() + dy);//���ʨ�쥻��y�y��+dy����m
	}
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
