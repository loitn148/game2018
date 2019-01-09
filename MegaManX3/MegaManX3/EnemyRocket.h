#pragma once
#ifndef __ENEMYROCKET__H__
#define __ENEMYROCKET__H__

#include "GameObject.h"
#include "GameTime.h"
#include "Animation.h"
#include "Camera.h"

#include "EnemyRocketData.h"
#include "EnemyRocketState.h"

#include "Rocket.h"
#include "Blood.h"
#include "DestroyedEffect.h"
#include <iostream>
#include <vector>
#include <map>
class EnemyRocket : public GameObject
{
	EnemyRocketData* enemyRocketData;
	EnemyRocketStates currentState;
	void UpdatePosition(double time);
	Blood* blood;

public:
	Rocket* rocket;
	DestroyedEffect*destroyedEffect;
	Animation* listAnimation;
	void Init(VT3 position, int width, int height, Direct direct);
	void Draw(double time);
	void Update(double time);
	void SetState(EnemyRocketState* state);
	void SetListAnimation();
	EnemyRocket();
	~EnemyRocket();
};

#endif //__EnemyRocket__H__
