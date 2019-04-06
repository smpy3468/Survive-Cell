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
#include "UInterface.h"

class GameSystem
{
public:
	GameSystem();
	static void Load();//���J
	static void Init();//��l��

	static bool IsGameOver();//�O�_�C������
	static void SetGameOver();//�]�w�C������

	static vector<GameObject*>& GetAllGameObject();//���o�Ҧ��C������
	static void AddGameObject(GameObject* obj);//�[�J�C������
	static void AddUserInterface(UInterface* ui); //�[�JUI����
	static void DeleteGameObject(GameObject* obj);//�R���C������
	static void DeleteAllGameObject();//�R���Ҧ�����
	
	template <class T> static T* GetGameObjectWithTag(string tag)//���o�S�w���Ҫ��C������(��@��)
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

	template <class T> static vector<T*> GetGameObjectsWithTag(string tag)//���o�S�w���Ҫ��C������(�h��)
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

	static void SetAllObjectBitMapPosition();//�]�w�Ҧ����󪺹Ϥ���m
	static void ShowAllObject();//��ܩҦ�����
	static void ShowAllUI();//��ܩҦ�UI����
	
	//------------���T����-------------//
	enum AUDIO
	{
		AUDIO_GAME_INIT = 0,
		AUDIO_GAME_RUN,
		AUDIO_GAME_OVER
	};
	static void PlayAudio(AUDIO id);//���񭵼�
	static void StopAudio(AUDIO id);//�����

	static void MonstersAutoMove();    //�����Ǫ��bdefenseRange������
	static void MonstersAttackPlayer();//�����Ǫ��bPlayer�i�JattackField�ɷ|�lPlayer


	//------------�ϼh����------------//
	enum LAYER//�ϼh�s��
	{
		LAYER_FLOOR = 0,
		LAYER_ITEM,
		LAYER_MONSTER,
		LAYER_PLAYER
	};
private:
	static vector<GameObject*> gameObjectList;//�s��Ҧ��C�����󪺦C��
	static vector<UInterface*> gameUIList;//�s��Ҧ��C��UI����C��

	static bool isGameOver;//�C���O�_����
};