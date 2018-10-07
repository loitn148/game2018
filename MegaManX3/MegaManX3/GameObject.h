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
	float dx, dy;
	VT3 position;
	int width, height;
	float v0, vx, vy;
	float ax, ay;
	Direct direct;
	Rect rectBound;
	Transform transform;
public:
	Object GetId();
	float GetV0();
	float GetVx();
	float GetVy();
	float GetAx();
	float GetAy();
	Rect GetRect();
	int GetWidth();
	int GetHeight();

	VT3 GetPosition();
	VT3 GetCenterPosition();

	void SetId(Object obj);
	void SetPosition(VT3 position);
	void SetV0(float v0);
	void SetVx(float vx);
	void SetVy(float vy);
	void SetAx(float ax);
	void SetAy(float ay);
	void SetRect(Rect rect);
	void UpdateRect();

	void Create(VT3 position, int width, int height, Rect rect);

	VT3 GetPositionInViewport();

	GameObject();
	~GameObject();
};
#endif // !__GAMEOBJECT__H__



