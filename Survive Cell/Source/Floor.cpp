#include "StdAfx.h"
#include "Floor.h"
#include "GameSystem.h"

Floor::Floor()
{
	tag = "Floor";
}

Floor::~Floor()
{
}

Floor::Floor(string tag, int x, int y, int width, int height, int pictureID) :GameObject(tag, x, y, width, height, pictureID)
{
	layer = GameSystem::LAYER::LAYER_FLOOR;
}

Floor::Floor(string tag, int x, int y, int width, int height) : GameObject(tag, x, y, width, height)
{
	layer = GameSystem::LAYER::LAYER_FLOOR;
	LoadBitMap(".\\res\\floor.bmp");
}

void Floor::ShowBitMap()
{
	//objectPic.ShowBitmap();

	CDC *pDC = CDDraw::GetBackCDC();
	CPen *pp, p(PS_SOLID, 1, RGB(128, 128, 128));
	pp = pDC->SelectObject(&p);

	CBrush *pg, g(RGB(128, 128, 128));
	pg = pDC->SelectObject(&g);

	pDC->Rectangle(x - Map::GetSX(), y - Map::GetSY(), x + width - Map::GetSX(), y + height - Map::GetSY());

	pDC->SelectObject(pp);
	pDC->SelectObject(pg);
	CDDraw::ReleaseBackCDC();					// ©ñ±¼ Back Plain ªº CDC
}
