#include "StdAfx.h"
#include "BossBullet.h"
#include "GameSystem.h"
#include "BossBullet2.h"
#include <math.h>

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
	originX = x;
	originY = y;
	targetX = player->GetX() + player->GetWidth() / 2;
	targetY = player->GetY() + player->GetHeight() / 2;
	distanceX = (targetX - (x + width / 2));
	distanceY = (targetY - (y + height / 2));
	int r = static_cast<int>(sqrt(pow(distanceX, 2) + pow(distanceY, 2)));//x,y�e�������T���Ϋ᪺����
	dx = static_cast<int>(static_cast<float>(distanceX) / r * moveSpeed);
	dy = static_cast<int>(static_cast<float>(distanceY) / r * moveSpeed);
}

BossBullet::~BossBullet()
{
	delete ani;
}

void BossBullet::Dead()
{
	player->DecreaseHP(attackDamage);
	GameObject::Dead();
}

void BossBullet::Act()
{
	x += dx;//����
	y += dy;//����

	if (x + width < 0 || x >= Map::WORLD_SIZE_X || y + height < 0 || y >= Map::WORLD_SIZE_Y)//���X���
		GameObject::Dead();//�����R��

	else if (x + width > player->GetX() && x < player->GetX() + player->GetWidth()
		&& y + height > player->GetY() && y < player->GetY() + player->GetHeight())//�������a
	{
		Dead();//���������a�A�R��
	}
	else if (boss->GetPhase() == 2)//Boss�ثe�b�ĤG���q�A�����g�\��
	{
		if (/*(x + width > targetX && x < targetX
			&& y + height > targetY && y < targetY
			&& sqrt(pow(x - originX, 2) + pow(y - originY, 2)) >= sqrt(pow(SIZE_X, 2) + pow(SIZE_Y, 2)) / 4)
			//��F���a��l��m�A�B���ʪ��Z���n�W�L�ù����䪺1/4
			||*/ 
			sqrt(pow(x - originX, 2) + pow(y - originY, 2)) >= sqrt(pow(SIZE_X, 2) + pow(SIZE_Y, 2)) / 2)
			//�Ϊ̲��ʪ��Z���W�L�ù����䪺1/2�A�N���g�l�u
		{
			//�s�y�K���l�u
			for (int i = 0; i < 8; i++)
			{
				GameSystem::AddGameObject(new BossBullet2("BossBullet", x, y, width, height, 30 + 45 * i));
			}

			GameObject::Dead();
		}
	}
	else if (boss->GetPhase() == 3)//Boss�ثe�b�ĤT���q�A���g�һݶZ���ܵu
	{
		if (sqrt(pow(x - originX, 2) + pow(y - originY, 2)) >= sqrt(pow(SIZE_X, 2) + pow(SIZE_Y, 2)) / 3)
			//�Ϊ̲��ʪ��Z���W�L�ù����䪺1/3�A�N���g�l�u
		{
			//�s�y�K���l�u
			for (int i = 0; i < 8; i++)
			{
				GameSystem::AddGameObject(new BossBullet2("BossBullet", x, y, width, height, 30 + 45 * i));
			}

			GameObject::Dead();
		}
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

		string sPic = "";
		
		if (boss->GetPhase() == 1)//�Ĥ@���q����
			sPic = ".\\res\\boss_bullet";
		else if (boss->GetPhase() == 2)//�ĤG���q����
			sPic = ".\\res\\boss_bullet2";
		else if (boss->GetPhase() == 3)//�ĤT���q����(��G���@��)
			sPic = ".\\res\\boss_bullet2";

		sPic += "_" + to_string(i) + ".bmp";

		//�নc-string
		char* cPic = new char[sPic.length() + 1];
		strcpy(cPic, sPic.c_str());

		ani->AddBitmap(cPic, RGB(255, 255, 255));//�[�J�Ϥ�
		delete cPic;//delete new
	}
}
