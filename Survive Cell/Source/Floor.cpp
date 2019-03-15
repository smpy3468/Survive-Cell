#include "StdAfx.h"
#include "Floor.h"

Floor::Floor()
{
	tag = "Floor";
}

Floor::Floor(string tag, int x, int y, int width, int height, int pictureID) :GameObject(tag, x, y, width, height, pictureID)
{

}
