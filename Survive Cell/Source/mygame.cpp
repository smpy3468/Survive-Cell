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
#include "Boss.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	/////////////////////////////////////////////////////////////////////////////

	CGameStateInit::CGameStateInit(CGame *g)
		: CGameState(g)
	{

	}

	CGameStateInit::~CGameStateInit()
	{
		Dead();
	}

	void CGameStateInit::OnInit()
	{
		//不要在這用
	}

	void CGameStateInit::OnBeginState()
	{
		Load();//載入

		GameSystem::CreatStage1Object();
		GameSystem::StopAudio(GameSystem::AUDIO_GAME_OVER_WIN);//停止遊戲結束的音樂
		GameSystem::StopAudio(GameSystem::AUDIO_GAME_OVER_LOSE);//停止遊戲結束的音樂
		GameSystem::PlayAudio(GameSystem::AUDIO_GAME_INIT);//播放遊戲結束的音樂
	}

	void CGameStateInit::Load()
	{
		if (isLoaded == false)
		{
			//OnInit
			GameSystem::Load();
			Map::Load();
			//

			buttonList.push_back(new Button("ButtonStart", SIZE_X * 3 / 4, SIZE_Y / 2 - 50, 100, 50, ButtonOnClickEvent::ON_CLICK_START));
			buttonList.push_back(new Button("ButtonOption", SIZE_X * 3 / 4, SIZE_Y / 2 + 50, 100, 50, ButtonOnClickEvent::ON_CLICK_OPTION));
			buttonList.push_back(new Button("ButtonExit", SIZE_X * 3 / 4, SIZE_Y / 2 + 150, 200, 50, ButtonOnClickEvent::ON_CLICK_EXIT));

			isLoaded = true;
		}
	}

	void CGameStateInit::Dead()
	{
		for (unsigned int i = 0; i < buttonList.size();)
		{
			delete buttonList[i];
			i++;
		}
	}

	void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		//GotoGameState(GAME_STATE_RUN);
	}

	void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
	{
		if (isShowOption)//開著選單時，按下滑鼠左鍵可關閉
		{
			isShowOption = false;
			return;
		}

		for (auto& i : buttonList)
		{
			if (point.x > i->GetX() && point.x < i->GetX() + i->GetWidth()
				&& point.y > i->GetY() && point.y < i->GetY() + i->GetHeight())//滑鼠在按鈕上
			{
				if (i->GetTag() == "ButtonOption")//按下選項
				{
					ButtonOnClickEvent::LoadOptionAni();
					isShowOption = true;
				}

				i->OnClick(this->game);//執行按鈕事件
			}
		}
	}

	void CGameStateInit::OnShow()
	{
		Map::ShowStartMenu();

		for (auto& i : buttonList)
		{
			i->SetBitMapPosition();
			i->ShowBitMap();
		}

		if (isShowOption)//顯示選項
		{
			ButtonOnClickEvent::OnClickOption(this->game);
		}
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

		GameSystem::StopAudio(GameSystem::AUDIO::AUDIO_GAME_RUN_1);//停止遊戲中的音樂
		GameSystem::StopAudio(GameSystem::AUDIO::AUDIO_GAME_RUN_2);//停止遊戲中的音樂

		if (GameSystem::GetOverMode() == GameSystem::OVER_LOSE)
			GameSystem::PlayAudio(GameSystem::AUDIO::AUDIO_GAME_OVER_LOSE);//播放失敗的音樂
		else
			GameSystem::PlayAudio(GameSystem::AUDIO::AUDIO_GAME_OVER_WIN);//播放勝利的音樂
	}

	void CGameStateOver::OnInit()
	{

	}

	void CGameStateOver::OnShow()
	{
		string text;

		if (GameSystem::GetOverMode() == GameSystem::OVER_LOSE)
		{
			for (int i = 0; i < countDown; i += 3)
			{
				text += "G";
			}

			GameSystem::ShowText(text, 0, 0, SIZE_X, SIZE_Y, GameSystem::ALIGN_CENTER, GameSystem::ALIGN_CENTER, 16
				, RGB(255 * (originCountDown - countDown) / originCountDown, 255 * (originCountDown - countDown) / originCountDown, 255 * (originCountDown - countDown) / originCountDown));
		}
		else if (GameSystem::GetOverMode() == GameSystem::OVER_WIN)
		{
			text += "太神啦";

			int r, g, b;
			r = static_cast<int>(GameSystem::Rand(210, 250));
			g = static_cast<int>(GameSystem::Rand(210, 250));
			b = static_cast<int>(GameSystem::Rand(210, 250));

			GameSystem::DrawRectangle(0, 0, SIZE_X, SIZE_Y, RGB(r, g, b));
			GameSystem::ShowText(text, 0, 0, SIZE_X, SIZE_Y, GameSystem::ALIGN_CENTER, GameSystem::ALIGN_CENTER, 16, RGB(255 - r, 255 - g, 255 - b));
		}

		if (countDown <= 0)
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
		//GameSystem::SetIsNextStage(true);
		if (GameSystem::IsNextStage()) {
			ShowInitProgress(30);				//換關卡的Loading
			Sleep(300);							//Delay
			GameSystem::ChangeToNextStage();
			ShowInitProgress(50);
			Sleep(300);

			player.MoveTo(GameSystem::GetGameObjectWithTag<Goal>("Goal")->GetX()
				, GameSystem::GetGameObjectWithTag<Goal>("Goal")->GetY());//移動至傳送門的位置

			GameSystem::StopAudio(GameSystem::AUDIO::AUDIO_GAME_RUN_1);//停止第一關的音樂
			GameSystem::PlayAudio(GameSystem::AUDIO::AUDIO_GAME_RUN_2);//播放第二關的音樂
		}
		else
		{
			GameSystem::StopAudio(GameSystem::AUDIO::AUDIO_GAME_RUN_2);//停止第二關的音樂
			GameSystem::PlayAudio(GameSystem::AUDIO::AUDIO_GAME_RUN_1);//播放第一關的音樂
		}
		GameSystem::StopAudio(GameSystem::AUDIO::AUDIO_GAME_INIT);//停止結束的音樂

		ShowInitProgress(100);
	}

	void CGameStateRun::OnMove()							// 移動遊戲元素
	{
		if (GameSystem::IsGameOver())//遊戲結束
			GotoGameState(GAME_STATE_OVER);//跳至遊戲結束狀態

		if (GameSystem::IsNextStage())
			GotoGameState(GAME_STATE_RUN);

		GameSystem::AllObjectAct();

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
		const char KEY_F = 0x46;//F鍵
		const char KEY_G = 0x47;//G鍵
		const char KEY_1 = 0x31;//1鍵
		const char KEY_2 = 0x32;//2鍵

		Player& player = *(GameSystem::GetGameObjectWithTag<Player>("Player"));//宣告一個玩家，避免每次都要打一長串GetGameObject...

		if (nChar == KEY_F)//測試用，按下時玩家加血
		{
			player.SetHP(player.GetHP() + 100);
		}

		if (nChar == KEY_G)//測試用，按下時BOSS扣血
		{
			Boss* boss = GameSystem::GetGameObjectWithType<Boss>();
			if (boss)//有boss才扣血
				boss->DecreaseHP(1000);
		}

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

		if (nChar == KEY_1)//換武器
		{
			player.ChangeWeapon(1);
		}

		if (nChar == KEY_2)//換武器
		{
			player.ChangeWeapon(2);
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
	}
}