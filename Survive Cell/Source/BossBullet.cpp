#include "StdAfx.h"
#include "BossBullet.h"

BossBullet::BossBullet()
{
}

BossBullet::BossBullet(string tag, int x, int y, int width, int height) :GameObject(tag, x, y, width, height)
{

}

BossBullet::~BossBullet()
{
}

void BossBullet::LoadAni()
{
	char* aniRotate = ".\\res\\boss_bullet";
}
