#include "StdAfx.h"
#include "Portal.h"

Portal::Portal() {};

Portal::Portal(string tag, int x, int y, int width, int height, int number) :GameObject(tag, x, y, width, height)
{	
	ani = new CAnimation();
	LoadAni();
	player = GameSystem::GetGameObjectWithTag<Player>("Player");
	layer = GameSystem::LAYER::LAYER_FLOOR;
	connectedNumber = number;
}

Portal::~Portal() 
{
	delete ani;
}

int Portal::GetConnectedNumber()
{
	return this->connectedNumber;
}

void Portal::Used() 
{	
	Portal* anotherPortal = Connected();
	player->SetIsPortaling(true, Connected()->GetX(), Connected()->GetY());	//讓玩家進入傳送模式
}
void Portal::SetBitMapPosition()
{
	ani->SetTopLeft(x - Map::GetSX(), y - Map::GetSY());
}
void Portal::ShowBitMap()
{
	ani->OnShow();
}

void Portal::LoadAni()
{
	char* picture0 = ".\\res\\portal.bmp";
	ani->AddBitmap(picture0,RGB(255,255,255));
};

Portal* Portal::Connected()
{
	vector<Portal*> portals = GameSystem::GetGameObjectsWithTag<Portal>("Portal");
	for (auto& i : portals)
	{
		if (i->GetConnectedNumber() + this->connectedNumber == 100 && i)
		{
			return i;
		}
	}
	return this;
}