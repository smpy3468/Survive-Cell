#include "StdAfx.h"
#include "Boss.h"
#include "BossBullet.h"
#include <math.h>

Boss::Boss()
{

}

Boss::~Boss()
{

}

Boss::Boss(string tag, int x, int y, int width, int height) :Monster(tag, x, y, width, height)
{
	tag = "Monster";

	maxHP = 10000;
	HP = maxHP / 2;
	aniDelay = 10;
	moveSpeed = 3;

	attackRange = 100;
	attackDamage = 50;

	isShoot = false;

	LoadAni();

	for (int i = 0; i < STATE_LENGTH; i++)//建立各項機率表
	{
		for (int j = 0; j <= i; j++)
			cumStateProb[i] += originStateProb[j];
	}

	phase = 1;//第一階段
	currentState = STATE_IDLE;//預設動作
}

void Boss::Act()
{
	if (static_cast<float>(HP) / maxHP <= 0.5)//第二階段
	{
		phase = 2;
	}

	//currentState = STATE_FAR_SHOOT;
	switch (currentState)//根據狀態做不同動作
	{
	case STATE_IDLE://靜止

		//faceLR = static_cast<int>(GameSystem::Rand(2));

		//if (ani[currentAni]->IsEnd())//播完動畫後
	{
		currentState = RandomState();//隨機改變狀態

		if (currentState == STATE_JUMP)//下一個狀態是跳躍時，紀錄玩家跟BOSS的距離
		{
			playerDistanceX = player->GetX() - x;
			playerDistanceY = player->GetY() - y;
		}
	}

	if (player->GetX() - x < 0)//玩家在左邊
		faceLR = FACE_LEFT;//面向左邊
	else
		faceLR = FACE_RIGHT;//面相右邊

	break;
	case STATE_MOVE://移動
		if (faceLR == FACE_LEFT)
		{
			Move(-moveSpeed, 0);
		}
		else
		{
			Move(moveSpeed, 0);
		}

		if (ani[currentAni]->IsEnd())//移動動畫播完
		{
			currentState = STATE_IDLE;//就回到靜止狀態
		}

		break;
	case STATE_NEAR_SLASH://攻擊
		NearSlash();
		break;
	case STATE_FAR_SHOOT://射擊
		FarShoot();
		break;
	case STATE_JUMP:
		Jump();
		break;
	}

	Fall(fallDisplacement);
}

int Boss::GetPhase()
{
	return phase;
}

void Boss::Fall(int perDisplacement)
{
	if (CanMoveDown(fallDisplacement))//如果腳下沒東西
	{
		fallDisplacement++;
		Move(0, fallDisplacement);
	}
	else
	{
		while (CanMoveDown(1))//再繼續用下降位移量下降，將會卡進地板，所以一次向下位移1進行微調0
			Move(0, 1);
		fallDisplacement = 0;

	}
}

void Boss::NearSlash()
{
	if (ani[currentAni]->IsEnd())//攻擊判定只會出現一次，因此攻擊動畫播完才攻擊
	{
		int leftEdge = 0, rightEdge = 0;
		if (faceLR == FACE_LEFT)//設定向左邊界
		{
			leftEdge = this->x - attackRange;
			rightEdge = this->x + this->width / 2;
		}
		else//設定向右邊界
		{
			leftEdge = this->x + this->width / 2;
			rightEdge = this->x + this->width + attackRange;
		}

		if (player->GetX() + player->GetWidth() / 2 > leftEdge
			&& player->GetX() + player->GetWidth() / 2 < rightEdge
			&& player->GetY() + player->GetHeight() > this->y
			&& player->GetY() < this->y + this->height)//玩家在範圍內
		{
			player->DecreaseHP(attackDamage);//攻擊玩家
		}

		currentState = STATE_IDLE;//回到靜止狀態
	}
}

void Boss::FarShoot()
{
	if (ani[currentAni]->IsEnd())
	{
		isShoot = false;
		currentState = STATE_IDLE;//回到靜止狀態
	}
	else if (ani[currentAni]->GetCurrentBitmapNumber() == 3)//第三張圖片時發射子彈
	{
		if (isShoot == false)
		{
			isShoot = true;
			GameSystem::AddGameObject(new BossBullet("BossBullet", x, y, 50, 50));
		}
	}
}

void Boss::Jump()
{
	if (jumpDisplacement-- > 0)//跳躍位移量隨時間遞減
	{
		if (jumpMode == JUMP_BACK)//在近處
			JumpBack();//向後跳
		else if (jumpMode == JUMP_FRONT)//在遠方
			JumpFront();//向前跳
	}
	else
	{
		jumpDisplacement = originJumpDisplacement;//跳躍位移量還原

		if (player->GetX() + player->GetWidth() > this->x - attackRange
			&& player->GetX() < this->x + this->width + attackRange
			&& player->GetY() + player->GetHeight() > this->y + this->height / 2
			&& player->GetY() < this->y + this->height)//玩家在範圍內
		{
			if (player->GetIsJump() == false)//玩家沒有在跳躍
				player->DecreaseHP(attackDamage);//攻擊玩家
		}

		currentState = STATE_IDLE;//回到靜止狀態
	}

	ani[currentAni]->OnMove();
}

void Boss::Move(int dx, int dy)
{
	if (x + dx >= 0 && x + dx < Map::WORLD_SIZE_X)//在地圖範圍內
		this->x += dx;
	if (y + dy >= 0 && y + dy < Map::WORLD_SIZE_Y)//在地圖範圍內
		this->y += dy;
}

void Boss::JumpBack()
{
	int dx = static_cast<int>(-5 * moveSpeed * playerDistanceX / abs(playerDistanceX));//向玩家反方向跳躍
	Move(dx, -jumpDisplacement);//向上位移，並向玩家方向跳躍
}

void Boss::JumpFront()
{
	int dx = static_cast<int>(5 * moveSpeed * playerDistanceX / sqrt(pow(playerDistanceX, 2) + pow(playerDistanceY, 2)));//向玩家跳躍
	Move(dx, -jumpDisplacement);//向上位移，並向玩家方向跳躍
}

void Boss::InstantDeath()
{
}

int Boss::RandomState()
{
	if (InNear())//近距離
	{
		ChangeStateProb(nearStateProb);//變為近距攻擊狀態
		jumpMode = JUMP_BACK;//向後跳
	}

	else if (InFar())//遠距離
	{
		ChangeStateProb(farStateProb);//變為遠距攻擊狀態
		jumpMode = JUMP_FRONT;
	}

	else//超過遠距離攻擊範圍，BOSS不再攻擊玩家
		ChangeStateProb(originStateProb);//原始狀態

	unsigned int r = static_cast<int>(GameSystem::Rand(cumStateProb[STATE_LENGTH - 1]));//產生隨機亂數

	for (int i = 0; i < STATE_LENGTH; i++) // 查詢所在區間
		if (r <= cumStateProb[i])
			return i;

	return 0;
}

void Boss::ChangeStateProb(unsigned int newStateProb[])//改變各項狀態機率
{
	for (int i = 0; i < STATE_LENGTH; i++)//重置累計機率為0
		cumStateProb[i] = 0;

	for (int i = 0; i < STATE_LENGTH; i++)
	{
		currentStateProb[i] = newStateProb[i];

		for (int j = 0; j <= i; j++)
			cumStateProb[i] += currentStateProb[j];
	}
}

bool Boss::InNear()
{
	if (sqrt(pow(player->GetX() + player->GetWidth() / 2 - (x + width / 2), 2) + pow(player->GetY() + player->GetHeight() / 2 - (y + height / 2), 2)) < nearAttackRange)//近距離
		return true;
	else
		return false;
}

bool Boss::InFar()
{
	if (sqrt(pow(player->GetX() + player->GetWidth() / 2 - (x + width / 2), 2) + pow(player->GetY() + player->GetHeight() / 2 - (y + height / 2), 2)) < farAttackRange)//遠距離
		return true;
	else
		return false;
}

void Boss::ShowBitMap()
{
	switch (currentState)
	{
	case STATE_IDLE://靜止
		currentAni = ANI_IDLE;
		ani[currentAni]->OnMove();
		break;

	case STATE_MOVE://移動
		if (faceLR == FACE_LEFT)
		{
			currentAni = ANI_LEFT;
		}
		else
		{
			currentAni = ANI_RIGHT;
		}
		ani[currentAni]->OnMove();
		break;

	case STATE_NEAR_SLASH://攻擊
		if (faceLR == FACE_LEFT)
		{
			currentAni = ANI_ATTACK_LEFT;
		}
		else
		{
			currentAni = ANI_ATTACK_RIGHT;
		}
		ani[currentAni]->OnMove();

		break;
	case STATE_FAR_SHOOT:
		if (faceLR == FACE_LEFT)
		{
			currentAni = ANI_FAR_SHOOT_LEFT;
		}
		else
		{
			currentAni = ANI_FAR_SHOOT_RIGHT;
		}
		ani[currentAni]->OnMove();
		break;
	case STATE_JUMP://跳躍
		currentAni = ANI_JUMP;
		break;
	}

	GameSystem::ShowText(to_string(GetHP()), x - Map::GetSX(), y - Map::GetSY() - 30, x + width - Map::GetSX(), y + height - Map::GetSY(), GameSystem::ALIGN_CENTER, GameSystem::ALIGN_TOP, 16, RGB(0, 0, 0));
	ani[currentAni]->OnShow();
}

void Boss::LoadAni()
{
	char* aniIdle[4] = { ".\\res\\boss_idle_0.bmp", ".\\res\\boss_idle_1.bmp", ".\\res\\boss_idle_2.bmp", ".\\res\\boss_idle_3.bmp" };
	AddAniBitMaps(aniIdle, ANI::ANI_IDLE, 4, aniDelay);

	char* aniLeft[4] = { ".\\res\\boss_left_0.bmp", ".\\res\\boss_left_1.bmp", ".\\res\\boss_left_2.bmp", ".\\res\\boss_left_3.bmp" };
	AddAniBitMaps(aniLeft, ANI_LEFT, 4, aniDelay);

	char* aniRight[4] = { ".\\res\\boss_right_0.bmp", ".\\res\\boss_right_1.bmp", ".\\res\\boss_right_2.bmp", ".\\res\\boss_right_3.bmp" };
	AddAniBitMaps(aniRight, ANI_RIGHT, 4, aniDelay);

	char* aniNearSlashLeft[3] = { ".\\res\\boss_near_slash_left_0.bmp", ".\\res\\boss_near_slash_left_1.bmp", ".\\res\\boss_near_slash_left_2.bmp" };
	AddAniBitMaps(aniNearSlashLeft, ANI_NEAR_SLASH_LEFT, 3, aniDelay);

	char* aniNearSlashRight[3] = { ".\\res\\boss_near_slash_right_0.bmp", ".\\res\\boss_near_slash_right_1.bmp", ".\\res\\boss_near_slash_right_2.bmp" };
	AddAniBitMaps(aniNearSlashRight, ANI_NEAR_SLASH_RIGHT, 3, aniDelay);

	char* aniJump[3] = { ".\\res\\boss_jump_0.bmp", ".\\res\\boss_jump_1.bmp", ".\\res\\boss_jump_2.bmp" };
	AddAniBitMaps(aniJump, ANI_JUMP, 3, aniDelay);

	char* aniFarShootLeft = ".\\res\\boss_far_shoot_left";
	AddAniBitMaps(aniFarShootLeft, ANI_FAR_SHOOT_LEFT, 7, aniDelay);

	char* aniFarShootRight = ".\\res\\boss_far_shoot_right";
	AddAniBitMaps(aniFarShootRight, ANI_FAR_SHOOT_RIGHT, 7, aniDelay);
}
