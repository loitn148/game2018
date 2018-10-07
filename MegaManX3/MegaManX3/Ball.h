#pragma once
#ifndef __BALL__H__
#define __BALL__H__

#include "GameObject.h"
#include "Animation.h"
#include "Viewport.h"
#include "Camera.h"
#include "Collision.h"

class Ball : public GameObject
{
public:
	bool isDead;
	void Draw(float time);
	void Update(float time);
	Ball(VT3 position, float vx, float vy);
	Ball();
	~Ball();
protected:
	Animation* listBall;
	int currentState;
};
#endif // !__BALL__H__