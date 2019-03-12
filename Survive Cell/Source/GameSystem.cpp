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
	for (auto& i : gameObjectList)
	{
		if (i.GetTag() == tag)
		{
			return &i;
		}
	}
	return NULL;
}

vector<GameObject*> GameSystem::GetGameObjectsWithTag(string tag)//���o�S�w���Ҫ��C������(�h��)
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

void GameSystem::SetAllObjectBitMapPosition()//�]�w�Ҧ�����Ϥ���m
{
	for (auto& i : gameObjectList)
	{
		i.SetBitMapPosition();
	}
}

void GameSystem::ShowAllObject()//��ܩҦ�����
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

		if (allMonster[i]->GetLR() == 0)							//�p�GGetLR == 0 , X ��������
			allMonster[i]->SetX(allMonster[i]->GetX() - (1 / 33)); 

		if (allMonster[i]->GetLR() == 1)
			allMonster[i]->SetX(allMonster[i]->GetX() + (1 / 33)); //�p�GGetLR == ! , X ���k����

		if (allMonster[i]->GetX() < allMonster[i]->GetdX[0])       //GetdX[0]����ĵ�ٽd��A�p�G�W�L���� ��k�䲾��
			allMonster[i]->SetdX(1);
		else if (allMonster[i]->GetX() > allMonster[i]->GetdX[1]) //GetdX[1]�k��ĵ�ٽd��A�p�G�W�L�k�� �索�䲾��
			allMonster[i]->SetdX(0);

		//GameSystem::GetGameObjectWithTag("Player")->SetX(GameSystem::GetGameObjectWithTag("Player")->GetX() - 10);
	}
}