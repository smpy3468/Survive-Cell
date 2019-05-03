#include"StdAfx.h"
#include"UIBlood.h"

UIBlood::UIBlood(string tag, int x, int y, int width, int height) :UInterface(tag, x, y, width, height)
{
	this->width = player->GetMaxHP() * 2;
	this->targetWidth = this->width;
}

void UIBlood::ShowBitMap()
{
	RefreshTargetWidth();
	OnShow();
}

void UIBlood::RefreshTargetWidth()
{
	this->targetWidth = player->GetHP() * 2;
}


void UIBlood::OnShow() {

	CDC *pDC = CDDraw::GetBackCDC();
	CPen *pp, p(PS_NULL, 0, RGB(0, 0, 0));
	pp = pDC->SelectObject(&p);

	CBrush *pr, r(RGB(0, 255, 0));
	pr = pDC->SelectObject(&r);

	if (targetWidth < width) {
		width -= 1;
		pDC->Rectangle(x, y, x + width, y + height);
	}
	else {
		pDC->Rectangle(x, y, x + width, y + height);
	}


	/*ÄÀ©ñpen*/
	pDC->SelectObject(pp);
	pDC->SelectObject(pr);
	CDDraw::ReleaseBackCDC();					// ©ñ±¼ Back Plain ªº CDC

	GameSystem::ShowText(to_string(player->GetHP()), 0, 0, SIZE_X, SIZE_Y, "LEFT", "BOTTOM");
}