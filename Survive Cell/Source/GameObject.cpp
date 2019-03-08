#include "StdAfx.h"
#include "GameObject.h"


GameObject::GameObject()
{
	tag = "GameObject";
}

string GameObject::GetTag()
{
	return tag;
}

void GameObject::SetTag(string tag)
{
	this->tag = tag;
}

void GameObject::SetWidth(int width) 
{
	this-> width = width;
}


int GameObject::GetWidth()
{
	return width;
}


void GameObject::SetLength(int length)
{
	this->length = length;
}

int GameObject::GetLength()
{
	return length;
}

void GameObject::LoadBitMap(string pictureAddress)
{
	NULL;
}
