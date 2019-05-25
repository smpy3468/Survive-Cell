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
	// �o��class���C�����C���}�Y�e������
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
		//���n�b�o��
	}

	void CGameStateInit::OnBeginState()
	{
		Load();//���J

		GameSystem::CreatStage1Object();
		GameSystem::StopAudio(GameSystem::AUDIO_GAME_OVER);//����C����������
		GameSystem::PlayAudio(GameSystem::AUDIO_GAME_INIT);//����C������������
	}

	void CGameStateInit::Load()
	{
		if (isLoaded == false)
		{
			//OnInit
			GameSystem::Load();
			Map::Load();
			//

			buttonList.push_back(new Button("ButtonStart", SIZE_X * 3 / 4, SIZE_Y / 2, 100, 50, ButtonOnClickEvent::ON_CLICK_START));
			buttonList.push_back(new Button("ButtonOption", SIZE_X * 3 / 4, SIZE_Y / 2 + 100, 100, 50, ButtonOnClickEvent::ON_CLICK_OPTION));
			buttonList.push_back(new Button("ButtonExit", SIZE_X * 3 / 4, SIZE_Y / 2 + 200, 100, 50, ButtonOnClickEvent::ON_CLICK_EXIT));

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
		if (isShowOption)//�}�ۿ��ɡA���U�ƹ�����i����
		{
			isShowOption = false;
			return;
		}

		for (auto& i : buttonList)
		{
			if (point.x > i->GetX() && point.x < i->GetX() + i->GetWidth()
				&& point.y > i->GetY() && point.y < i->GetY() + i->GetHeight())//�ƹ��b���s�W
			{
				i->OnClick(this->game);//������s�ƥ�

				if (i->GetTag() == "ButtonOption")//���U�ﶵ
					isShowOption = true;
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

		if (isShowOption)//��ܿﶵ
		{
			ButtonOnClickEvent::OnClickOption(this->game);
		}
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
			text += "�ӯ���";

			int r, g, b;
			r = static_cast<int>(GameSystem::Rand(210,250));
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
		GameSystem::Exit();//���}�C��
	}

	void CGameStateRun::OnBeginState()
	{
		Player& player = *(GameSystem::GetGameObjectWithTag<Player>("Player"));
		player.AdjustPositionOnBegin();
		//GameSystem::SetIsNextStage(true);
		if (GameSystem::IsNextStage()) {
			ShowInitProgress(30);				//�����d��Loading
			Sleep(300);							//Delay
			GameSystem::ChangeToNextStage();
			ShowInitProgress(50);
			Sleep(300);

			player.MoveTo(GameSystem::GetGameObjectWithTag<Goal>("Goal")->GetX()
				, GameSystem::GetGameObjectWithTag<Goal>("Goal")->GetY());//���ʦܶǰe������m
		}
		GameSystem::StopAudio(GameSystem::AUDIO::AUDIO_GAME_INIT);//�����������
		GameSystem::PlayAudio(GameSystem::AUDIO::AUDIO_GAME_RUN);//����C��������
		ShowInitProgress(100);
	}

	void CGameStateRun::OnMove()							// ���ʹC������
	{
		if (GameSystem::IsGameOver())//�C������
			GotoGameState(GAME_STATE_OVER);//���ܹC���������A

		if (GameSystem::IsNextStage())
			GotoGameState(GAME_STATE_RUN);

		GameSystem::AllObjectAct();

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
		const char KEY_ATTACK = 0x58;//������X��
		const char KEY_INTERACT = 0x43;//������c��
		const char KEY_ROLL = 0x5a;//½�u��Z��
		const char KEY_F = 0x46;//F��
		const char KEY_G = 0x47;//G��
		const char KEY_1 = 0x31;//1��
		const char KEY_2 = 0x32;//2��

		Player& player = *(GameSystem::GetGameObjectWithTag<Player>("Player"));//�ŧi�@�Ӫ��a�A�קK�C�����n���@����GetGameObject...

		if (nChar == KEY_F)//���եΡA���U�ɪ��a�[��
		{
			player.DecreaseHP(-100);
		}
		
		if (nChar == KEY_G)//���եΡA���U��BOSS����
		{
			Boss* boss = GameSystem::GetGameObjectWithType<Boss>();
			if(boss)//��boss�~����
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

		if (nChar == KEY_1)//���Z��
		{
			player.ChangeWeapon(1);
		}

		if (nChar == KEY_2)//���Z��
		{
			player.ChangeWeapon(2);
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
			player.SetIsSquat(false);
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
	}
}