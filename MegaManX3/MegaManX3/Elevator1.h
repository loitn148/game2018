#pragma once
#ifndef __ELEVATOR1__H__
#define __ELEVATOR1__H__

#include "GameObject.h"
#include "Animation.h"
#include "Camera.h"
#include "Global.h"

class Elevator1 :
	public GameObject
{
public:
	void Update(double time);
	void Draw(double time);
	bool isActive;
	bool isStop;
	Elevator1(VT3 position, double vx, double vy);
	Elevator1();
	~Elevator1();
	Animation* animation;
	void SetIsActive(bool isActive);
	bool GetIsActive();
};
#endif // !__ELEVATOR1__H__