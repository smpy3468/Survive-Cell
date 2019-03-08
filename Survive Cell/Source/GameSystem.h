#pragma once

//GameSystem
//�C���t��
//�������W�Ҧ������T

#include <vector>
using namespace std;
#include "GameObject.h"

class GameSystem
{
public:
	GameSystem();

	static vector<GameObject>& GetAllGameObject();//���o�Ҧ��C������
	static void AddGameObject(GameObject& obj);//�[�J�C������
	static GameObject* GetGameObjectWithTag(string tag);//���o�S�w���Ҫ��C������(��@��)
	static vector<GameObject*> GetGameObjectsWithTag(string tag);//���o�S�w���Ҫ��C������(�h��)
private:
	static vector<GameObject> gameObjectList;//�s��Ҧ��C�����󪺦C��
};