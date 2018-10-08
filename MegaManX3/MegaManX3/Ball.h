#pragma once
#ifndef __BALL__H__
#define __BALL__H__

#include "Bar.h"
#include "GameObject.h"
#include "Animation.h"
#include "Viewport.h"
#include "Camera.h"
#include "Collision.h"

class Bar;

class Ball : public GameObject 
{
protected:
	Bar* bar;
	Bar* bar2;
	Animation* listBall;
	int currentState;
public:
	bool isDead;
	void Draw(double time);
	void Update(double time);
	void SetBar(Bar* bar, Bar* bar2);
	Ball(VT3 position, double vx, double vy);
	Ball();
	~Ball();
};
#endif // !__BALL__H__