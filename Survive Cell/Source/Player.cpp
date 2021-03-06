#include "StdAfx.h"
#include "Player.h"
#include "Monster.h"
#include "Map.h"
#include "Item.h"
#include "PlayerTradationalSword.h"
#include "Floor.h"
#include "Door.h"
#include "Goal.h"
#include "Portal.h"

Player::Player()
{
	tag = "Player";
}

Player::~Player()
{
	for (unsigned int i = 0; i < equipments.size(); i++)
	{
		delete equipments[i];
	}
	equipments.clear();
}

Player::Player(string tag, int x, int y, int width, int height) :Character(tag, x, y, width, height)
{
	tag = "Player";

	maxHP = 1000;
	HP = maxHP;

	originWidth = width;
	originHeight = height;

	originMoveSpeed = 5;
	moveSpeed = originMoveSpeed;

	fallDisplacement = 0;

	originJumpDisplacement = 15;
	jumpDisplacement = originJumpDisplacement;

	originRollDisplacement = 15;
	rollDisplacement = originRollDisplacement;

	attackRange = 10;
	attackDamage = 10;
	attackSpeed = 5;
	defense = 0;
	destinationX = 0;
	destinationY = 0;

	pickCount = 0;

	isMoveLeft = false;
	isMoveRight = false;

	isJumpKeyDown = false;
	isJump = false;
	isFall = false;
	isGrounded = false;
	isRollKeyDown = false;
	isRoll = false;
	isSquatKeyDown = false;
	isSquat = false;
	isUnconquered = false;
	isDownJump = false;
	isPortaling = false;
	isAttack = false;
	isGetHit = false;

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

void Player::DecreaseHP(int dhp)
{
	//if (isUnconquered == false)
	{
		isGetHit = true;

		int finalDHp = dhp - defense;//最終的扣血量
		
		if (finalDHp < 0)
			finalDHp = 0;
		
		HP -= finalDHp;
	}
	if (HP <= 0)
	{
		HP = 0;
		isDead = true;

		Dead();
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

void Player::MoveTo(int x, int y)
{
	Character::MoveTo(x, y);
	Map::SetSX(x - SIZE_X / 2);
	Map::SetSY(y - SIZE_Y / 2);
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

void Player::SetIsDownJump(bool isDownJump)
{
	this->isDownJump = isDownJump;
}

void Player::SetIsAttack(bool isAttack)
{
	this->isAttack = isAttack;
}

void Player::SetIsRoll(bool isRoll)
{
	this->isRollKeyDown = isRoll;
}

void Player::SetIsSquat(bool isSquat)
{
	this->isSquatKeyDown = isSquat;
}

void Player::SetIsUnconquered(bool isUnconquered)
{
	this->isUnconquered = isUnconquered;
}

bool Player::GetIsJump()
{
	return isJump;
}

int Player::GetPickCount()
{
	return pickCount;
}

void Player::SetIsPortaling(bool isPortaling, int destX, int destY)
{
	this->isPortaling = isPortaling;
	this->destinationX = destX;
	this->destinationY = destY;
}

bool Player::HasWeapon()
{
	return hasWeapon;
}

void Player::ChangeWeapon(int weaponNum)
{
	switch (weaponNum)
	{
	case 1:
		if(weapon1 != NULL)//如果有武器1
			weapon = weapon1;
		break;
	case 2:
		if(weapon2 != NULL)//如果有武器2
			weapon = weapon2;
		break;
	}

	if(weapon != NULL)//有武器
		CalculateAbility(weapon);//重新計算能力值
}

PlayerEquipment * Player::GetWeapon()
{
	return weapon;
}

PlayerEquipment * Player::GetWeapon1()
{
	return weapon1;
}

PlayerEquipment * Player::GetWeapon2()
{
	return weapon2;
}

int Player::CurrentWeapon()
{
	if (weapon == weapon1)
		return 1;
	else if (weapon == weapon2)
		return 2;
	else
		return 0;
}



void Player::SetIsGrounded(bool isGrounded)
{
	this->isGrounded = isGrounded;
}

void Player::Act()//行動
{
	if (isRoll == true || isSquat)//翻滾中或蹲下中不能攻擊
		isAttack = false;


	if (isAttack == false)//沒在攻擊
	{
		if (isRollKeyDown)//按下翻滾
		{
			isRollKeyDown = false;

			if (isGrounded && isRoll == false)//在地上才能開始翻，而且目前還沒翻滾(翻轉寬高只需翻轉一次)
			{
				isUnconquered = true;//翻滾時無敵
				isRoll = true;
				FlipWidthHeight();//翻轉寬高
			}
		}
		else if (isRoll == false)
		{
			if (this->isSquatKeyDown && isGetHit == false)//蹲下
			{
				//isSquatKeyDown = false;
				if (isGrounded)
				{
					isSquat = true;//改變蹲下狀態

					//if(height == originHeight)//高度跟原本一樣
					ChangeHeight(originHeight / 2);//將高度變為一半
					SetMoveSpeed(originMoveSpeed / 2);//速度變為一半
				//else
					//ChangeHeight(originHeight);//將高度還原
				}
			}
			else
			{
				if (CanStand())
				{
					isSquat = false;
					ChangeHeight(originHeight);//將高度還原
					SetMoveSpeed(originMoveSpeed);//將速度還原
				}
			}

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
		}

		if (this->isJumpKeyDown)//如果按下跳躍
		{
			isJumpKeyDown = false;//跳躍鍵不能持續按住

			if (isRoll == false)//翻滾中不能跳躍
			{
				if (isGrounded)//如果在地上
				{
					if (isSquat)//蹲下且跳躍，進行下跳
					{
						SetIsDownJump(true);//下跳
						isSquat = false;//下跳時不再蹲下
						ChangeHeight(originHeight);//將高度還原
						SetMoveSpeed(originMoveSpeed);//將速度還原
					}
					else
					{
						isJump = true;//正在跳躍
					}
					isGrounded = false;//沒在地上
				}

				if (!isDownJump)//沒有下跳才能多段跳
				{
					if (jumpCount < MAX_JUMP_COUNT)//小於最大跳躍段數
					{
						jumpCount++;//計數目前是幾段跳
						jumpDisplacement = originJumpDisplacement;//重置跳躍位移量，呈現二段跳的效果

						//以下是:若在下降中按下二段跳
						isFall = false;//如果原本在下降，則不再下降
						fallDisplacement = 0;//下降位移量重置
						isJump = true;//重新往上跳跳躍
					}
				}
			}
		}
	}

	if (isRoll)
		Roll();

	if (isPortaling)
		Portaling();

	else if (isDownJump)
	{
		DownJump();
	}
	else
	{
		if (isJump)
			Jump();//跳躍
		else
			Fall();//下降
	}
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
		jumpCount = 0;//跳躍段數重置

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

void Player::DownJump()
{
	Move(0, fallDisplacement);//向下移動
	fallDisplacement++;

	if (IsInFloor() == false//不在地板中
		//|| y + height + 1 >= GameSystem::GetGameObjectWithTag<Floor>("Ground")->GetY()//已在最底層地板
		//|| IsFloorOnGround()//地板跟最底層地板剛好貼合，代表不能下跳
		|| !HasSpaceToDownJump())//下方沒有足夠的空間可以下跳
	{
		isDownJump = false;//沒有下跳
	}
}

bool Player::HasSpaceToDownJump()
{
	int returnValue = true;//回傳值

	for (int i = x; i < x + width; i++)
	{
		int cy = y + height + 1;//玩家腳底的位置

		while (Map::HasObject(i, cy))//此處有地板
		{
			cy++;//cy往下移動直到沒有地板

			if (cy >= Map::WORLD_SIZE_Y)//cy已超出地圖範圍
			{
				return false;//沒有空間可以下跳
			}
		}

		int h = 0;//確認高度是否足夠讓玩家進入

		while (!Map::HasObject(i, cy))//此處沒有地板
		{
			h++;//高度增加
			cy++;//cy往下移動
		}

		if (h < height)//沒有足夠的高度
		{
			return false;//不能下跳
		}
	}
	return true;
}

void Player::ChangeHeight(int height)
{
	AdjustY(this->height - height);
	this->height = height;
}

bool Player::CanStand()
{
	for (int i = x; i < x + width; i++)
	{
		int h = 0;//計算高度
		int cy = y + h;//從玩家腳底開始

		while (!Map::HasObject(i, cy) && h < height)//往上計算高度有多少
		{
			cy--;
			h++;
		}

		if (h < height)//高度不夠
			return false;
	}

	return true;//每個x座標上方的高度都夠
}

void Player::Interact()
{
	//若有多個能夠互動的物件重疊，則先對道具互動，再對門互動
	vector<Item*> itemList;//道具
	vector<Goal*> goalList;//終點的門
	vector<Portal*> portalList;//傳送門

	for (auto&i : GameSystem::GetAllGameObject())//將對應的物件加入對應的列表中
	{
		if (dynamic_cast<Item*>(i) != NULL)//道具
			itemList.push_back(dynamic_cast<Item*>(i));

		else if (dynamic_cast<Goal*>(i) != NULL)//終點
			goalList.push_back(dynamic_cast<Goal*>(i));

		else if (dynamic_cast<Portal*>(i) != NULL)//傳送門
			portalList.push_back(dynamic_cast<Portal*>(i));
	}

	for (auto& i : itemList)//對道具互動
	{
		if (i->GetX() + i->GetWidth() > this->x && i->GetX() < this->x + this->width
			&& i->GetY() + i->GetHeight() > this->y && i->GetY() < this->y + this->height) {
			static_cast<Item*>(i)->Picked();
			return;
		}
	}

	for (auto& i : goalList)//對終點互動
	{
		if (i->GetX() + i->GetWidth() > this->x && i->GetX() < this->x + this->width
			&& i->GetY() + i->GetHeight() > this->y && i->GetY() < this->y + this->height) {
			static_cast<Goal*>(i)->Picked();
			return;
		}
	}

	for (auto& i : portalList)//對傳送門互動
	{
		if (i->GetX() + i->GetWidth() > this->x && i->GetX() < this->x + this->width
			&& i->GetY() + i->GetHeight() > this->y && i->GetY() < this->y + this->height) {
			static_cast<Portal*>(i)->Used();
			return;
		}
	}
}

void Player::Attack()
{
	vector<Monster*>monsters = GameSystem::GetGameObjectsWithType<Monster>();
	//vector<Monster*> monsters = GameSystem::GetGameObjectsWithTag<Monster>("Monster");

	for (auto& i : monsters)//對怪物攻擊
	{
		if (i->GetX() + i->GetWidth() > this->x - attackRange && i->GetX() < this->x + this->width + attackRange
			&& i->GetY() + i->GetHeight() > this->y && i->GetY() < this->y + this->height)//怪物在攻擊範圍內
		{
			i->PlayerAttack(attackDamage);
			GameSystem::ShowText(to_string(GetAttackDamage()), i->GetX() - Map::GetSX() + 10, i->GetY() - Map::GetSY() - 30, i->GetX() + i->GetWidth() - Map::GetSX(), i->GetY() + i->GetHeight() - Map::GetSY(), GameSystem::ALIGN_CENTER, GameSystem::ALIGN_TOP, 20, RGB(255, 0, 0));
		}
	}

	isAttack = false;//攻擊結束
}

void Player::Portaling()		//傳送
{
	int dX = (destinationX - x) / 4;//四張動畫 每張動畫得位移量
	int dY = (destinationY - y) / 4;


	if (x != destinationX && dX > 0)
	{
		x += dX;
		Map::MoveScreenTopLeft(dX, 0);
	}
	else if (x != destinationX && dX < 0)
	{
		x += dX;
		Map::MoveScreenTopLeft(dX, 0);
	}

	if (y != destinationY && dY < 0)
	{
		y += dY;
		Map::MoveScreenTopLeft(0, dY);
	}
	else if (y != destinationY && dY > 0)
	{
		y += dY;
		Map::MoveScreenTopLeft(0, dY);
	}

	if (abs(x - destinationX) <= 30 && abs(y - destinationY) <= 30)
		isPortaling = false;
}

void Player::ShowBitMap()
{
	if (isGetHit)//被攻擊
	{
		if (faceLR == FACE_LEFT)
		{
			currentAni = ANI_GET_HIT_LEFT;
		}
		else
		{
			currentAni = ANI_GET_HIT_RIGHT;
		}

		ani[currentAni]->OnMove();

		if (ani[currentAni]->IsEnd())
			isGetHit = false;
	}
	else if (isAttack)
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
	else if (isRoll)//翻滾動畫
	{
		if (faceLR == FACE_LEFT)
		{
			currentAni = ANI::ANI_ROLL_LEFT;
		}
		else
		{
			currentAni = ANI::ANI_ROLL_RIGHT;
		}
	}
	else if (isSquat)
	{
		if (faceLR == FACE_LEFT)
		{
			currentAni = ANI::ANI_SQUAT_LEFT;
		}
		else
		{
			currentAni = ANI::ANI_SQUAT_RIGHT;
		}
	}

	else if (isJump || isFall || isDownJump)//跳躍動畫
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
	else if (isPortaling)
	{
		currentAni = ANI::ANI_PORTALING;
		ani[ANI::ANI_PORTALING]->OnMove();
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

	if (hasWeapon)//有武器就顯示武器
	{
		ShowWeapon();
	}
}

void Player::RemoveWeapon()
{
	for (unsigned int i = 0; i < equipments.size(); i++)
	{
		if (equipments[i] == weapon)
		{
			if (weapon == weapon1)
			{
				weapon1 = NULL;//清除武器
			}
			else if (weapon == weapon2)
			{
				weapon2 = NULL;//清除武器
			}

			delete equipments[i];
			equipments.erase(equipments.begin() + i);
			break;
		}
	}
}

void Player::CalculateAbility(PlayerEquipment* equipment)
{
	//攻擊力與防禦累加上去
	this->attackDamage = equipment->GetAttackDamage();
	this->defense = equipment->GetDefense();
	//攻擊距離使用武器的攻擊距離
	this->attackRange = equipment->GetAttackRange();
	
}

void Player::Dead()
{
	GameSystem::SetGameOver(GameSystem::OVER_LOSE);//遊戲結束
	//GameSystem::DeleteGameObject(this);
}

void Player::Roll()
{
	if (faceLR == FACE_LEFT)
	{
		Move(-rollDisplacement, 0);
	}
	else
	{
		Move(rollDisplacement, 0);
	}

	for (auto& i : GameSystem::GetGameObjectsWithTag<Door>("Door"))//翻滾時踢門
	{
		if (i->GetX() < this->x + this->width && i->GetX() + i->GetWidth() > this->x
			&& i->GetY() < this->y + this->height && i->GetY() + i->GetHeight() > this->y && !i->GetRuin())//門在玩家範圍內 
		{
			i->Kicked();//踢門
			break;
		}


	}

	if (rollDisplacement-- <= 0)
	{
		isUnconquered = false;//無敵結束
		isRoll = false;//翻滾結束
		rollDisplacement = originRollDisplacement;

		FlipWidthHeight();//還原寬高

		if (CanStand() == false)//翻滾完之後的位置無法站起
		{
			isSquat = true;//變為蹲下狀態
			ChangeHeight(originHeight / 2);//將高度變為一半
			SetMoveSpeed(originMoveSpeed / 2);//速度變為一半
		}
	}
}

void Player::FlipWidthHeight()
{
	int temp = width;
	width = height;
	height = temp;

	AdjustY(width - height);
}

void Player::AdjustY(int dy)
{
	y += dy;
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

	//---------------左翻滾
	char* aniRollLeft = ".\\res\\player_roll_left.bmp";
	AddAniBitMap(aniRollLeft, ANI::ANI_ROLL_LEFT);

	//---------------右翻滾
	char* aniRollRight = ".\\res\\player_roll_right.bmp";
	AddAniBitMap(aniRollRight, ANI::ANI_ROLL_RIGHT);

	//左蹲下
	char* aniSquatLeft = ".\\res\\player_squat_left.bmp";
	AddAniBitMap(aniSquatLeft, ANI::ANI_SQUAT_LEFT);

	//右蹲下
	char* aniSquatRight = ".\\res\\player_squat_right.bmp";
	AddAniBitMap(aniSquatRight, ANI::ANI_SQUAT_RIGHT);

	//傳送
	char* aniPortaling[4] = { ".\\res\\portaling0.bmp",  ".\\res\\portaling1.bmp" , ".\\res\\portaling2.bmp" ,".\\res\\portaling0.bmp" };
	AddAniBitMaps(aniPortaling, ANI::ANI_PORTALING, 4, 2);
}
