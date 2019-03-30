#pragma once

//Map
//�a��
//�y�Шt�κ޲z

#include "gamelib.h"
using namespace game_framework;

class Map
{
public:
	Map();

	static void LoadBackgroundPic();//���J�I���Ϥ�
	static void ShowBackgroundPic();//��ܭI���Ϥ�

	static int GetSX();//���o�ù����W��X�y��
	static int GetSY();//���o�ù����W��Y�y��

	static void SetSX(int x);//�]�w�ù����W��X�y��
	static void SetSY(int y);//�]�w�ù����W��Y�y��

	static void MoveScreenTopLeft(int dx, int dy);//���ʿù����W����m

	static void SetStaticObject();//�]�w���|���ʪ�����y�СA�u�|�b�C���@�}�l�I�s
	static bool HasObject(int x, int y);//�Ӯy�ЬO�_������

	static const int WORLD_SIZE_X = 3 * 640, WORLD_SIZE_Y = 480;//��ӹC���a�Ϫ����e
private:
	static bool coordinate[WORLD_SIZE_X][WORLD_SIZE_Y];//�������Ӯy�Ц�����
	static int sx, sy;//�ù����W�����y�Цb�a�Ϯy�Ъ�����
	static CMovingBitmap backgroundPic;//�I���Ϥ�
};