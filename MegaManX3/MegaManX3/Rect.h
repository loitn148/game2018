#pragma once
#ifndef __RECT__H__
#define __RECT__H__

#include <d3d9.h>
#include <d3dx9.h>
#include "Global.h"

class Rect : public RECT
{
private:
	VT3 center;
public:
	VT3 GetCenter();
	Rect(int top, int left, int bottom, int right, VT3 deltaCenter = VT3(0, 0, 0));
	
	Rect();
	~Rect();
};

#endif // !__RECT__H__