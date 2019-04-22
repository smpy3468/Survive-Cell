#include"Stdafx.h"
#include "audio.h"
#include "GameSystem.h"
#include "Monster.h"
#include "Floor.h"

vector<GameObject*> GameSystem::gameObjectList;//��l�ƪ���C��
vector<UInterface*> GameSystem::gameUIList;//��l�ƪ���C��
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
	for (unsigned int i = 0; i < gameObjectList.size(); i++)//�ιϼh�i��Ƨǫᴡ�J
	{
		if (gameObjectList[i]->GetLayer() >= obj->GetLayer())//�ۦP�ϼh �άO �󰪪��ϼh
		{
			gameObjectList.insert(gameObjectList.begin() + i, obj);//�b����m�[�J����
			return;
		}
	}

	gameObjectList.push_back(obj);//�٨S���P������ۦP�ϼh������A�N������[��̧���
}

void GameSystem::AddUserInterface(UInterface* ui) {
	gameUIList.push_back(ui);
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

void GameSystem::DeleteUInterface(UInterface* ui)
{
	for (auto i = gameUIList.begin(); i != gameUIList.end(); i++)
	{
		if (*i == ui)
		{
			gameUIList.erase(i);
			return;
		}
	}
}

void GameSystem::DeleteAllGameObject()
{
	while (!gameObjectList.empty())
	{
		DeleteGameObject(gameObjectList[0]);
	}
}



void GameSystem::DeleteAllUI()
{
	while (!gameUIList.empty())
	{
		DeleteUInterface(gameUIList[0]);
	}
}

void GameSystem::CreateFloor(int x, int y, int width, int height)
{
	for (int currentY = y; currentY < y + height; currentY += FLOOR_HEIGHT)//�qy�y�ж}�l�A���򩹤U�W�[�a�O
	{
		for (int currentX = x; currentX < x + width; currentX += FLOOR_WIDTH)//�qx�y�ж}�l�A���򩹥k�W�[�a�O
		{
			AddGameObject(new Floor("Floor", currentX, currentY, FLOOR_WIDTH, FLOOR_HEIGHT));
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

void GameSystem::ShowAllUI()
{
	for (auto& i : gameUIList)
	{
		i->ShowBitMap();
	}
}

void GameSystem::Load()
{
	CAudio::Instance()->Load(AUDIO::AUDIO_GAME_INIT, ".\\res\\game_init.mp3");
	CAudio::Instance()->Load(AUDIO::AUDIO_GAME_RUN, ".\\res\\game_run.mp3");
	CAudio::Instance()->Load(AUDIO::AUDIO_GAME_OVER, ".\\res\\game_over.mp3");
}

void GameSystem::Init()
{
	isGameOver = false;//���m�C�����A
	Map::SetSX(0);
	Map::SetSY(0);
	DeleteAllGameObject();//�R���Ҧ�����
	isGameOver = false;
	DeleteAllGameObject();
	DeleteAllUI();
}

void GameSystem::PlayAudio(AUDIO id)
{
	CAudio::Instance()->Play(id, true);
}

void GameSystem::StopAudio(AUDIO id)
{
	CAudio::Instance()->Stop(id);
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

void GameSystem::MonstersAct() {
	vector<Monster*> allMonster = GameSystem::GetGameObjectsWithTag<Monster>("Monster");
	for (auto& i : allMonster) {
		i->Act();
	}
}