#pragma once
#ifndef __COLLISION__H__
#define __COLLISION__H__

#include <d3dx9.h>
#include "Rect.h"
#include "Global.h"
#include <iostream>
using namespace std;

class Collision
{
public:
	static CollisionResult SweptAABB(Rect rect1, VT2 v1, Rect rect2, VT2 v2, float time);
	Collision();
	~Collision();
};
#endif // !__COLLISION__H__