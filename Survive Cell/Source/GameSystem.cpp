#include"Stdafx.h"
#include <functional>
#include <random>
#include <gdiplus.h>
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
#include "Boss.h"
#include "Portal.h"
#include "Treasure.h"

vector<GameObject*> GameSystem::gameObjectList;//初始化物件列表
vector<UInterface*> GameSystem::gameUIList;//初始化物件列表
bool GameSystem::isGameOver = false;
bool GameSystem::isNextStage = false;
int  GameSystem::nowStage = 0;
bool GameSystem::isLoaded = false;
int GameSystem::stage1Floor[stage1FloorCount][4] =
{
	{0,600,710,120},{ 0, 720, 710, 640 },{ 330, 400, 410, 80 },{ 890, 170, 200, 45 },{ 1090, 600, 850, 120 }
,{ 1090, 0, 65, 490 },{ 0, 1360, 310, 205 },{ 650, 1360, 60, 150 },{ 710, 910, 220, 45 },{ 825, 1150, 180, 35 }
,{ 710, 1325, 120, 35 },{ 920, 710, 170, 35 },{ 1090, 720, 850, 280 },{ 1090, 1110, 850, 260 },{ 1530, 1000, 410, 110 }
,{ 1570, 1370, 100, 195 },{ 1115, 380, 455, 35 },{ 1315, 170, 170, 95 },{ 1425, 170, 275, 50 },{ 1700, 120, 80, 480 }
,{ 2160, 600, 1680, 120 },{ 1890, 445, 610, 35 },{ 2160, 720, 310, 650 },{ 2230, 1370, 140, 75 },{ 2700, 720, 520, 110 }
,{ 3080, 830, 140, 130 },{ 2700, 960, 520, 320 },{ 2140, 0, 1700, 60 },{ 2140, 210, 930, 70 },{ 2630, 60, 80, 95 }
,{ 3260, 60, 580, 360 },{ 3380, 420, 100, 60 },{ 2830, 410, 80, 190 },{ 2630, 460, 200, 50 },{ 2910, 410, 160, 40 }
};

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


bool GameSystem::IsNextStage()
{
	return isNextStage;
}

void GameSystem::SetIsNextStage(bool nextStage)
{
	isNextStage = nextStage;
}

void GameSystem::StagePlusOne()
{
	nowStage = nowStage + 1;
}

vector<GameObject*>& GameSystem::GetAllGameObject()//取得所有物件
{
	return gameObjectList;
}

void GameSystem::AddGameObject(GameObject* obj)//增加遊戲物件
{
	for (unsigned int i = 0; i < gameObjectList.size(); i++)//用圖層進行排序後插入
	{
		if (gameObjectList[i]->GetLayer() >= obj->GetLayer())//相同圖層 或是 更高的圖層
		{
			gameObjectList.insert(gameObjectList.begin() + i, obj);//在此位置加入物件
			return;
		}
	}

	gameObjectList.push_back(obj);//還沒有與此物件相同圖層的物件，將此物件加到最尾端
}

void GameSystem::AddUserInterface(UInterface* ui) {
	gameUIList.push_back(ui);
}


void GameSystem::DeleteGameObject(GameObject * obj)
{
	for (unsigned int i = 0; i < gameObjectList.size();)
	{
		if (gameObjectList[i] == obj)
		{
			delete gameObjectList[i];
			gameObjectList.erase(gameObjectList.begin() + i);
			return;
		}
		else
		{
			i++;
		}
	}

	/*for (auto i = gameObjectList.begin(); i != gameObjectList.end(); i++)
	{
		if (*i == obj)
		{
			gameObjectList.erase(i);
			return;
		}
	}*/
}

void GameSystem::DeleteUInterface(UInterface* ui)
{
	for (unsigned int i = 0; i < gameUIList.size(); )
	{
		if (gameUIList[i] == ui)
		{
			delete gameUIList[i];
			gameUIList.erase(gameUIList.begin() + i);
			return;
		}
		else
		{
			i++;
		}
	}

	/*for (auto i = gameUIList.begin(); i != gameUIList.end(); i++)
	{
		if (*i == ui)
		{
			gameUIList.erase(i);
			return;
		}
	}*/
}

void GameSystem::DeleteAllUI()
{
	while (!gameUIList.empty())
	{
		DeleteUInterface(gameUIList[0]);
	}
}

void GameSystem::DeleteAllGameObject()
{
	while (!gameObjectList.empty())
	{
		DeleteGameObject(gameObjectList[0]);
	}
}

void GameSystem::DeleteAllGameObjectExceptPlayer()
{
	int index = 0;
	while (gameObjectList.size() != 1)
	{
		if (gameObjectList[index]->GetTag() == "Player")
		{
			index++;
		}
		DeleteGameObject(gameObjectList[index]);
	}
}

void GameSystem::CreateFloor(int x, int y, int width, int height)
{
	for (int currentY = y; currentY < y + height; currentY += FLOOR_HEIGHT)//從y座標開始，持續往下增加地板
	{
		for (int currentX = x; currentX < x + width; currentX += FLOOR_WIDTH)//從x座標開始，持續往右增加地板
		{
			AddGameObject(new Floor("Floor", currentX, currentY, FLOOR_WIDTH, FLOOR_HEIGHT));
		}
	}
}


void GameSystem::AllObjectAct()
{
	for (auto& i : gameObjectList)
	{
		if(GameSystem::GetGameObjectWithType<Boss>())
			GameSystem::GetGameObjectWithType<Boss>()->GetPhase();
		i->Act();
	}
	//GetGameObjectWithType<Player>()->Act();
	//MonstersAct();

}

void GameSystem::SetAllObjectBitMapPosition()//設定所有物件圖片位置
{
	for (auto& i : gameObjectList)
	{
		i->SetBitMapPosition();
	}
}

void GameSystem::ShowAllObject()//顯示所有物件
{
	for (auto& i : gameObjectList)
	{
		string k = i->GetTag();
		bool i1 = i->GetX() <= Map::GetSX() + SIZE_X;
		bool i2 = i->GetX() + i->GetWidth() >= Map::GetSX();
		bool i3 = i->GetY() <= Map::GetSY() + SIZE_Y;
		int iy = i->GetY();
		bool i4 = i->GetY() + i->GetHeight() >= Map::GetSY();
		if (i->GetX() <= Map::GetSX() + SIZE_X
			&& i->GetX() + i->GetWidth() >= Map::GetSX()
			&& i->GetY() <= Map::GetSY() + SIZE_Y
 			&& i->GetY() + i->GetHeight() >= Map::GetSY())//只顯示在畫面中的物件
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

void GameSystem::ShowText(string text, int left, int top, int right, int bottom, int alignHor, int alignVer, int fontSize, COLORREF textColor, int bkMode, COLORREF bkColor)
{
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f, *fp;
	f.CreatePointFont(fontSize * 10, "Times New Roman");	// 產生 font f; 160表示16 point的字
	fp = pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkMode(bkMode);
	pDC->SetBkColor(bkColor);
	pDC->SetTextColor(textColor);

	char str[1000];								// Demo 數字對字串的轉換
	sprintf(str, text.c_str());

	CRect rect = { left,top,right,bottom };//設定矩形左、上、右、下的座標	

	if (alignVer == ALIGN_TOP)//上
	{
		if (alignHor == ALIGN_LEFT)
		{
			pDC->DrawText(str, rect, DT_LEFT | DT_WORDBREAK);//靠左對齊，可換行
		}
		else if (alignHor == ALIGN_CENTER)
		{
			pDC->DrawText(str, rect, DT_CENTER | DT_WORDBREAK);//靠中對齊，可換行
		}
		else if (alignHor == ALIGN_RIGHT)
		{
			pDC->DrawText(str, rect, DT_RIGHT | DT_WORDBREAK);//靠右對齊，可換行
		}
	}

	else if (alignVer == ALIGN_CENTER)
	{
		//這裡在設定垂直置中
		CRect temp = rect;
		int height = pDC->DrawText(str, temp, DT_CENTER | DT_WORDBREAK | DT_CALCRECT);
		rect.top += (rect.Height() - height) / 2;
		//rect.DeflateRect(0, (rect.Height() - height) / 2);

		if (alignHor == ALIGN_LEFT)
		{
			pDC->DrawText(str, rect, DT_LEFT | DT_WORDBREAK);//靠左對齊，可換行
		}
		else if (alignHor == ALIGN_CENTER)
		{
			pDC->DrawText(str, rect, DT_CENTER | DT_WORDBREAK);
		}
		else if (alignHor == ALIGN_RIGHT)
		{
			pDC->DrawText(str, rect, DT_RIGHT | DT_WORDBREAK);//靠右對齊，可換行
		}
	}

	else if (alignVer == ALIGN_BOTTOM)
	{
		//這裡在設定垂直置下
		CRect temp = rect;
		int height = pDC->DrawText(str, temp, DT_WORDBREAK | DT_CALCRECT);
		rect.top += rect.Height() - height;
		//rect.DeflateRect(0, (rect.Height() - height));

		if (alignHor == ALIGN_LEFT)
		{
			pDC->DrawText(str, rect, DT_LEFT | DT_WORDBREAK);//靠左對齊，可換行
		}
		else if (alignHor == ALIGN_CENTER)
		{
			pDC->DrawText(str, rect, DT_CENTER | DT_WORDBREAK);
		}
		else if (alignHor == ALIGN_RIGHT)
		{
			pDC->DrawText(str, rect, DT_RIGHT | DT_WORDBREAK);//靠右對齊，可換行
		}
	}

	//pDC->DrawText(str, rect, DT_CENTER | DT_WORDBREAK);

	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}

void GameSystem::DrawRectangle(int x, int y, int width, int height, COLORREF color)
{
	CDC *pDC = CDDraw::GetBackCDC();
	CPen *pp, p(PS_NULL, 0, RGB(0, 0, 0));
	pp = pDC->SelectObject(&p);

	CBrush *pr, r(color);
	pr = pDC->SelectObject(&r);

	pDC->Rectangle(x, y, x + width, y + height);

	pDC->SelectObject(pp);
	pDC->SelectObject(pr);
	CDDraw::ReleaseBackCDC();
}

void GameSystem::Load()
{
	if (isLoaded == false)//還沒載入
	{
		CAudio::Instance()->Load(AUDIO::AUDIO_GAME_INIT, ".\\res\\game_init.mp3");
		CAudio::Instance()->Load(AUDIO::AUDIO_GAME_RUN, ".\\res\\game_run.mp3");
		CAudio::Instance()->Load(AUDIO::AUDIO_GAME_OVER, ".\\res\\game_over.mp3");

		isLoaded = true;
	}
}

void GameSystem::Init()
{
	isGameOver = false;//重置遊戲狀態
	isNextStage = false;
	nowStage = 1;
	Map::SetSX(0);
	Map::SetSY(0);
	DeleteAllGameObject();//刪除所有物件
	isGameOver = false;
	DeleteAllGameObject();
	DeleteAllUI();
}

void GameSystem::Exit()
{
	DeleteAllGameObject();
	DeleteAllUI();
	gameObjectList.clear();
	gameUIList.clear();
}

void GameSystem::PlayAudio(AUDIO id)
{
	CAudio::Instance()->Play(id, true);
}

void GameSystem::StopAudio(AUDIO id)
{
	CAudio::Instance()->Stop(id);
}

/*void GameSystem::MonstersAutoMove() {
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
}*/

void GameSystem::ChangeToNextStage()
{
	DeleteAllGameObjectExceptPlayer();
	CreatStage2Object();


	SetIsNextStage(false);
}

double GameSystem::Rand(double maxValue)
{
	std::random_device rd;
	std::default_random_engine gen = std::default_random_engine(rd());
	std::uniform_real_distribution<double> dis(0, maxValue);
	auto randFun = std::bind(dis, gen);

	return randFun();
}

double GameSystem::Rand(double minValue, double maxValue)
{
	std::random_device rd;
	std::default_random_engine gen = std::default_random_engine(rd());
	std::uniform_real_distribution<double> dis(minValue, maxValue);
	auto randFun = std::bind(dis, gen);

	return randFun();
}

void GameSystem::CreatStage1Object()
{
	
	Init();
	AddGameObject(new Player("Player", 80, 80, 50, 80));
	Player* player = GetGameObjectWithTag<Player>("Player");
	Map::SetSX(player->GetX() - SIZE_X / 2);
	Map::SetSY(player->GetY() - SIZE_Y / 2);


	AddGameObject(new Floor("Floor", 0, Map::WORLD_SIZE_Y - 355, Map::WORLD_SIZE_X, 355, IDB_GROUND));

	for (int i = 0; i < stage1FloorCount; i++)
	{
		//CreateFloor(stage1Floor[i][0], stage1Floor[i][1], stage1Floor[i][2], stage1Floor[i][3]);
		GameSystem::AddGameObject(new Floor("Floor", stage1Floor[i][0], stage1Floor[i][1], stage1Floor[i][2], stage1Floor[i][3]));
	}
	
	AddGameObject(new Treasure("Treasure", 400, 1388, 250, 187, 100,100, 0, 10));

	AddGameObject(new Door("Door", 530, 480, 12, 120));//門
	AddGameObject(new Door("Door", 1315, 260, 12, 120));//門
	AddGameObject(new Door("Door", 2330, 1445, 12, 120));//門
	AddGameObject(new Door("Door", 3420, 480, 12, 120));//門
	AddGameObject(new Goal("Goal", 3510, 1353, 143, 212));
	AddGameObject(new Portal("Portal", 100, 480, 80, 120, 100));
	AddGameObject(new Portal("Portal", GetGameObjectWithType<Goal>()->GetX() - 300, GetGameObjectWithType<Goal>()->GetY(), 80, 120, 0));
	
	AddGameObject(new Demon("Monster", 100, 100, 110, 158));

	AddUserInterface(new EquipedSlot("EquipedSlot", SIZE_X / 10 - 100, SIZE_Y * 9 / 10, 64, 60));
	AddUserInterface(new EquipedSlot("EquipedSlot", SIZE_X / 10 - 10, SIZE_Y * 9 / 10, 64, 60));
	AddUserInterface(new UIBlood("UIBlood", 0, SIZE_Y - 30, 400, 30));
	AddUserInterface(new UIMonsterBlood("UIMonster", 0, 0, 0, 0));
	
	Map::SetStaticObject();
}

void GameSystem::CreatStage2Object()
{
	AddGameObject(new Boss("Monster", SIZE_X - 200, Map::WORLD_SIZE_Y - 100 - 280, 180, 280));
	//AddGameObject((new Demon("Monster", SIZE_X / 2 + 100, SIZE_Y / 2 - 133, 131, 141)));
	//AddGameObject((new Demon("Monster", SIZE_X / 2 - 150, SIZE_Y / 2 - 133, 131, 141)));

	AddGameObject(new Floor("Floor", 0, Map::WORLD_SIZE_Y - 100, Map::WORLD_SIZE_X, 100, IDB_GROUND));//地圖最下方的地板

	AddGameObject(new Door("Door", 100, Map::WORLD_SIZE_Y - 220, 12, 120));//門
	AddGameObject(new Goal("Goal", 150, Map::WORLD_SIZE_Y - 312, 143, 212));
	//AddUserInterface(new UIBlood("UIBlood", 0, SIZE_Y - 30, 400, 30));

	Map::Init();
	Map::SetStaticObject();
}