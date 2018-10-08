#pragma once
#ifndef __BAR__H__
#define __BAR__H__
#include "GameObject.h"
#include "Animation.h"
#include "Viewport.h"
#include "Camera.h"
#include "Collision.h"
#include "Ball.h"
class Bar : public GameObject
{
public:
	bool isDead;
	void Draw(double time);
	void Update(double time);
	Bar(VT3 position, double vx, double vy);
protected:
	Animation* listBar;
	int currentState;
public:
	Bar();
	~Bar();
};
#endif
