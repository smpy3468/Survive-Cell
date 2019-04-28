#include "StdAfx.h"
#include "Door.h"

Door::Door() :GameObject()
{
	tag = "Door";
}

Door::Door(string tag, int x, int y, int width, int height) : GameObject(tag, x, y, width, height)
{
	isRuin = false;
	ani = new CAnimation();
	layer = GameSystem::LAYER::LAYER_DOOR;
	LoadAni();
	stunRangeX = 100;
	stunRangeY = 100;
}

void Door::Kicked()
{
	Player* player = GameSystem::GetGameObjectWithTag<Player>("Player");
	isRuin = true;
	if (player->GetX()+50 > this->x)			//被破壞時決定往哪飛
		lr = LEFT;
	else
		lr = RIGHT;
}

bool Door::GetRuin() 
{
	return this->isRuin;

}

void Door::SetBitMapPosition()
{
	ani->SetTopLeft(x - Map::GetSX(), y - Map::GetSY());
}

void Door::Dead()
{
	//攻擊怪物
	
	DazeMonster();
	GameSystem::DeleteGameObject(this);//刪除物件
}

void Door::DazeMonster()
{
	vector <Monster*> allMonster = GameSystem::GetGameObjectsWithTag<Monster>("Monster");
	for (auto & i : allMonster)
	{	
		bool x = i->GetX() < this->x + this->width + stunRangeX && i->GetX() > this->x - stunRangeX;
		bool y = i->GetY() < this->y + stunRangeY && i->GetY() > this->y - stunRangeY/2;
		if (x && y)
		{
			i->PlayerAttack(0);
		}
	}
}
void Door::ShowBitMap()
{
	if (isRuin)
	{	
		if (lr == RIGHT)
			x += 1;
		else
			x -= 1;
		ani->OnMove();//播放破壞動畫
	}//被破壞的話
	
	if (ani->IsEnd())//播完破壞動畫後
		Dead();//刪除物件
	
	ani->OnShow();


}

void Door::LoadAni()
{
	char* pic0 = ".\\res\\door0.bmp";
	char* pic1 = ".\\res\\door1.bmp";
	char* pic2 = ".\\res\\door2.bmp";
	char* pic3 = ".\\res\\door3.bmp";
	ani->AddBitmap(pic0);
	ani->AddBitmap(pic1);
	ani->AddBitmap(pic2);
	ani->AddBitmap(pic3);
	ani->SetDelayCount(3);
}