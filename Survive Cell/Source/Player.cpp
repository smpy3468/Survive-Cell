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
	if ((dx > 0 && CanMoveRight(moveSpeed)) || (dx < 0 && CanMoveLeft(moveSpeed)))//x�첾�q���k�ӥB�k��S�F�� �Ϊ� x�첾�q�����ӥB����S�F��
	{
		this->x += dx;//���ax����
	}

	this->y += dy;//���ay����

	if (dx > 0 && this->x + this->width / 2 >= Map::GetSX() + SIZE_X / 2)
		Map::MoveScreenTopLeft(dx, 0);//�ù�����
	else if (dx < 0 && this->x + this->width / 2 < Map::GetSX() + SIZE_X / 2)
		Map::MoveScreenTopLeft(dx, 0);//�ù�����

	if (dy > 0 && this->y + this->height / 2 >= Map::GetSY() + SIZE_Y * 3 / 4)
		Map::MoveScreenTopLeft(0, dy);//�ù�����
	else if (dy < 0 && this->y + this->height / 2 < Map::GetSY() + SIZE_Y / 4)
		Map::MoveScreenTopLeft(0, dy);//�ù�����
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

void Player::Move()//���ʤ�V
{
	if (!this->isAttack)//�p�G���O�b�������A
	{
		if (this->isMoveLeft)
		{
			if (this->x > 0)
			{
				faceLR = FACE_LEFT;//���V����
				Move(-moveSpeed, 0);
			}
		}

		if (this->isMoveRight)
		{
			if (this->x + this->width < Map::WORLD_SIZE_X)
			{
				faceLR = FACE_RIGHT;//���V�k��
				Move(moveSpeed, 0);
			}
		}

		if (this->isJumpKeyDown)//�p�G���U���D
		{
			if (isGrounded)//�p�G�b�a�W
			{
				isJump = true;//���b���D
				isGrounded = false;//�S�b�a�W
			}
		}
	}

	if (isJump)
		Jump();//���D
	else
		Fall();//�U��
}

void Player::Fall()
{
	if (CanMoveDown(fallDisplacement))//�p�G�}�U�S�F��
	{
		isFall = true;//���b�U��
		isGrounded = false;//���b�a�W
		fallDisplacement++;
		Move(0, fallDisplacement);
	}
	else
	{
		while (CanMoveDown(1))//�A�~��ΤU���첾�q�U���A�N�|�d�i�a�O�A�ҥH�@���V�U�첾1�i��L��
			Move(0, 1);

		fallDisplacement = 0;
		isGrounded = true;//�b�a�W
		isFall = false;//�S�b�U��

		if (currentAni == ANI::ANI_JUMP_LEFT)//�N���D�ʵe�٭�
			currentAni = ANI::ANI_LEFT;
		else if (currentAni == ANI::ANI_JUMP_RIGHT)
			currentAni = ANI::ANI_RIGHT;
	}
}

void Player::Jump()
{
	if (isGrounded == false && isFall == false)//�p�G�S�b�a�W�B�S�b�U��
	{
		jumpDisplacement--;//�첾�q�H�ۮɶ�����

		if (jumpDisplacement >= 0)//���W��
		{
			if (CanMoveUp(jumpDisplacement))//�i�V�W����
				Move(0, -jumpDisplacement);
			else
				jumpDisplacement = 0;//�}�l���U��
		}
		else//���U��
		{
			isJump = false;
			isFall = true;
			jumpDisplacement = originJumpDisplacement;//���D�첾�q�٭�
		}
	}
}

void Player::Interact()
{
	for (auto& i : GameSystem::GetAllGameObject())//�磌�󤬰�
	{
		if (i->GetTag() == "Item" || i->GetTag() == "Potion" || i->GetTag() == "ItemWeapon")//�O���~
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

	for (auto& i : monsters)//��Ǫ�����
	{
		if (i->GetX() + i->GetWidth() > this->x - attackRange && i->GetX() < this->x + this->width + attackRange
			&& i->GetY() + i->GetHeight() > this->y && i->GetY() < this->y + this->height)//�Ǫ��b�����d��
		{
			i->DecreaseHP(attackDamage);
		}
	}

	isAttack = false;//��������
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
	else if (isJump || isFall)//���D�ʵe
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
	else if (isMoveLeft)//�����ʵe
	{
		currentAni = ANI::ANI_LEFT;
		ani[ANI::ANI_LEFT]->OnMove();

	}
	else if (isMoveRight)//�k���ʵe
	{
		currentAni = ANI::ANI_RIGHT;
		ani[ANI::ANI_RIGHT]->OnMove();
	}
	else
	{
		for (auto& i : ani)
		{
			i->Reset();//���m�Ҧ��ʵe
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
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f, *fp;
	f.CreatePointFont(80, "Times New Roman");	// ���� font f; 160���16 point���r
	fp = pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkMode(TRANSPARENT);				//�z���I��
	pDC->SetTextColor(RGB(0, 0, 255));

	char str[800];								// Demo �Ʀr��r�ꪺ�ഫ

	sprintf(str, "HP:%d\nAttack:%d\nAttack Speed:%d\nAttackRange:%d\nMoveSpeed:%d\nDefense:%d\n"
		, GetHP(), GetAttackDamage(), GetAttackSpeed(), GetAttackRange(), GetMoveSpeed(), GetDefense());

	CRect rect = { 0,30,SIZE_X,SIZE_Y };//�]�w�x�Υ��B�W�B�k�B�U���y��
	pDC->DrawText(str, rect, DT_LEFT | DT_WORDBREAK);//�a������A�i����

	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
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

	if (!hasWeapon)//�٨S���Z��
	{
		if (equipment->GetTag() == "ItemWeapon")//�O�Z��
		{
			this->weapon = new PlayerEquipment(equipment);//���B�����D
		}
	}

}*/

void Player::CalculateAbility(PlayerEquipment* equipment)
{
	//�����O�P���m�֥[�W�h
	this->attackDamage += equipment->GetAttackDamage();
	this->defense += equipment->GetDefense();

	//�����Z���ϥΪZ���������Z��
	this->attackRange = equipment->GetAttackRange();
}

void Player::Dead()
{
	GameSystem::SetGameOver();//�C������
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

	//---------------�R��
	char* aniIdle[1] = { ".\\res\\player_idle.bmp" };
	AddAniBitMaps(aniIdle, ANI::ANI_IDLE, 1);

	//---------------����
	char* aniLeft[4] = { ".\\res\\player_left_0.bmp", ".\\res\\player_left_1.bmp", ".\\res\\player_left_2.bmp", ".\\res\\player_left_3.bmp" };
	AddAniBitMaps(aniLeft, ANI::ANI_LEFT, 4);

	//---------------�k��
	char* aniRight[4] = { ".\\res\\player_right_0.bmp", ".\\res\\player_right_1.bmp", ".\\res\\player_right_2.bmp", ".\\res\\player_right_3.bmp" };
	AddAniBitMaps(aniRight, ANI::ANI_RIGHT, 4);

	//---------------����
	char* aniJumpLeft = ".\\res\\player_jump_left.bmp";
	AddAniBitMap(aniJumpLeft, ANI::ANI_JUMP_LEFT);

	//---------------�k��
	char* aniJumpRight = ".\\res\\player_jump_right.bmp";
	AddAniBitMap(aniJumpRight, ANI::ANI_JUMP_RIGHT);

	//---------------����
	char* aniAttackLeft[3] = { ".\\res\\player_attack_left_0.bmp", ".\\res\\player_attack_left_1.bmp", ".\\res\\player_attack_left_2.bmp" };
	AddAniBitMaps(aniAttackLeft, ANI::ANI_ATTACK_LEFT, 3, 5);

	//---------------�k��
	char* aniAttackRight[3] = { ".\\res\\player_attack_right_0.bmp", ".\\res\\player_attack_right_1.bmp", ".\\res\\player_attack_right_2.bmp" };
	AddAniBitMaps(aniAttackRight, ANI::ANI_ATTACK_RIGHT, 3, 5);

	//---------------���Q��
	char* aniGetHitLeft = ".\\res\\player_get_hit_left.bmp";
	AddAniBitMap(aniGetHitLeft, ANI::ANI_GET_HIT_LEFT);

	//---------------�k�Q��
	char* aniGetHitRight = ".\\res\\player_get_hit_right.bmp";
	AddAniBitMap(aniGetHitRight, ANI::ANI_GET_HIT_RIGHT);
}
