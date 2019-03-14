#pragma once

//GameSystem
//�C���t��
//�������W�Ҧ������T

#include "StdAfx.h"
#include <vector>
using namespace std;
#include "gamelib.h"
using namespace game_framework;

#include "Map.h"
#include "GameObject.h"

class GameSystem
{
public:
	GameSystem();

	static vector<GameObject>& GetAllGameObject();//���o�Ҧ��C������
	static void AddGameObject(GameObject& obj);//�[�J�C������
	
	template <class T> static T* GetGameObjectWithTag(string tag)//���o�S�w���Ҫ��C������(��@��)
	{
		for (auto& i : gameObjectList)
		{
			if (i.GetTag() == tag)
			{
				return static_cast<T*>(&i);
			}
		}
		return NULL;
	}

	template <class T> static vector<T*> GetGameObjectsWithTag(string tag)//���o�S�w���Ҫ��C������(�h��)
	{
		vector<T*> targetObjects;
		for (auto& i : gameObjectList)
		{
			if (i.GetTag() == tag)
			{
				targetObjects.push_back(static_cast<T*>(&i));
			}
		}

		return targetObjects;
	}

	static void MoveScreenTopLeft(int dx, int dy);//���ʿù����W����m
	static void SetAllObjectBitMapPosition();//�]�w�Ҧ����󪺹Ϥ���m
	static void ShowAllObject();//��ܩҦ�����
	
private:
	static vector<GameObject> gameObjectList;//�s��Ҧ��C�����󪺦C��
	static CMovingBitmap backgroundPic;//�I���Ϥ�
};