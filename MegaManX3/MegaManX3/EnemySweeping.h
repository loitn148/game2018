#pragma once
#ifndef __ENEMYSWEEPING__H__
#define __ENEMYSWEEPING__H__
#include "GameObject.h"
#include "GameTime.h"
#include "Animation.h"
#include "Camera.h"

#include "EnemySweepingData.h"
#include "EnemySweepingState.h"

#include "RocketEnemy3.h"

#include <iostream>
#include <vector>
#include <map>

class EnemySweeping :
	public GameObject
{
	EnemySweepingData* enemySweepingData;
	EnemySweepingStates currentState;
	void UpdatePosition(double time);
public:
	RocketEnemy3* rocket;
	VT3 oldPosition;
	Animation* listAnimation;
	void Init(VT3 position, int width, int height, Direct direct);
	void Draw(double time);
	void Update(double time);
	void SetState(EnemySweepingState* state);
	void SetListAnimation();
	EnemySweeping();
	~EnemySweeping();
};
#endif
