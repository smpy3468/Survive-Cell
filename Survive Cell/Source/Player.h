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
	~Player();
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
	void SetIsPortaling(bool isPortaling, int destX, int destY); //設定是否在傳送 和 傳送位置
	void SetIsUnconquered(bool isUnconquered);//設定是否無敵


	bool GetIsJump();//是否在跳躍
	int GetPickCount(); //撿了幾次武器

	bool HasWeapon();//是否有武器
	void ChangeWeapon(int weaponNum);//切換武器
	PlayerEquipment* GetWeapon();
	PlayerEquipment* GetWeapon1();
	PlayerEquipment* GetWeapon2();
	int CurrentWeapon();//目前用的武器是哪一把

	//----------------動作相關---------------------//
	void Act();//按下按鍵行動
	void Fall();//下降
	void Jump();//跳躍
	void DownJump();//下跳
	void Interact();//互動
	void Move(int dx, int dy)override;//移動特定距離
	void MoveTo(int x, int y)override;//移動到特定座標
	void Attack()override;//攻擊
	void Portaling();//傳送


	//----------------動畫相關---------------------//
	void ShowBitMap()override;//顯示動畫

	//-------------顯示玩家資訊------------------//
	void ShowInformation();//顯示玩家資訊

	//-------------系統相關------------------//
	template <class T> void AddEquipment(T* equipment)//增加裝備
	{
		this->equipments.push_back(equipment);

		if (dynamic_cast<PlayerWeapon*>(equipment))//撿起的裝備是武器
		{	
			pickCount++;	//計算撿裝備的次數
			if (weaponCount < MAX_WEAPON_COUNT)//目前武器數量小於最大武器數量
			{
				if (!weapon1)//還沒有武器
				{
					this->weapon1 = equipments[equipments.size() - 1];
					this->weapon = weapon1;
				}
				else if (!weapon2)//還沒有第二把武器
				{
					this->weapon2 = equipments[equipments.size() - 1];
					this->weapon = weapon2;
				}

				hasWeapon = true;//有武器了
				weaponCount++;//持有武器數量+1	
			}
			else
			{
				RemoveWeapon();//移除武器

				if (!weapon1)//武器1已清除
				{
					this->weapon1 = equipments[equipments.size() - 1];
					this->weapon = weapon1;
				}
				else if (!weapon2)//武器2已清除
				{
					this->weapon2 = equipments[equipments.size() - 1];
					this->weapon = weapon2;
				}
			}
		}

		CalculateAbility(equipment);//計算能力值
	}

	void RemoveWeapon();//移除武器

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
	bool isGetHit;//是否被打
	bool isPortaling;//是否正在傳送途中

	//---------------跳躍相關---------------//
	int fallDisplacement;//下降位移量(移動到沒有地板的位置會用到)
	int originJumpDisplacement, jumpDisplacement;//跳躍位移量
	bool isGrounded;//是否在地上
	int jumpCount = 0;//跳躍段數計數
	const int MAX_JUMP_COUNT = 3;//最多能幾段跳


	//---------------蹲下相關---------------//
	void ChangeHeight(int height);//讓寬高變一樣
	bool CanStand();//目前空間高度，能不能站起來

	//---------------下跳相關---------------//
	//bool IsFloorOnGround();//地板跟最底層地板剛好貼合，代表不能下跳
	bool HasSpaceToDownJump();//下方有足夠的高度可以容納玩家

	void CalculateAbility(PlayerEquipment* equipment);//計算能力值

	void Dead()override;//死亡時呼叫

	//---------------翻滾相關---------------//
	void Roll();//翻滾
	int originRollDisplacement, rollDisplacement;//翻滾位移量
	int originWidth, originHeight;//翻滾時角色是倒下的，寬高會互換，用origin變數儲存原本的寬高
	void FlipWidthHeight();//對調寬高
	void AdjustY(int dy);//調整y座標


	//---------------傳送相關---------------//
	int destinationX, destinationY;
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
		ANI_SQUAT_RIGHT,
		ANI_PORTALING
	};

	vector<PlayerEquipment*> equipments;//裝備
	PlayerEquipment* weapon = NULL;//目前武器
	PlayerEquipment* weapon1 = NULL,*weapon2 = NULL;//身上的兩把武器

	const int MAX_WEAPON_COUNT = 2;//最大武器數量
	int weaponCount = 0;//武器數量
	bool hasWeapon = false;
	int pickCount = 0;		//算撿起的數量
};