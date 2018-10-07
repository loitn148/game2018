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
	void Draw(float time);
	void Update(float time);
	Bar(VT3 position, float vx, float vy);
protected:
	Animation* listBar;
	int currentState;
public:
	Bar();
	~Bar();
};
#endif
