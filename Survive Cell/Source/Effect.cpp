#include "StdAfx.h"
#include "Effect.h"
#include "Monster.h"
#include "GameSystem.h"

//---------------------------------Constructor------------------------------//
Effect::Effect(string tag, int x, int y, int width, int height, int pictureID):GameObject(tag, x, y, width, height, pictureID){
	isHit = 0;
	currentAni = 0;
}



//-----------------------------------SetHit----------------------------------//
void Effect::SetHit(int hit) {
	this->isHit = hit;
}


void Effect::SetBitMapPosition()
{
	for (auto& i : ani)
	{
		i->SetTopLeft(this->x - Map::GetSX(), this->y - Map::GetSY());
	}
}

//-------------------------------other-----------------------------------------//

void  Effect::EffectAttackMonster(int attackDamage)
{
	vector<Monster*> allMonsters = GameSystem::GetGameObjectsWithTag<Monster>("Monster");
	for (auto& i : allMonsters) {
		if (IsObjectInRange(i, 0, 0, 0, 0) == 1) {
			i->DecreaseHP(5);
			isHit = true;
		}
	}
}

void Effect::SetXY(int hostX, int hostY, int hostCurrentAni) {}


//---------------------------Picture And Animation-----------------------------------------//
void Effect::AddAniBitMaps(char * pic[], int aniType, int picCount)
{
	for (int i = 0; i < picCount; i++)
	{
		AddAniBitMap(pic[i], aniType);
	}
}

void Effect::AddAniBitMap(char* pic, int aniType)
{
	while ((int)ani.size() <= aniType)//vector���j�p�����j
		ani.push_back(new CAnimation);//�W�[�j�p

	ani[aniType]->AddBitmap(pic, RGB(255, 255, 255));
}


void Effect::LoadAni() {}
void Effect::ShowBitMap(int hostX, int hostY, int hostCurrentAni, int attackAniNumber) {}



//---------------------------------judgment-------------------------------------//

bool Effect::IsObjectInRange(GameObject* obj, int right_fix, int left_fix, int up_fix, int down_fix) {
	int RIGHT_EDGE = x + width + right_fix, LEFT_EDGE = x - left_fix,
		UP_EDGE = y - up_fix, DOWN_EDGE = y + height + down_fix;

	int OB_X = obj->GetX(), OB_Y = obj->GetY(), OB_WIDTH = obj->GetWidth(), OB_HEIGHT = obj->GetHeight();

	int OB_RIGHT_EDGE = OB_X + OB_WIDTH, OB_LEFT_EDGE = OB_X,
		OB_UP_EDGE = OB_Y, OB_DOWN_EDGE = OB_Y + OB_HEIGHT;

	if (OB_RIGHT_EDGE >= LEFT_EDGE && OB_RIGHT_EDGE <= RIGHT_EDGE)        //�H�b��, ���K�b�k
		return true;
	else if (OB_LEFT_EDGE <= RIGHT_EDGE && OB_LEFT_EDGE >= LEFT_EDGE)  //�H�b�k, ���K�b��
		return true;
	/*else if (OB_DOWN_EDGE > UP_EDGE)       //�H�b�U, �Ǫ��b�W
			return true;
	else if (OB_UP_EDGE < DOWN_EDGE)	   //�H�b�W, �Ǫ��b�U
			return true;*/
	return false;
}


bool Effect::CanMoveLeft(int perDisplacement)
{
	bool canMoveLeft = true;
	for (int i = y; i < y + height; i++)
	{
		if (Map::HasObject(this->x - perDisplacement, i))//���b�䦳�F��
		{
			canMoveLeft = false;
			return canMoveLeft;
		}
	}
	return canMoveLeft;
}

bool Effect::CanMoveRight(int perDisplacement)
{
	bool canMoveRight = true;
	for (int i = y; i < y + height; i++)
	{
		if (Map::HasObject(this->x + this->width + perDisplacement, i))//�k�b�䦳�F��
		{
			canMoveRight = false;
			return canMoveRight;
		}
	}
	return canMoveRight;
}

bool Effect::CanMoveUp(int perDisplacement)
{
	bool canMoveUp = true;
	for (int i = x; i < x + width; i++)
	{
		if (Map::HasObject(i, y - perDisplacement) || y < 0)//�W�����F��
		{
			canMoveUp = false;
			return canMoveUp;
		}
	}
	return canMoveUp;
}

bool Effect::CanMoveDown(int perDisplacement)
{
	bool canMoveDown = true;
	for (int i = x; i < x + width; i++)
	{
		if (Map::HasObject(i, y + height + perDisplacement))//�U�����F��
		{
			canMoveDown = false;
			return canMoveDown;
		}
	}
	return canMoveDown;
}