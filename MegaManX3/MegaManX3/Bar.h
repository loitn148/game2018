#pragma once
#ifndef __BAR__H__
#define __BAR__H__
#include "GameObject.h"
#include "Animation.h"
#include "Viewport.h"
#include "Camera.h"
#include "Collision.h"
#include "Ball.h"
#include "GameInput.h"

class Bar : public GameObject, public GameInput
{
public:
	bool isDead;
	void Draw(double time);
	void Update(double time);
	void OnKeyUp(int keyCode);
	void OnKeyDown(int keyCode);
	int barIdx;
	HWND hWnd;
	HINSTANCE hInstance;
	Bar(VT3 position, double vx, double vy, HWND hWnd, HINSTANCE hInstance, int barIdx);
protected:
	Animation* listBar;
	int currentState;
public:
	Bar();
	~Bar();
};
#endif __BAR__H__
