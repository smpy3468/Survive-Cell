#include "StdAfx.h"
#include "BossBullet.h"
#include "GameSystem.h"

BossBullet::BossBullet()
{
}

BossBullet::BossBullet(string tag, int x, int y, int width, int height) :GameObject(tag, x, y, width, height)
{
	layer = GameSystem::LAYER_MONSTER;
	ani = new CAnimation(5);
	LoadAni();

	moveSpeed = 10;
	attackDamage = 50;

	Player* player = GameSystem::GetGameObjectWithType<Player>();
	targetX = player->GetX() + player->GetWidth() / 2;
	targetY = player->GetY() + player->GetHeight() / 2;
	distanceX = (targetX - (x + width / 2));
	distanceY = (targetY - (y + height / 2));
}

BossBullet::~BossBullet()
{
	delete ani;
}

void BossBullet::Dead()
{
	player->DecreaseHP(attackDamage);
	GameSystem::DeleteGameObject(this);
}

void BossBullet::Act()
{
	int r = static_cast<int>(sqrt(pow(distanceX, 2) + pow(distanceY, 2)));//x,y�e�������T���Ϋ᪺����

	x += static_cast<int>(static_cast<float>(distanceX) / r * moveSpeed);
	y += static_cast<int>(static_cast<float>(distanceY) / r * moveSpeed);

	if (x + width < 0 || x >= Map::WORLD_SIZE_X || y + height < 0 || y >= Map::WORLD_SIZE_Y)//���X���
		GameObject::Dead();//�����R��

	else if (x + width > player->GetX() && x < player->GetX() + player->GetWidth()
		&& y + height > player->GetY() && y < player->GetY() + player->GetHeight())//�������a
	{
		Dead();//���������a�A�R��
	}
}

void BossBullet::SetBitMapPosition()
{
	ani->SetTopLeft(x - Map::GetSX(), y - Map::GetSY());
}

void BossBullet::ShowBitMap()
{
	ani->OnMove();
	ani->OnShow();
}

void BossBullet::LoadAni()
{
	for (int i = 0; i < 8; i++)
	{
		//�N�ɦW�걵���u+�s��+���ɦW
		string sPic = ".\\res\\boss_bullet";
		sPic += "_" + to_string(i) + ".bmp";

		//�নc-string
		char* cPic = new char[sPic.length() + 1];
		strcpy(cPic, sPic.c_str());

		ani->AddBitmap(cPic, RGB(255, 255, 255));//�[�J�Ϥ�
		delete cPic;//delete new
	}
}
