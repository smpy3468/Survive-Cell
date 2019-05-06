#include "StdAfx.h"
#include "UIMonsterBlood.h"

UIMonsterBlood::UIMonsterBlood(string tag, int x, int y, int width, int height) :UInterface(tag, x, y, width, height) 
{
}

UIMonsterBlood::~UIMonsterBlood()
{

}


void UIMonsterBlood::OnShow(int x, int y, int hp)
{	
	int bloodHeight = 5;
	int bloodWidth = hp * 2;
	CDC *pDC = CDDraw::GetBackCDC();
	CPen *pp, p(PS_NULL, 0, RGB(0, 0, 0));
	pp = pDC->SelectObject(&p);

	CBrush *pg, g(RGB(255, 0, 0));
	pg = pDC->SelectObject(&g);

	pDC->Rectangle(x +10-Map::GetSX(), y-Map::GetSY()-10, x + bloodWidth - Map::GetSX(), y + bloodHeight - Map::GetSY());
	


	/*ÄÀ©ñpen*/
	pDC->SelectObject(pp);
	pDC->SelectObject(pg);
	CDDraw::ReleaseBackCDC();					// ©ñ±¼ Back Plain ªº CDC
}