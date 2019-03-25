#include "StdAfx.h"
#include "Monster.h"
#include "Player.h"
#include "Item.h"

Monster::Monster()
{
	tag = "Monster";
}


Monster::Monster(string tag, int x, int y, int width, int height, int pictureID) :Character(tag, x, y, width, height, pictureID)
{
	tag = "Monster";
	defenseRange = 300;
	attackField = 50;
	dX[0] = x - defenseRange; //����
	dX[1] = x + defenseRange;	//�k��
	rl = 1;
	SetOriginAttackRange(10);
	HP = 10;
	SetAttackRange(GetOriginAttackRange());

	//SetWidth(100);
	//SetHeight(100);
	LoadAni();
}

void Monster::SetDefenseRange(int defenseRange) {
	this->defenseRange = defenseRange;
}

int Monster::GetDefenseRange() {
	return defenseRange;
}

void Monster::SetdX() {
	dX[0] = x - defenseRange; //����
	dX[1] = x + defenseRange;	//�k��
}

void Monster::SetRL(int rl) {
	this->rl = rl;
}

int Monster::GetRL() {
	return rl;
}

int Monster::GetdX(int point) {
	if (point == 0)
		return dX[0];
	else
		return dX[1];
}

void Monster::SetdY() {
	this->dY[0] = y - defenseRange; //�U
	this->dY[1] = y + defenseRange;	//�W
}

void Monster::AutoMove() {
	if (rl == LEFT && status == STANDBY) {			//�p�GGetLR == 0 , X ��������
		this->x = x - moveSpeed;
		currentAni = ANI_LEFT;					    //�]�w�{�b�ʵe��LEFT
	}
	else if (rl == RIGHT && status == STANDBY) {
		this->x = x + moveSpeed;					//�p�GGetLR == 1 , X ���k����
		currentAni = ANI_RIGHT;						//�]�w�{�b�ʵe��RIGHT
	}

	ani[currentAni]->OnMove();						//��ܰʵe

	if (x <= dX[0] && rl != 0)       //GetdX[0]����ĵ�ٽd��A�p�G�W�L���� ��k�䲾��
		this->rl = RIGHT;

	else if (x >= dX[1] && rl != 0) //GetdX[1]�k��ĵ�ٽd��A�p�G�W�L�k�� �索�䲾��
		this->rl = LEFT;
}

bool Monster::IsInAttackField(int playerX, int playerY) {
	int attackXField_Left = x - attackField, attackXField_Right = x + attackField;
	int attackYField_down = y + attackField, attackYField_up = y - attackField;

	if (playerX >= attackXField_Left && playerX <= attackXField_Right &&
		playerY >= attackYField_up && playerY <= attackYField_down)
		return true;

	return false;
}

void Monster::Attack() {
	Player* player = GameSystem::GetGameObjectWithTag<Player>("Player");
	const int ATTACK_SPEED = 4;

	if (IsInAttackField(player->GetX(), player->GetY())) {  //�Ǫ��ĹL�h�����D��
		status = ATTACK;

		moveSpeed = ATTACK_SPEED;
		if (IsAnthorObjectInRange(player) == false) {	//�p�G�Ǫ��٨S����}��
			if (x > player->GetX()) {		//�p�G�Ǫ��b�H���k��
				x -= moveSpeed;
				currentAni = ANI_LEFT;      //�]�w�������ʵe
			}
			else if (x < player->GetX()) {  //�p�G�Ǫ��b�H������
				x += moveSpeed;
				currentAni = ANI_RIGHT;     //�]�w���k���ʵe
			}
		}
		else {
			currentAni = ANI_IDLE;  //�ݦb��a
		}
	}
	else {
		status = STANDBY;
		moveSpeed = originMoveSpeed;
		currentAni = ANI_IDLE;  //�ݦb��a
	}
}

void Monster::ShowBitMap()
{
	ani[currentAni]->OnShow();
}

void Monster::Dead()
{
	GameSystem::AddGameObject(new Item("Item", x + width / 2, y + height, 20, 10, IDB_CELL_GREEN));//���ͤ@�ӲӭM�D��

	GameSystem::DeleteGameObject(this);
}

void Monster::LoadAni()
{
	char* aniIdle[1] = { ".\\res\\demon_idle.bmp" };
	AddAniBitMaps(aniIdle, ANI_IDLE, 1);

	char* aniLeft[6] = { ".\\res\\demon_left_0.bmp",".\\res\\demon_left_1.bmp" ,".\\res\\demon_left_2.bmp"
						,".\\res\\demon_left_3.bmp" ,".\\res\\demon_left_4.bmp" ,".\\res\\demon_left_5.bmp" };
	AddAniBitMaps(aniLeft, ANI_LEFT, 6);

	char* aniRight[6] = { ".\\res\\demon_right_0.bmp", ".\\res\\demon_right_1.bmp" ,".\\res\\demon_right_2.bmp" ,
						".\\res\\demon_right_3.bmp" ,".\\res\\demon_right_4.bmp" ,".\\res\\demon_right_5.bmp" };
	AddAniBitMaps(aniRight, ANI_RIGHT, 6);
}
