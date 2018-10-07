#pragma once
#ifndef __VIEWPORT__H__
#define __VIEWPORT__H__

#include <d3dx9.h>
#include "Global.h"

class Viewport
{
private:
	static Viewport* instance;
	int x, y;
public:
	int GetX();
	int GetY();
	void Init(int x, int y);
	VT3 GetPositionInViewport(VT3 worldPosition);
	static Viewport* GetInstance();
	Viewport();
	~Viewport();
};

#endif // !__VIEWPORT__H__

