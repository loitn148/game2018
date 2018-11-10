#pragma once
#ifndef __GAMEOBJECT__H__
#define __GAMEOBJECT__H__

#include <d3d9.h>
#include <d3dx9.h>
#include "Global.h"
#include "Rect.h"
#include "Viewport.h"
class GameObject
{
protected:
	Object id;
	double dx, dy;
	VT3 position;
	int width, height;
	double v0, vx, vy;
	double ax, ay;
	Direct direct;
	Rect rectBound;
	Transform transform;
public:
	Object GetId();
	double GetV0();
	double GetVx();
	double GetVy();
	double GetAx();
	double GetAy();
	Rect GetRect();
	Direct GetDirect();
	int GetWidth();
	int GetHeight();

	VT3 GetPosition();
	VT3 GetCenterPosition();

	void SetId(Object obj);
	void SetPosition(VT3 position);
	void SetV0(double v0);
	void SetVx(double vx);
	void SetVy(double vy);
	void SetAx(double ax);
	void SetAy(double ay);
	void SetRect(Rect rect);
	void SetDirect(Direct direct);
	void UpdateRect();

	void Create(VT3 position, int width, int height, Rect rect);

	VT3 GetPositionInViewport();

	GameObject();
	~GameObject();
};
#endif // !__GAMEOBJECT__H__



