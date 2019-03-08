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
