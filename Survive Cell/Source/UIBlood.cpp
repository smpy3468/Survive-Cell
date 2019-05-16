#include"StdAfx.h"
#include"UIBlood.h"

UIBlood::UIBlood(string tag, int x, int y, int width, int height) :UInterface(tag, x, y, width, height)
{
	this->x = 110;
	this->y = 10;

	this->width = maxWidth * player->GetHP() / player->GetMaxHP();

	this->maxWidth = 100;//程糴
	this->width = maxWidth;//程秨﹍糴砞程糴

	targetWidth = this->width;//程秨﹍糴砞程糴
}

UIBlood::~UIBlood()
{
}

void UIBlood::ShowBitMap()
{
	RefreshTargetWidth();
	OnShow();
}

void UIBlood::RefreshTargetWidth()
{
	this->targetWidth = maxWidth * player->GetHP() / player->GetMaxHP();
	//this->targetWidth = player->GetHP() * 2;
}


void UIBlood::OnShow() {
	GameSystem::DrawRectangle(0, 0, 300, 100, RGB(210, 210, 210));

	if (targetWidth < width && width <= maxWidth)
	{
		width -= 1;
	}
	else if (targetWidth > width && width <= maxWidth)
	{
		width += 1;
	}

	GameSystem::DrawRectangle(x, y, maxWidth, height, RGB(0, 0, 0));//礶﹀兵┏场
	GameSystem::DrawRectangle(x, y, width, height, RGB(255, 0, 0));//礶﹀兵

	//陪ボUIゅ
	string text = "HP:" + to_string(player->GetHP()) + "\nю阑:" + to_string(player->GetAttackDamage())
		+ "\nň縨:" + to_string(player->GetDefense());
	GameSystem::ShowText(text, x + maxWidth + 10, 10, SIZE_X, SIZE_Y, GameSystem::ALIGN_LEFT, GameSystem::ALIGN_TOP, 8);

	//陪ボUI瓜
	CMovingBitmap uiPlayer;
	uiPlayer.LoadBitmap(".\\res\\UIPlayer.bmp", RGB(255, 255, 255));
	uiPlayer.SetTopLeft(0, 0);
	uiPlayer.ShowBitmap();
}