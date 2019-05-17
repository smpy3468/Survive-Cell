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

	for (int i = 0; i < STATE_LENGTH; i++)//�إߦU�����v��
	{
		for (int j = 0; j <= i; j++)
			cumStateProb[i] += originStateProb[j];
	}

	phase = 1;//�Ĥ@���q
	currentState = STATE_IDLE;//�w�]�ʧ@
}

void Boss::Act()
{
	if (static_cast<float>(HP) / maxHP <= 0.5)//�ĤG���q
	{
		phase = 2;
	}

	//currentState = STATE_FAR_SHOOT;
	switch (currentState)//�ھڪ��A�����P�ʧ@
	{
	case STATE_IDLE://�R��

		//faceLR = static_cast<int>(GameSystem::Rand(2));

		//if (ani[currentAni]->IsEnd())//�����ʵe��
	{
		currentState = RandomState();//�H�����ܪ��A

		if (currentState == STATE_JUMP)//�U�@�Ӫ��A�O���D�ɡA�������a��BOSS���Z��
		{
			playerDistanceX = player->GetX() - x;
			playerDistanceY = player->GetY() - y;
		}
	}

	if (player->GetX() - x < 0)//���a�b����
		faceLR = FACE_LEFT;//���V����
	else
		faceLR = FACE_RIGHT;//���ۥk��

	break;
	case STATE_MOVE://����
		if (faceLR == FACE_LEFT)
		{
			Move(-moveSpeed, 0);
		}
		else
		{
			Move(moveSpeed, 0);
		}

		if (ani[currentAni]->IsEnd())//���ʰʵe����
		{
			currentState = STATE_IDLE;//�N�^���R��A
		}

		break;
	case STATE_NEAR_SLASH://����
		NearSlash();
		break;
	case STATE_FAR_SHOOT://�g��
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
	if (CanMoveDown(fallDisplacement))//�p�G�}�U�S�F��
	{
		fallDisplacement++;
		Move(0, fallDisplacement);
	}
	else
	{
		while (CanMoveDown(1))//�A�~��ΤU���첾�q�U���A�N�|�d�i�a�O�A�ҥH�@���V�U�첾1�i��L��0
			Move(0, 1);
		fallDisplacement = 0;

	}
}

void Boss::NearSlash()
{
	if (ani[currentAni]->IsEnd())//�����P�w�u�|�X�{�@���A�]�������ʵe�����~����
	{
		int leftEdge = 0, rightEdge = 0;
		if (faceLR == FACE_LEFT)//�]�w�V�����
		{
			leftEdge = this->x - attackRange;
			rightEdge = this->x + this->width / 2;
		}
		else//�]�w�V�k���
		{
			leftEdge = this->x + this->width / 2;
			rightEdge = this->x + this->width + attackRange;
		}

		if (player->GetX() + player->GetWidth() / 2 > leftEdge
			&& player->GetX() + player->GetWidth() / 2 < rightEdge
			&& player->GetY() + player->GetHeight() > this->y
			&& player->GetY() < this->y + this->height)//���a�b�d��
		{
			player->DecreaseHP(attackDamage);//�������a
		}

		currentState = STATE_IDLE;//�^���R��A
	}
}

void Boss::FarShoot()
{
	if (ani[currentAni]->IsEnd())
	{
		isShoot = false;
		currentState = STATE_IDLE;//�^���R��A
	}
	else if (ani[currentAni]->GetCurrentBitmapNumber() == 3)//�ĤT�i�Ϥ��ɵo�g�l�u
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
	if (jumpDisplacement-- > 0)//���D�첾�q�H�ɶ�����
	{
		if (jumpMode == JUMP_BACK)//�b��B
			JumpBack();//�V���
		else if (jumpMode == JUMP_FRONT)//�b����
			JumpFront();//�V�e��
	}
	else
	{
		jumpDisplacement = originJumpDisplacement;//���D�첾�q�٭�

		if (player->GetX() + player->GetWidth() > this->x - attackRange
			&& player->GetX() < this->x + this->width + attackRange
			&& player->GetY() + player->GetHeight() > this->y + this->height / 2
			&& player->GetY() < this->y + this->height)//���a�b�d��
		{
			if (player->GetIsJump() == false)//���a�S���b���D
				player->DecreaseHP(attackDamage);//�������a
		}

		currentState = STATE_IDLE;//�^���R��A
	}

	ani[currentAni]->OnMove();
}

void Boss::Move(int dx, int dy)
{
	if (x + dx >= 0 && x + dx < Map::WORLD_SIZE_X)//�b�a�Ͻd��
		this->x += dx;
	if (y + dy >= 0 && y + dy < Map::WORLD_SIZE_Y)//�b�a�Ͻd��
		this->y += dy;
}

void Boss::JumpBack()
{
	int dx = static_cast<int>(-5 * moveSpeed * playerDistanceX / abs(playerDistanceX));//�V���a�Ϥ�V���D
	Move(dx, -jumpDisplacement);//�V�W�첾�A�æV���a��V���D
}

void Boss::JumpFront()
{
	int dx = static_cast<int>(5 * moveSpeed * playerDistanceX / sqrt(pow(playerDistanceX, 2) + pow(playerDistanceY, 2)));//�V���a���D
	Move(dx, -jumpDisplacement);//�V�W�첾�A�æV���a��V���D
}

void Boss::InstantDeath()
{
}

int Boss::RandomState()
{
	if (InNear())//��Z��
	{
		ChangeStateProb(nearStateProb);//�ܬ���Z�������A
		jumpMode = JUMP_BACK;//�V���
	}

	else if (InFar())//���Z��
	{
		ChangeStateProb(farStateProb);//�ܬ����Z�������A
		jumpMode = JUMP_FRONT;
	}

	else//�W�L���Z�������d��ABOSS���A�������a
		ChangeStateProb(originStateProb);//��l���A

	unsigned int r = static_cast<int>(GameSystem::Rand(cumStateProb[STATE_LENGTH - 1]));//�����H���ü�

	for (int i = 0; i < STATE_LENGTH; i++) // �d�ߩҦb�϶�
		if (r <= cumStateProb[i])
			return i;

	return 0;
}

void Boss::ChangeStateProb(unsigned int newStateProb[])//���ܦU�����A���v
{
	for (int i = 0; i < STATE_LENGTH; i++)//���m�֭p���v��0
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
	if (sqrt(pow(player->GetX() + player->GetWidth() / 2 - (x + width / 2), 2) + pow(player->GetY() + player->GetHeight() / 2 - (y + height / 2), 2)) < nearAttackRange)//��Z��
		return true;
	else
		return false;
}

bool Boss::InFar()
{
	if (sqrt(pow(player->GetX() + player->GetWidth() / 2 - (x + width / 2), 2) + pow(player->GetY() + player->GetHeight() / 2 - (y + height / 2), 2)) < farAttackRange)//���Z��
		return true;
	else
		return false;
}

void Boss::ShowBitMap()
{
	switch (currentState)
	{
	case STATE_IDLE://�R��
		currentAni = ANI_IDLE;
		ani[currentAni]->OnMove();
		break;

	case STATE_MOVE://����
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

	case STATE_NEAR_SLASH://����
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
	case STATE_JUMP://���D
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
