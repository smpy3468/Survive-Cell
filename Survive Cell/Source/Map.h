#pragma once

//Map
//�a��
//�y�Шt�κ޲z

#include "gamelib.h"

class Map
{
public:
	Map();
	static void SetStaticObject();//�]�w���|���ʪ�����y�СA�u�|�b�C���@�}�l�I�s
	static void SetDynamicObject();//�]�w�|���ʪ�����y��(���a�B�Ǫ�)
	static bool HasObject(int x, int y);//�Ӯy�ЬO�_������
private:
	static bool coordinate[SIZE_X][SIZE_Y];//�������Ӯy�Ц�����
};