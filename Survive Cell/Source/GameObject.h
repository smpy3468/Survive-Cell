#pragma once

//GameObject
//�C������
//���W�Ҧ�����Base Class

#include "StdAfx.h"
#include <string>
using namespace std;

class GameObject
{
public:
	GameObject();
	string GetTag();
	void SetTag(string tag);
protected:
	string tag;//�������
};