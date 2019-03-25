/*
 * mygame.cpp: 本檔案儲遊戲本身的class的implementation
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

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	/////////////////////////////////////////////////////////////////////////////

	CGameStateInit::CGameStateInit(CGame *g)
		: CGameState(g)
	{
	}

	void CGameStateInit::OnInit()
	{
		menu.LoadBitmap(".\\res\\menu.bmp");

		Map::LoadBackgroundPic();

		GameSystem::AddGameObject((new Player("Player", SIZE_X / 2, SIZE_Y / 2 - 100, 50, 80, IDB_PLAYER)));
		GameSystem::AddGameObject((new Monster("Monster", SIZE_X / 2 - 30, SIZE_Y / 2, 10, 10, IDB_0)));
		GameSystem::AddGameObject((new Monster("Monster", SIZE_X / 2 + 30, SIZE_Y / 2, 10, 10, IDB_1)));

		GameSystem::AddGameObject(new Floor("Floor", 0, Map::GetWorldSizeY() / 2 + 20, Map::GetWorldSizeX(), 100, IDB_GROUND));

		//GameSystem::AddGameObject(new Floor("Floor", SIZE_X / 2, SIZE_Y / 2 + 100, 30, 30, IDB_ERASER1));
		//GameSystem::AddGameObject(new Floor("Floor", SIZE_X / 2 - 30, SIZE_Y + 20, 80, 50, IDB_ERASER1));
		//GameSystem::AddGameObject(new Floor("Floor", SIZE_X / 2 - 120, SIZE_Y + 150, 80, 50, IDB_ERASER1));

		Map::SetStaticObject();
	}

	void CGameStateInit::OnBeginState()
	{

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
		// 放掉 Back Plain 的 CDC
		menu.ShowBitmap();
		
	}

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	CGameStateOver::CGameStateOver(CGame *g)
		: CGameState(g)
	{
	}

	void CGameStateOver::OnMove()
	{

	}

	void CGameStateOver::OnBeginState()
	{

	}

	void CGameStateOver::OnInit()
	{

	}

	void CGameStateOver::OnShow()
	{

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

	}

	void CGameStateRun::OnMove()							// 移動遊戲元素
	{
		Player& player = *(GameSystem::GetGameObjectWithTag<Player>("Player"));//宣告一個玩家，避免每次都要打一長串GetGameObject...
		player.Move();
		GameSystem::MonstersAttackPlayer(); //攻擊Player
		GameSystem::MonstersAutoMove();//怪物來回移動
		GameSystem::SetAllObjectBitMapPosition();//設定所有物件圖片位置
	}

	void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
	{

	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const char KEY_SPACE = 0x20;//空白鍵

		Player& player = *(GameSystem::GetGameObjectWithTag<Player>("Player"));//宣告一個玩家，避免每次都要打一長串GetGameObject...

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
			//player.SetIsMoveDown(true);
		}
		if (nChar == KEY_SPACE)
		{
			player.Attack();
		}
	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭

		Player& player = *(GameSystem::GetGameObjectWithTag<Player>("Player"));//宣告一個玩家，避免每次都要打一長串GetGameObject...

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

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{

	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{

	}

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{

	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{

	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{

	}

	void CGameStateRun::OnShow()
	{
		Map::ShowBackgroundPic();
		GameSystem::ShowAllObject();
	}
}