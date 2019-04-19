/*
 * mygame.cpp: ���ɮ��x�C��������class��implementation
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include "Map.h"
#include "GameSystem.h"
#include "GameObject.h"
#include "Character.h"
#include "Player.h"
#include "Monster.h"
#include "Floor.h"
#include "Item.h"
#include "Fire.h"
#include "Demon.h"
#include "EquipedSlot.h"
#include "UIBlood.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C���}�Y�e������
	/////////////////////////////////////////////////////////////////////////////

	CGameStateInit::CGameStateInit(CGame *g)
		: CGameState(g)
	{
	}

	void CGameStateInit::OnInit()
	{
		GameSystem::Load();
		Map::Load();
	}

	void CGameStateInit::OnBeginState()
	{
		GameSystem::Init();

		GameSystem::AddGameObject((new Player("Player", SIZE_X / 2, SIZE_Y / 2 - 100, 50, 80)));
		GameSystem::AddGameObject((new Demon("Monster", SIZE_X / 2 + 100, SIZE_Y / 2 - 133, 149, 133)));
		GameSystem::AddGameObject((new Demon("Monster", SIZE_X / 2 - 150, SIZE_Y / 2 - 133, 149, 133)));

		GameSystem::AddGameObject(new Floor("Ground", 0, Map::WORLD_SIZE_Y - 100, Map::WORLD_SIZE_X, 100, IDB_GROUND));//�a�ϳ̤U�誺�a�O
		GameSystem::AddGameObject(new Floor("Floor", 0, Map::WORLD_SIZE_Y - 100, Map::WORLD_SIZE_X, 100, IDB_GROUND));//�a�ϳ̤U�誺�a�O

		GameSystem::CreateFloor(SIZE_X / 2, Map::WORLD_SIZE_Y / 2 + 400, 1000, 80);
		GameSystem::CreateFloor(SIZE_X / 2 + 1000, Map::WORLD_SIZE_Y / 2 + 500, 300, 80);
		GameSystem::CreateFloor(SIZE_X / 2 + 1000 + 300, Map::WORLD_SIZE_Y / 2 + 400, 1000, 80);
		GameSystem::CreateFloor(SIZE_X / 2 - 400, Map::WORLD_SIZE_Y - 150, 300, 80);

		GameSystem::CreateFloor(SIZE_X / 2 + 900, Map::WORLD_SIZE_Y / 2, 300, 80);
		GameSystem::CreateFloor(SIZE_X / 2 + 600, Map::WORLD_SIZE_Y / 2 + 100, 300, 80);
		GameSystem::CreateFloor(SIZE_X / 2 + 300, Map::WORLD_SIZE_Y /2 + 200, 300, 80);
		/*for (int i = 0; i < 3; i++)
		{
			//GameSystem::AddGameObject(new Floor("Floor", SIZE_X / 2 + 150 * i, SIZE_Y / 2 - 80 * i, 80, 50));
			
		}*/
		

		GameSystem::AddUserInterface(new EquipedSlot("EquipedSlot", SIZE_X / 2 - 230, SIZE_Y / 2 + 175, 64, 60));
		GameSystem::AddUserInterface(new EquipedSlot("EquipedSlot", SIZE_X / 2 - 310, SIZE_Y / 2 + 175, 64, 60));
		GameSystem::AddUserInterface(new UIBlood("UIBlood", 0, 0, 400, 30));
		Map::SetStaticObject();


		//GameSystem::StopAudio(GameSystem::AUDIO::AUDIO_GAME_OVER);//����C����������
		//GameSystem::PlayAudio(GameSystem::AUDIO::AUDIO_GAME_INIT);//����C������������
	}

	void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		GotoGameState(GAME_STATE_RUN);
	}

	void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
	{

	}

	void CGameStateInit::OnShow()
	{
		// �� Back Plain �� CDC
		Map::ShowStartMenu();
	}

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	CGameStateOver::CGameStateOver(CGame *g)
		: CGameState(g)
	{
	}

	void CGameStateOver::OnMove()
	{
		countDown--;
		if (countDown <= 0)
		{
			GotoGameState(GAME_STATE_INIT);
		}
	}

	void CGameStateOver::OnBeginState()
	{
		countDown = 3 * 30;
		//GameSystem::StopAudio(GameSystem::AUDIO::AUDIO_GAME_OVER);//����C������������
		//GameSystem::PlayAudio(GameSystem::AUDIO::AUDIO_GAME_INIT);//����C���}�l������

		GameSystem::StopAudio(GameSystem::AUDIO::AUDIO_GAME_RUN);//����C����������
		GameSystem::PlayAudio(GameSystem::AUDIO::AUDIO_GAME_OVER);//����C������������
	}

	void CGameStateOver::OnInit()
	{

	}

	void CGameStateOver::OnShow()
	{
		CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// ���� font f; 160���16 point���r
		fp = pDC->SelectObject(&f);					// ��� font f
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 255));

		char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
		sprintf(str, "�A�w�g���F ! \n�e�������Ŷ�");

		CRect rect = { 0,0,SIZE_X,SIZE_Y };//�]�w�x�Υ��B�W�B�k�B�U���y��

		//�o�̦b�]�w�����m��
		CRect temp = rect;
		int height = pDC->DrawText(str, temp, DT_CENTER | DT_WORDBREAK | DT_CALCRECT);
		rect.DeflateRect(0, (rect.Height() - height) / 2);

		pDC->DrawText(str, rect, DT_CENTER | DT_WORDBREAK);//�����m��

		pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
		CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
	}


	CGameStateRun::CGameStateRun(CGame *g)
		: CGameState(g)
	{

	}

	CGameStateRun::~CGameStateRun()
	{

	}

	void CGameStateRun::OnBeginState()
	{
		Player& player = *(GameSystem::GetGameObjectWithTag<Player>("Player"));
		player.AdjustPositionOnBegin();

		GameSystem::StopAudio(GameSystem::AUDIO::AUDIO_GAME_OVER);//�����������
		GameSystem::PlayAudio(GameSystem::AUDIO::AUDIO_GAME_RUN);//����C��������
	}

	void CGameStateRun::OnMove()							// ���ʹC������
	{
		if (GameSystem::IsGameOver())//�C������
			GotoGameState(GAME_STATE_OVER);//���ܹC���������A

		Player& player = *(GameSystem::GetGameObjectWithTag<Player>("Player"));//�ŧi�@�Ӫ��a�A�קK�C�����n���@����GetGameObject...
		player.Move();
		GameSystem::MonstersAttackPlayer(); //����Player
		GameSystem::MonstersAutoMove();//�Ǫ��Ӧ^����
		GameSystem::SetAllObjectBitMapPosition();//�]�w�Ҧ�����Ϥ���m
	}

	void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
	{

	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25; // keyboard���b�Y
		const char KEY_UP = 0x26; // keyboard�W�b�Y
		const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
		const char KEY_DOWN = 0x28; // keyboard�U�b�Y
		const char KEY_SPACE = 0x20;//�ť���
		const char KEY_INTERACT = 0x5a;//������Z��

		Player& player = *(GameSystem::GetGameObjectWithTag<Player>("Player"));//�ŧi�@�Ӫ��a�A�קK�C�����n���@����GetGameObject...

		if (nChar == KEY_LEFT)
		{
			player.SetIsMoveLeft(true);
		}
		if (nChar == KEY_RIGHT)
		{
			player.SetIsMoveRight(true);
		}
		if (nChar == KEY_UP)
		{
			player.SetIsJump(true);
		}
		if (nChar == KEY_DOWN)
		{
			player.SetIsDownJump(true);
			//player.SetIsMoveDown(true);
		}
		if (nChar == KEY_SPACE)
		{
			player.SetIsAttack(true);
		}

		if (nChar == KEY_INTERACT)
		{
			player.Interact();
		}
	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25; // keyboard���b�Y
		const char KEY_UP = 0x26; // keyboard�W�b�Y
		const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
		const char KEY_DOWN = 0x28; // keyboard�U�b�Y

		Player& player = *(GameSystem::GetGameObjectWithTag<Player>("Player"));//�ŧi�@�Ӫ��a�A�קK�C�����n���@����GetGameObject...

		if (nChar == KEY_LEFT)
		{
			player.SetIsMoveLeft(false);
		}
		if (nChar == KEY_RIGHT)
		{
			player.SetIsMoveRight(false);
		}
		if (nChar == KEY_UP)
		{
			player.SetIsJump(false);
		}
		if (nChar == KEY_DOWN)
		{
			//player.SetIsMoveDown(false);
		}
	}

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
	{

	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
	{

	}

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
	{

	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
	{

	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
	{

	}

	void CGameStateRun::OnShow()
	{
		Map::ShowBackgroundPic();
		GameSystem::ShowAllObject();
		GameSystem::ShowAllUI();
		Player& player = *(GameSystem::GetGameObjectWithTag<Player>("Player"));

		player.ShowInformation();//��ܪ��a��T
	}
}