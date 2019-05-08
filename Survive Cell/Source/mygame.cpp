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
#include "UIMonsterBlood.h"
#include "Door.h"
#include "Goal.h"

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
		GameSystem::Load();
		Map::Load();
	}

	void CGameStateInit::OnBeginState()
	{
		GameSystem::CreatStage1Object();

		//GameSystem::StopAudio(GameSystem::AUDIO::AUDIO_GAME_OVER);//停止遊戲中的音樂
		//GameSystem::PlayAudio(GameSystem::AUDIO::AUDIO_GAME_INIT);//播放遊戲結束的音樂
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
		Map::ShowStartMenu();
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
		countDown--;
		if (countDown <= 0)
		{
			GotoGameState(GAME_STATE_INIT);
		}
	}

	void CGameStateOver::OnBeginState()
	{
		countDown = 3 * 30;
		//GameSystem::StopAudio(GameSystem::AUDIO::AUDIO_GAME_OVER);//停止遊戲結束的音樂
		//GameSystem::PlayAudio(GameSystem::AUDIO::AUDIO_GAME_INIT);//播放遊戲開始的音樂

		GameSystem::StopAudio(GameSystem::AUDIO::AUDIO_GAME_RUN);//停止遊戲中的音樂
		GameSystem::PlayAudio(GameSystem::AUDIO::AUDIO_GAME_OVER);//播放遊戲結束的音樂
	}

	void CGameStateOver::OnInit()
	{

	}

	void CGameStateOver::OnShow()
	{
		string text;
		for (int i = 0; i < countDown; i += 3)
			text += "G";
		GameSystem::ShowText(text, 0, 0, SIZE_X, SIZE_Y, GameSystem::ALIGN_CENTER, GameSystem::ALIGN_CENTER, 16
			, RGB(255 * (originCountDown - countDown) / originCountDown, 255 * (originCountDown - countDown) / originCountDown, 255 * (originCountDown - countDown) / originCountDown));

		if(countDown <= 0)
			countDown = originCountDown;
	}


	CGameStateRun::CGameStateRun(CGame *g)
		: CGameState(g)
	{

	}

	CGameStateRun::~CGameStateRun()
	{
		GameSystem::Exit();//離開遊戲
	}

	void CGameStateRun::OnBeginState()
	{
		Player& player = *(GameSystem::GetGameObjectWithTag<Player>("Player"));
		player.AdjustPositionOnBegin();

		if (GameSystem::IsNextStage()) {
			ShowInitProgress(30);				//換關卡的Loading
			Sleep(300);							//Delay
			GameSystem::ChangeToNextStage();
			ShowInitProgress(50);
			Sleep(300);

			player.MoveTo(GameSystem::GetGameObjectWithTag<Goal>("Goal")->GetX()
				, GameSystem::GetGameObjectWithTag<Goal>("Goal")->GetY());//移動至傳送門的位置
		}
		GameSystem::StopAudio(GameSystem::AUDIO::AUDIO_GAME_OVER);//停止結束的音樂
		GameSystem::PlayAudio(GameSystem::AUDIO::AUDIO_GAME_RUN);//播放遊戲的音樂
		ShowInitProgress(100);
	}

	void CGameStateRun::OnMove()							// 移動遊戲元素
	{
		if (GameSystem::IsGameOver())//遊戲結束
			GotoGameState(GAME_STATE_OVER);//跳至遊戲結束狀態
		if (GameSystem::IsNextStage())
			GotoGameState(GAME_STATE_RUN);

		Player& player = *(GameSystem::GetGameObjectWithTag<Player>("Player"));//宣告一個玩家，避免每次都要打一長串GetGameObject...

		player.Act();
		/*GameSystem::MonstersAttackPlayer(); //攻擊Player
		GameSystem::MonstersAutoMove();//怪物來回移動*/
		GameSystem::MonstersAct();
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
		const char KEY_ATTACK = 0x58;//攻擊鍵X鍵
		const char KEY_INTERACT = 0x43;//互動鍵c鍵
		const char KEY_ROLL = 0x5a;//翻滾鍵Z鍵

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
			//player.SetIsJump(true);
		}
		if (nChar == KEY_DOWN)
		{
			player.SetIsSquat(true);
		}

		if (nChar == KEY_SPACE)
		{
			player.SetIsJump(true);
			//player.SetIsDownJump(true);
		}

		if (nChar == KEY_ATTACK)
		{
			player.SetIsAttack(true);
		}

		if (nChar == KEY_INTERACT)
		{
			player.Interact();
		}

		if (nChar == KEY_ROLL)
		{
			player.SetIsRoll(true);
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
			player.SetIsSquat(false);
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
		GameSystem::ShowAllUI();
		Player& player = *(GameSystem::GetGameObjectWithTag<Player>("Player"));

		player.ShowInformation();//顯示玩家資訊
	}
}