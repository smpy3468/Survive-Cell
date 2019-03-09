#pragma once

//GameSystem
//�C���t��
//�������W�Ҧ������T

#include "StdAfx.h"
#include <vector>
using namespace std;
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
using namespace game_framework;

#include "GameObject.h"

class GameSystem
{
public:
	GameSystem();

	static vector<GameObject>& GetAllGameObject();//���o�Ҧ��C������
	static void AddGameObject(GameObject& obj);//�[�J�C������
	static GameObject* GetGameObjectWithTag(string tag);//���o�S�w���Ҫ��C������(��@��)
	static vector<GameObject*> GetGameObjectsWithTag(string tag);//���o�S�w���Ҫ��C������(�h��)

	static void MoveAllObject(int dx, int dy);//���ʩҦ�����

private:
	static vector<GameObject> gameObjectList;//�s��Ҧ��C�����󪺦C��
	static CMovingBitmap backgroundPic;//�I���Ϥ�
};