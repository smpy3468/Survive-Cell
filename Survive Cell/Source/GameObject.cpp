#include "StdAfx.h"
#include "GameObject.h"


GameObject::GameObject()
{
	tag = "GameObject";
	x = 0;
	y = 0;
	width = 10;
	height = 10;
}

string GameObject::GetTag()
{
	return tag;
}

int GameObject::GetX()
{
	return this->x;
}

int GameObject::GetY()
{
	return this->y;
}

void GameObject::SetTag(string tag)
{
	this->tag = tag;
}

void GameObject::SetX(int x)
{
	this->x = x;
}

void GameObject::SetY(int y)
{
	this->y = y;
}

void GameObject::SetWidth(int width) 
{
	this-> width = width;
}

void GameObject::SetHeight(int height)
{
	this->height = height;
}

int GameObject::GetWidth()
{
	return width;
}

int GameObject::GetHeight()
{
	return height;
}

void GameObject::LoadBitMap(string pictureAddress)
{
	NULL;
}
