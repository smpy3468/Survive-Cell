#pragma once

//Map
//�a��
//�y�Шt�κ޲z

#include "gamelib.h"

class Map
{
public:
	Map();

	static int GetSX();//���o�ù����W��X�y��
	static int GetSY();//���o�ù����W��Y�y��

	static void SetSX(int x);//�]�w�ù����W��X�y��
	static void SetSY(int y);//�]�w�ù����W��Y�y��

	static void SetStaticObject();//�]�w���|���ʪ�����y�СA�u�|�b�C���@�}�l�I�s
	static bool HasObject(int x, int y);//�Ӯy�ЬO�_������

private:
	static bool coordinate[SIZE_X][SIZE_Y];//�������Ӯy�Ц�����
	static int sx, sy;//�ù����W�����y�Цb�a�Ϯy�Ъ�����
//	static CMovingBitmap backgroundPic;//�I���Ϥ�
	
};