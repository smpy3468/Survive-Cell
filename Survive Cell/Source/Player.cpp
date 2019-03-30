#include "StdAfx.h"
#include "GameSystem.h"
#include "Player.h"
#include "Monster.h"
#include "Map.h"
#include "Item.h"

Player::Player()
{
	tag = "Player";
}

Player::Player(string tag, int x, int y, int width, int height, int pictureID) :Character(tag, x, y, width, height, pictureID)
{
	tag = "Player";

	maxHP = 3;
	HP = maxHP;

	originMoveSpeed = 5;
	moveSpeed = originMoveSpeed;

	fallDisplacement = 0;

	originJumpDisplacement = 15;
	jumpDisplacement = originJumpDisplacement;

	attackRange = 10;
	attackDamage = 5;

	isMoveLeft = false;
	isMoveRight = false;

	isJumpKeyDown = false;
	isJump = false;
	isFall = false;
	isGrounded = false;

	currentAni = ANI::ANI_IDLE;

	layer = GameSystem::LAYER::LAYER_PLAYER;

	LoadAni();
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

void Player::SetIsGrounded(bool isGrounded)
{
	this->isGrounded = isGrounded;
}

void Player::Move()//���ʤ�V
{
	if (this->isMoveLeft)
	{
		if (this->x > 0)
			Move(-moveSpeed, 0);
	}

	if (this->isMoveRight)
	{
		if (this->x + this->width < Map::WORLD_SIZE_X)
			Move(moveSpeed, 0);
	}

	if (this->isJumpKeyDown)//�p�G���U���D
	{
		if (isGrounded)//�p�G�b�a�W
		{
			isJump = true;//���b���D
			isGrounded = false;//�S�b�a�W
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
			if(CanMoveUp(jumpDisplacement))//�i�V�W����
				Move(0, -jumpDisplacement);
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
		if (i->GetTag() == "Item" || i->GetTag() == "Potion")//�O���~
		{
			if (i->GetX() > this->x && i->GetX() < this->x + this->width
				&& i->GetY() > this->y && i->GetY() < this->y + this->height)
				static_cast<Item*>(i)->Picked();
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
}

void Player::ShowBitMap()
{
	if (isJump || isFall)//���D�ʵe
	{
		if (currentAni == ANI::ANI_LEFT)
		{
			currentAni = ANI::ANI_JUMP_LEFT;
		}
		else if (currentAni == ANI::ANI_RIGHT)
		{
			currentAni = ANI::ANI_JUMP_RIGHT;
		}
		else if (currentAni == ANI::ANI_JUMP_LEFT && isMoveRight)//���V������D�ɫ��U�k��n���V�k��
		{
			currentAni = ANI::ANI_JUMP_RIGHT;
		}
		else if (currentAni == ANI::ANI_JUMP_RIGHT && isMoveLeft)//���V�k����D�ɫ��U����n���V����
		{
			currentAni = ANI::ANI_JUMP_LEFT;
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
	}

	ani[currentAni]->OnShow();
}

void Player::ShowInformation()
{
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f, *fp;
	f.CreatePointFont(80, "Times New Roman");	// ���� font f; 160���16 point���r
	fp = pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkColor(RGB(255, 255, 255));
	pDC->SetTextColor(RGB(0, 0, 0));
	char str[800];								// Demo �Ʀr��r�ꪺ�ഫ

	sprintf(str, "HP:%d", GetHP());
	pDC->TextOut(0, 0, str);

	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
}

void Player::Dead()
{
	GameSystem::SetGameOver();//�C������
	//GameSystem::DeleteGameObject(this);
}

void Player::LoadAni()
{
	char* aniIdle[1] = { ".\\res\\player_idle.bmp" };
	AddAniBitMaps(aniIdle, ANI::ANI_IDLE, 1);

	char* aniLeft[4] = { ".\\res\\player_left_0.bmp", ".\\res\\player_left_1.bmp", ".\\res\\player_left_2.bmp", ".\\res\\player_left_3.bmp" };
	AddAniBitMaps(aniLeft, ANI::ANI_LEFT, 4);

	char* aniRight[4] = { ".\\res\\player_right_0.bmp", ".\\res\\player_right_1.bmp", ".\\res\\player_right_2.bmp", ".\\res\\player_right_3.bmp" };
	AddAniBitMaps(aniRight, ANI::ANI_RIGHT, 4);

	char* aniJumpLeft = ".\\res\\player_jump_left.bmp";
	AddAniBitMap(aniJumpLeft, ANI::ANI_JUMP_LEFT);

	char* aniJumpRight = ".\\res\\player_jump_right.bmp";
	AddAniBitMap(aniJumpRight, ANI::ANI_JUMP_RIGHT);
}
