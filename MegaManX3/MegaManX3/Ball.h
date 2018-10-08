#pragma once
#ifndef __BALL__H__
#define __BALL__H__

#include "Bar.h"
#include "GameObject.h"
#include "Animation.h"
#include "Viewport.h"
#include "Camera.h"
#include "Collision.h"

class Ball : public GameObject
{
public:
	bool isDead;
	void Draw(double time);
	void Update(double time);
	void SetBar(GameObject *b);
	Ball(VT3 position, double vx, double vy);
	Ball();
	~Ball();
protected:
	GameObject* bar;
	Animation* listBall;
	int currentState;
};
#endif // !__BALL__H__