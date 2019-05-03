#pragma once

//Player
//玩家
//繼承Character
#include "StdAfx.h"
#include "Character.h"
#include "Item.h"
#include "ItemWeapon.h"
#include "PlayerEquipment.h"
#include "GameSystem.h"
class Player :public Character
{
public:
	Player();
	Player(string tag, int x, int y, int width, int height);

	void AdjustPositionOnBegin();//載入遊戲時微調玩家位置，避免玩家跟地板重疊

	void DecreaseHP(int dhp);

	//----------------按鍵相關---------------------//
	void SetIsMoveLeft(bool isMoveLeft);//設定是否向左移動
	void SetIsMoveRight(bool isMoveRight);//設定是否向右移動
	void SetIsGrounded(bool isGrounded);//設定是否在地上
	void SetIsJump(bool isJump);//設定是否按下跳躍
	void SetIsDownJump(bool isDownJump);//設定是否下跳
	void SetIsAttack(bool isAttack);//設定是否按下攻擊
	void SetIsRoll(bool isRoll);//設定是否按下翻滾
	void SetIsSquat(bool isSquat);//設定是否蹲下
	
	void SetIsUnconquered(bool isUnconquered);//設定是否無敵

	bool HasWeapon();//是否有武器

	//----------------動作相關---------------------//
	void Act();//按下按鍵行動
	void Fall();//下降
	void Jump();//跳躍
	void DownJump();//下跳
	void Interact();//互動
	void Move(int dx, int dy)override;//移動特定距離
	void Attack()override;//攻擊

	//----------------動畫相關---------------------//
	void ShowBitMap()override;//顯示動畫

	//-------------顯示玩家資訊------------------//
	void ShowInformation();//顯示玩家資訊

	//-------------系統相關------------------//
	template <class T> void AddEquipment(T* equipment)//增加裝備
	{
		this->equipments.push_back(equipment);

		if (!this->hasWeapon)//沒有武器
		{
			if (equipment->GetTag() == "PlayerWeapon")//是武器
			{
				this->weapon = equipments[equipments.size() - 1];
				hasWeapon = true;//有武器了
			}
		}

		CalculateAbility(equipment);//計算能力值
	}

private:
	bool isMoveLeft;//是否向左移動
	bool isMoveRight;//是否向右移動
	bool isJumpKeyDown;//是否按下跳躍
	bool isJump;//是否正在跳躍
	bool isDownJump;//是否正在下跳
	bool isFall;//是否正在下降
	bool isAttack;//是否正在攻擊
	bool isRoll;//是否正在翻滾
	bool isRollKeyDown;//是否按下翻滾
	bool isSquatKeyDown;//是否按下蹲下
	bool isSquat;//是否蹲下
	bool isUnconquered;//是否無敵

	int currentState = 0, nextState = 0;//現態,次態
	enum STATE//狀態機
	{
		STATE_IDLE=0,
		STATE_MOVE_LEFT,
		STATE_MOVE_RIGHT,
		STATE_JUMP,
		STATE_DOWN_JUMP,
		STATE_ATTACK,
		STATE_ROLL,
		STATE_SQUAT
	};

	//---------------跳躍相關---------------//
	int fallDisplacement;//下降位移量(移動到沒有地板的位置會用到)
	int originJumpDisplacement, jumpDisplacement;//跳躍位移量
	bool isGrounded;//是否在地上
	int jumpCount = 0;//跳躍段數計數
	const int MAX_JUMP_COUNT = 10;//最多能幾段跳

	//---------------蹲下相關---------------//
	void ChangeHeight(int height);//讓寬高變一樣

	//---------------下跳相關---------------//
	bool IsFloorOnGround();//地板跟最底層地板剛好貼合，代表不能下跳
	bool HasSpaceToDownJump();//下方有足夠的高度可以容納玩家

	void CalculateAbility(PlayerEquipment* equipment);//計算能力值

	void Dead()override;//死亡時呼叫

	//---------------翻滾相關---------------//
	void Roll();//翻滾
	int originRollDisplacement, rollDisplacement;//翻滾位移量
	int originWidth, originHeight;//翻滾時角色是倒下的，寬高會互換，用origin變數儲存原本的寬高
	void FlipWidthHeight();//對調寬高
	void AdjustY(int dy);//調整y座標

	//---------------動畫相關---------------//
	void ShowWeapon();//顯示武器

	bool faceLR;//面向左邊或面向右邊
	const bool FACE_LEFT = true;//面向左邊
	const bool FACE_RIGHT = false;//面向右邊

	void LoadAni()override;//載入動畫
	int currentAni = 0;//目前動畫
	enum ANI
	{
		ANI_IDLE = 0,
		ANI_LEFT,
		ANI_RIGHT,
		ANI_ATTACK_LEFT,
		ANI_ATTACK_RIGHT,
		ANI_JUMP_LEFT,
		ANI_JUMP_RIGHT,
		ANI_GET_HIT_LEFT,
		ANI_GET_HIT_RIGHT,
		ANI_ROLL_LEFT,
		ANI_ROLL_RIGHT,
		ANI_SQUAT_LEFT,
		ANI_SQUAT_RIGHT
	};

	vector<PlayerEquipment*> equipments;//裝備
	PlayerEquipment* weapon;//武器

	//彥澤加的
	//Item* equipment;
	bool hasWeapon = false;
};