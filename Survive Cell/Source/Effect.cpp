#include "StdAfx.h"
#include "Effect.h"


Effect::Effect(string tag, int x, int y, int width, int height, int pictureID):GameObject(tag, x, y, width, height, pictureID){
	hit = 0;
	currentAni = 0;
}

void Effect::SetXY(int hostX, int hostY, int hostCurrentAni) {}

void Effect::SetHit(int hit) {
	this->hit = hit;
}


void Effect::SetBitMapPosition()
{
	for (auto& i : ani)
	{
		i->SetTopLeft(this->x - Map::GetSX(), this->y - Map::GetSY());
	}
}
void Effect::LoadAni() {}
void Effect::ShowBitMap(int hostX, int hostY, int hostCurrentAni, int attackAniNumber){}

/*void Effect::ShowBitMap(int attackAniNumber, int currentAni) {
	if (attackAniNumber >= 6 && currentAni == ANI_ATTACK_LEFT) { //3�O���������A
		currentAni = ANI_FIRE_LEFT;
		SetBitMapPosition();
		ani[currentAni]->OnMove();
		ani[currentAni]->OnShow();
		if (IsPlayerInRange(0, 0, 0, 0) && ani[currentAni]->GetCurrentBitmapNumber() >= 2 && hit == 0) {
			player->DecreaseHP(1);
			hit = 1;
		}

	}
	else if (attackAniNumber >= 6 && currentAni == ANI_ATTACK_RIGHT) {//4�O�k�������A
		currentAni = ANI_FIRE_RIGHT;
		SetBitMapPosition();
		ani[currentAni]->OnMove();
		ani[currentAni]->OnShow();
		if (IsPlayerInRange(0, 0, 0, 0) && ani[currentAni]->GetCurrentBitmapNumber() >= 2 && hit == 0) {
			player->DecreaseHP(1);
			hit = 1;
		}
	}
	else hit = 0;
}*/
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

bool Effect::IsPlayerInRange(GameObject* obj, int right_fix, int left_fix, int up_fix, int down_fix) {
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
