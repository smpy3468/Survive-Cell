#include"Stdafx.h"
#include "GameSystem.h"
#include "Monster.h"
#include "Player.h"
#include "GameObject.h"
#include "UInterface.h"
#include "gamelib.h"
#include "Map.h"
#include "GameObject.h"
#include "Character.h"
#include "Player.h"
#include "Floor.h"
#include "Item.h"
#include "Fire.h"
#include "Demon.h"
#include "EquipedSlot.h"
#include "UIBlood.h"
#include "UIMonsterBlood.h"
#include "Door.h"
#include "Goal.h"
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

void GameSystem::ShowText(string text, string alignHor, string alignVer, int fontSize, COLORREF textColor, int dx, int dy, int bkMode, COLORREF bkColor)
{
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f, *fp;
	f.CreatePointFont(fontSize * 10, "Times New Roman");	// ���� font f; 160���16 point���r
	fp = pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkMode(bkMode);
	pDC->SetBkColor(bkColor);
	pDC->SetTextColor(textColor);

	char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
	sprintf(str, text.c_str());

	CRect rect = { dx,dy,SIZE_X,SIZE_Y };//�]�w�x�Υ��B�W�B�k�B�U���y��	

	if (alignVer == "TOP")//�W
	{
		if (alignHor == "LEFT")
		{
			pDC->DrawText(str, rect, DT_LEFT | DT_WORDBREAK);//�a������A�i����
		}
		else if (alignHor == "CENTER")
		{
			pDC->DrawText(str, rect, DT_CENTER | DT_WORDBREAK);//�a������A�i����
		}
		else if (alignHor == "RIGHT")
		{
			pDC->DrawText(str, rect, DT_RIGHT | DT_WORDBREAK);//�a�k����A�i����
		}
	}

	else if (alignVer == "CENTER")
	{
		//�o�̦b�]�w�����m��
		CRect temp = rect;
		int height = pDC->DrawText(str, temp, DT_CENTER | DT_WORDBREAK | DT_CALCRECT);
		rect.top += (rect.Height() - height) / 2;
		//rect.DeflateRect(0, (rect.Height() - height) / 2);

		if (alignHor == "LEFT")
		{
			pDC->DrawText(str, rect, DT_LEFT | DT_WORDBREAK);//�a������A�i����
		}
		else if (alignHor == "CENTER")
		{
			pDC->DrawText(str, rect, DT_CENTER | DT_WORDBREAK);
		}
		else if (alignHor == "RIGHT")
		{
			pDC->DrawText(str, rect, DT_RIGHT | DT_WORDBREAK);//�a�k����A�i����
		}
	}

	else if (alignVer == "BOTTOM")
	{
		//�o�̦b�]�w�����m�U
		CRect temp = rect;
		int height = pDC->DrawText(str, temp, DT_WORDBREAK | DT_CALCRECT);
		rect.top += rect.Height() - height;
		//rect.DeflateRect(0, (rect.Height() - height));

		if (alignHor == "LEFT")
		{
			pDC->DrawText(str, rect, DT_LEFT | DT_WORDBREAK);//�a������A�i����
		}
		else if (alignHor == "CENTER")
		{
			pDC->DrawText(str, rect, DT_CENTER | DT_WORDBREAK);
		}
		else if (alignHor == "RIGHT")
		{
			pDC->DrawText(str, rect, DT_RIGHT | DT_WORDBREAK);//�a�k����A�i����
		}
	}

	//pDC->DrawText(str, rect, DT_CENTER | DT_WORDBREAK);

	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
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

void GameSystem::ChangeToStageX(int stageNumber)
{
	GameSystem::Init();
	if (stageNumber == 1) {
		CreatStage1Object();
	}


}

void GameSystem::CreatStage1Object()
{

	GameSystem::AddGameObject((new Player("Player", SIZE_X / 2, SIZE_Y / 2 - 100, 50, 80)));
	GameSystem::AddGameObject((new Demon("Monster", SIZE_X / 2 + 100, SIZE_Y / 2 - 133, 131, 141)));
	GameSystem::AddGameObject((new Demon("Monster", SIZE_X / 2 - 150, SIZE_Y / 2 - 133, 131, 141)));

	GameSystem::AddGameObject(new Floor("Ground", 0, Map::WORLD_SIZE_Y - 100, Map::WORLD_SIZE_X, 100, IDB_GROUND));//�a�ϳ̤U�誺�a�O
	GameSystem::AddGameObject(new Floor("Floor", 0, Map::WORLD_SIZE_Y - 100, Map::WORLD_SIZE_X, 100, IDB_GROUND));//�a�ϳ̤U�誺�a�O

	GameSystem::AddGameObject(new Door("Door", 100, Map::WORLD_SIZE_Y - 200, 10, 100));//��
	GameSystem::AddGameObject(new Goal("Gaol", 100, Map::WORLD_SIZE_Y - 200, 143, 212));
	GameSystem::CreateFloor(SIZE_X / 2, SIZE_Y / 2 + 400, 1000, 80);

	GameSystem::CreateFloor(SIZE_X / 2, Map::WORLD_SIZE_Y / 2 + 400, 1000, 80);
	GameSystem::CreateFloor(SIZE_X / 2 + 1000, Map::WORLD_SIZE_Y / 2 + 450, 300, 80);
	GameSystem::CreateFloor(SIZE_X / 2 + 1000 + 300, Map::WORLD_SIZE_Y / 2 + 400, 1000, 80);
	GameSystem::CreateFloor(SIZE_X / 2 - 400, Map::WORLD_SIZE_Y - 150, 300, 80);

	GameSystem::CreateFloor(SIZE_X / 2 + 900, Map::WORLD_SIZE_Y / 2, 300, 80);
	GameSystem::CreateFloor(SIZE_X / 2 + 600, Map::WORLD_SIZE_Y / 2 + 100, 300, 80);
	GameSystem::CreateFloor(SIZE_X / 2 + 300, Map::WORLD_SIZE_Y / 2 + 200, 300, 80);


	GameSystem::AddUserInterface(new EquipedSlot("EquipedSlot", SIZE_X / 10 - 100, SIZE_Y * 9 / 10, 64, 60));
	GameSystem::AddUserInterface(new EquipedSlot("EquipedSlot", SIZE_X / 10 - 10, SIZE_Y * 9 / 10, 64, 60));
	GameSystem::AddUserInterface(new UIBlood("UIBlood", 0, 0, 400, 30));
	GameSystem::AddUserInterface(new UIMonsterBlood("UIMonster", 0, 0, 0, 0));
	Map::SetStaticObject();
}

