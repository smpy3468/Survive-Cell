#include "StdAfx.h"
#include "GameSystem.h"
#include "Player.h"
#include "Monster.h"
#include "Map.h"
#include "Item.h"
#include "PlayerTradationalSword.h"

Player::Player()
{
	tag = "Player";
}

Player::Player(string tag, int x, int y, int width, int height) :Character(tag, x, y, width, height)
{
	tag = "Player";

	maxHP = 100;
	HP = maxHP;

	originMoveSpeed = 5;
	moveSpeed = originMoveSpeed;

	fallDisplacement = 0;

	originJumpDisplacement = 15;
	jumpDisplacement = originJumpDisplacement;

	attackRange = 3;
	attackDamage = 5;
	attackSpeed = 5;
	defense = 0;

	isMoveLeft = false;
	isMoveRight = false;

	isJumpKeyDown = false;
	isJump = false;
	isFall = false;
	isGrounded = false;

	isAttack = false;

	faceLR = FACE_RIGHT;

	currentAni = ANI::ANI_IDLE;

	layer = GameSystem::LAYER::LAYER_PLAYER;

	LoadAni();
}

void Player::AdjustPositionOnBegin()
{
	while (Map::HasObject(x, y + this->height + 1))
	{
		this->y--;
	}
}

void Player::Move(int dx, int dy)
{
	if ((dx > 0 && CanMoveRight(moveSpeed)) || (dx < 0 && CanMoveLeft(moveSpeed)))//x位移量往右而且右邊沒東西 或者 x位移量往左而且左邊沒東西
	{
		this->x += dx;//玩家x移動
	}

	this->y += dy;//玩家y移動

	if (dx > 0 && this->x + this->width / 2 >= Map::GetSX() + SIZE_X / 2)
		Map::MoveScreenTopLeft(dx, 0);//螢幕移動
	else if (dx < 0 && this->x + this->width / 2 < Map::GetSX() + SIZE_X / 2)
		Map::MoveScreenTopLeft(dx, 0);//螢幕移動

	if (dy > 0 && this->y + this->height / 2 >= Map::GetSY() + SIZE_Y * 3 / 4)
		Map::MoveScreenTopLeft(0, dy);//螢幕移動
	else if (dy < 0 && this->y + this->height / 2 < Map::GetSY() + SIZE_Y / 4)
		Map::MoveScreenTopLeft(0, dy);//螢幕移動
}

void Player::SetIsMoveLeft(bool isMoveLeft)
{
	this->isMoveLeft = isMoveLeft;
}

void Player::SetIsMoveRight(bool isMoveRight)
{
	this->isMoveRight = isMoveRight;
}

void Player::SetIsJump(bool isJump)
{
	this->isJumpKeyDown = isJump;
}

void Player::SetIsAttack(bool isAttack)
{
	this->isAttack = isAttack;
}

bool Player::HasWeapon()
{
	return hasWeapon;
}

void Player::SetIsGrounded(bool isGrounded)
{
	this->isGrounded = isGrounded;
}

void Player::Move()//移動方向
{
	if (!this->isAttack)//如果不是在攻擊狀態
	{
		if (this->isMoveLeft)
		{
			if (this->x > 0)
			{
				faceLR = FACE_LEFT;//面向左邊
				Move(-moveSpeed, 0);
			}
		}

		if (this->isMoveRight)
		{
			if (this->x + this->width < Map::WORLD_SIZE_X)
			{
				faceLR = FACE_RIGHT;//面向右邊
				Move(moveSpeed, 0);
			}
		}

		if (this->isJumpKeyDown)//如果按下跳躍
		{
			if (isGrounded)//如果在地上
			{
				isJump = true;//正在跳躍
				isGrounded = false;//沒在地上
			}
		}
	}

	if (isJump)
		Jump();//跳躍
	else
		Fall();//下降
}

void Player::Fall()
{
	if (CanMoveDown(fallDisplacement))//如果腳下沒東西
	{
		isFall = true;//正在下降
		isGrounded = false;//不在地上
		fallDisplacement++;
		Move(0, fallDisplacement);
	}
	else
	{
		while (CanMoveDown(1))//再繼續用下降位移量下降，將會卡進地板，所以一次向下位移1進行微調
			Move(0, 1);

		fallDisplacement = 0;
		isGrounded = true;//在地上
		isFall = false;//沒在下降

		if (currentAni == ANI::ANI_JUMP_LEFT)//將跳躍動畫還原
			currentAni = ANI::ANI_LEFT;
		else if (currentAni == ANI::ANI_JUMP_RIGHT)
			currentAni = ANI::ANI_RIGHT;
	}
}

void Player::Jump()
{
	if (isGrounded == false && isFall == false)//如果沒在地上且沒在下降
	{
		jumpDisplacement--;//位移量隨著時間改變

		if (jumpDisplacement >= 0)//往上升
		{
			if (CanMoveUp(jumpDisplacement))//可向上移動
				Move(0, -jumpDisplacement);
			else
				jumpDisplacement = 0;//開始往下掉
		}
		else//往下降
		{
			isJump = false;
			isFall = true;
			jumpDisplacement = originJumpDisplacement;//跳躍位移量還原
		}
	}
}

void Player::Interact()
{
	for (auto& i : GameSystem::GetAllGameObject())//對物件互動
	{
		if (i->GetTag() == "Item" || i->GetTag() == "Potion" || i->GetTag() == "ItemWeapon")//是物品
		{
			if (i->GetX() > this->x && i->GetX() < this->x + this->width
				&& i->GetY() > this->y && i->GetY() < this->y + this->height) {
				static_cast<Item*>(i)->Picked();
			}
		}
	}
}

void Player::Attack()
{
	vector<Monster*> monsters = GameSystem::GetGameObjectsWithTag<Monster>("Monster");

	for (auto& i : monsters)//對怪物攻擊
	{
		if (i->GetX() + i->GetWidth() > this->x - attackRange && i->GetX() < this->x + this->width + attackRange
			&& i->GetY() + i->GetHeight() > this->y && i->GetY() < this->y + this->height)//怪物在攻擊範圍內
		{
			i->DecreaseHP(attackDamage);
		}
	}

	isAttack = false;//攻擊結束
}

void Player::ShowBitMap()
{
	if (hasWeapon)
	{
		ShowWeapon();
	}

	if (isAttack)
	{
		if (faceLR == FACE_LEFT)
		{
			currentAni = ANI::ANI_ATTACK_LEFT;
			ani[ANI::ANI_ATTACK_LEFT]->OnMove();
		}
		else
		{
			currentAni = ANI::ANI_ATTACK_RIGHT;
			ani[ANI::ANI_ATTACK_RIGHT]->OnMove();
		}

		if (ani[currentAni]->IsEnd())
		{
			Attack();
		}
	}
	else if (isJump || isFall)//跳躍動畫
	{
		if (faceLR == FACE_LEFT)
		{
			currentAni = ANI::ANI_JUMP_LEFT;
		}
		else
		{
			currentAni = ANI::ANI_JUMP_RIGHT;
		}
	}
	else if (isMoveLeft)//左移動畫
	{
		currentAni = ANI::ANI_LEFT;
		ani[ANI::ANI_LEFT]->OnMove();

	}
	else if (isMoveRight)//右移動畫
	{
		currentAni = ANI::ANI_RIGHT;
		ani[ANI::ANI_RIGHT]->OnMove();
	}
	else
	{
		for (auto& i : ani)
		{
			i->Reset();//重置所有動畫
		}

		if (faceLR == FACE_LEFT)
			currentAni = ANI::ANI_LEFT;
		else
			currentAni = ANI::ANI_RIGHT;
	}

	ani[currentAni]->OnShow();
}

void Player::ShowInformation()
{
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f, *fp;
	f.CreatePointFont(80, "Times New Roman");	// 產生 font f; 160表示16 point的字
	fp = pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkMode(TRANSPARENT);				//透明背景
	pDC->SetTextColor(RGB(0, 0, 255));

	char str[800];								// Demo 數字對字串的轉換

	sprintf(str, "HP:%d\nAttack:%d\nAttack Speed:%d\nAttackRange:%d\nMoveSpeed:%d\nDefense:%d\n"
		, GetHP(), GetAttackDamage(), GetAttackSpeed(), GetAttackRange(), GetMoveSpeed(), GetDefense());

	CRect rect = { 0,30,SIZE_X,SIZE_Y };//設定矩形左、上、右、下的座標
	pDC->DrawText(str, rect, DT_LEFT | DT_WORDBREAK);//靠左對齊，可換行

	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}

/*void Player::AddEquipment(int equipmentID, ItemWeapon* equipment)
{
	switch (equipmentID)
	{
		case GameSystem::EQUIPMENT_ID::EQUIPMENT_TRADITIONAL_SWORD:
			this->equipments.push_back(new PlayerTraditionalSword(equipment));
		break;

		default:
		break;
	}

	if (!hasWeapon)//還沒有武器
	{
		if (equipment->GetTag() == "ItemWeapon")//是武器
		{
			this->weapon = new PlayerEquipment(equipment);//此處有問題
		}
	}

}*/

void Player::CalculateAbility(PlayerEquipment* equipment)
{
	//攻擊力與防禦累加上去
	this->attackDamage += equipment->GetAttackDamage();
	this->defense += equipment->GetDefense();

	//攻擊距離使用武器的攻擊距離
	this->attackRange = equipment->GetAttackRange();
}

void Player::Dead()
{
	GameSystem::SetGameOver();//遊戲結束
	//GameSystem::DeleteGameObject(this);
}

void Player::ShowWeapon()
{
	if (faceLR == FACE_LEFT)
	{
		weapon->SetXY(x, y, ANI_ATTACK_LEFT, ani[ANI::ANI_ATTACK_LEFT]->GetCurrentBitmapNumber());
		weapon->ShowBitMap();
	}
	else
	{
		weapon->SetXY(x, y, ANI_ATTACK_RIGHT, ani[ANI::ANI_ATTACK_RIGHT]->GetCurrentBitmapNumber());
		weapon->ShowBitMap();
	}
}

void Player::LoadAni()
{
	objectPic.LoadBitmap(".\\res\\player.bmp");

	//---------------靜止
	char* aniIdle[1] = { ".\\res\\player_idle.bmp" };
	AddAniBitMaps(aniIdle, ANI::ANI_IDLE, 1);

	//---------------左走
	char* aniLeft[4] = { ".\\res\\player_left_0.bmp", ".\\res\\player_left_1.bmp", ".\\res\\player_left_2.bmp", ".\\res\\player_left_3.bmp" };
	AddAniBitMaps(aniLeft, ANI::ANI_LEFT, 4);

	//---------------右走
	char* aniRight[4] = { ".\\res\\player_right_0.bmp", ".\\res\\player_right_1.bmp", ".\\res\\player_right_2.bmp", ".\\res\\player_right_3.bmp" };
	AddAniBitMaps(aniRight, ANI::ANI_RIGHT, 4);

	//---------------左跳
	char* aniJumpLeft = ".\\res\\player_jump_left.bmp";
	AddAniBitMap(aniJumpLeft, ANI::ANI_JUMP_LEFT);

	//---------------右跳
	char* aniJumpRight = ".\\res\\player_jump_right.bmp";
	AddAniBitMap(aniJumpRight, ANI::ANI_JUMP_RIGHT);

	//---------------左攻
	char* aniAttackLeft[3] = { ".\\res\\player_attack_left_0.bmp", ".\\res\\player_attack_left_1.bmp", ".\\res\\player_attack_left_2.bmp" };
	AddAniBitMaps(aniAttackLeft, ANI::ANI_ATTACK_LEFT, 3, 5);

	//---------------右攻
	char* aniAttackRight[3] = { ".\\res\\player_attack_right_0.bmp", ".\\res\\player_attack_right_1.bmp", ".\\res\\player_attack_right_2.bmp" };
	AddAniBitMaps(aniAttackRight, ANI::ANI_ATTACK_RIGHT, 3, 5);

	//---------------左被擊
	char* aniGetHitLeft = ".\\res\\player_get_hit_left.bmp";
	AddAniBitMap(aniGetHitLeft, ANI::ANI_GET_HIT_LEFT);

	//---------------右被擊
	char* aniGetHitRight = ".\\res\\player_get_hit_right.bmp";
	AddAniBitMap(aniGetHitRight, ANI::ANI_GET_HIT_RIGHT);
}
