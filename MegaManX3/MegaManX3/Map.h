#pragma once
#ifndef __MAP__H__
#define __MAP__H__

#include "GameGraphic.h"
#include "Global.h"
#include "Camera.h"
#include "Viewport.h"

class Map
{
private:
	VT3 position;
	RECT mapRect;

public:
	TEXTURE mapTexture;
	void LoadResource();
	void Draw();

	Map(int x, int y, int z);
	Map();
	~Map();
};
#endif // !__MAP__H__