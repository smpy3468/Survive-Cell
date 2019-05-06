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
#include "audio.h"
#include "GameObject.h"
#include "UInterface.h"

class GameSystem
{
public:
	GameSystem();
	static void Load();//���J
	static void Init();//��l��
	static void Exit();//���}�C��

	static bool IsGameOver();//�O�_�C������
	static void SetGameOver();//�]�w�C������
	static bool IsNextStage();
	static void SetIsNextStage(bool nextStage);
	static void StagePlusOne();

	static vector<GameObject*>& GetAllGameObject();//���o�Ҧ��C������
	static void AddGameObject(GameObject* obj);//�[�J�C������
	static void AddUserInterface(UInterface* ui); //�[�JUI����
	static void DeleteGameObject(GameObject* obj);//�R���C������
	static void DeleteUInterface(UInterface* ui);//�R��UI����
	static void DeleteAllGameObject();//�R���Ҧ��C������
	static void DeleteAllGameObjectExceptPlayer(); //�R���Ҧ��C������(player���~)
	static void DeleteAllUI();//�R���Ҧ�UI����
	static void CreateFloor(int x, int y, int width, int height);//���a�O�A�ǤJ�y�лP�e��
	static void ChangeToNextStage();
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

	template <class T>static T* GetUInterfaceWithTag(string tag) //���o�S�w���Ҫ��C������(��@��)
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

	template <class T>static vector<T*> GetUInterfacesWithTag(string tag) //���o�S�w���Ҫ�UI����(�h��)
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

	static void SetAllObjectBitMapPosition();//�]�w�Ҧ����󪺹Ϥ���m
	static void ShowAllObject();//��ܩҦ�����
	static void ShowAllUI();//��ܩҦ�UI����

	//------------��ܤ�r-------------//
	enum ALIGN
	{
		ALIGN_TOP = 0,
		ALIGN_BOTTOM,
		ALIGN_LEFT,
		ALIGN_RIGHT,
		ALIGN_CENTER
	};

	static void ShowText(string text
		, int left = 0, int top = 0, int right = SIZE_X, int bottom = SIZE_Y//�x�Ϊ��|���I�y��
		, int alignHor = ALIGN_LEFT, int alignVer = ALIGN_TOP//��ܤ�r,����覡
		, int fontSize = 16, COLORREF textColor = RGB(0, 0, 0)//�r��j�p,�r���C��
		, int bkMode = 1, COLORREF bkColor = RGB(255, 255, 255));//�I���Ҧ�(OPAQUE:���z��, TRANSPARENT:�z��),�I���C��

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
	static void MonstersAct();
	static void CreatStage1Object();
	//------------�ϼh����------------//
	enum LAYER//�ϼh�s��
	{
		LAYER_DOOR = 0,
		LAYER_FLOOR,
		LAYER_ITEM,
		LAYER_MONSTER,
		LAYER_PLAYER
	};

	//------------�˳�ID------------//
	enum EQUIPMENT_ID
	{
		EQUIPMENT_WEAPON,
		EQUIPMENT_TRADITIONAL_SWORD
	};

private:
	static void CreatStage2Object();			//�ЫزĤG��(�Ĥ@���H��n�O�dUI�MPlayer)


	static vector<GameObject*> gameObjectList;//�s��Ҧ��C�����󪺦C��
	static vector<UInterface*> gameUIList;//�s��Ҧ��C��UI����C��

	const static int FLOOR_WIDTH = 20, FLOOR_HEIGHT = 20;
	static bool isGameOver;//�C���O�_����
	static bool isNextStage;
	static int  nowStage;

	static const int stage1FloorCount = 35;//�Ĥ@���a�O�ƶq
	static int stage1Floor[stage1FloorCount][4];//�Ĥ@�����a�O�Ax,y,width,height�|�ӼƦr

};