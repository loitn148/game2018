#pragma once
#ifndef __ENEMYONEGUN__H__
#define __ENEMYONEGUN__H__

#include "GameEnemy.h"
#include "GameTime.h"
#include "Animation.h"
#include "Camera.h"

#include "EnemyOneGunData.h"
#include "EnemyOneGunState.h"
#include "EnemyOneGunJumpState.h"
#include "EnemyOneGunStandState.h"
#include "Rocket.h"
#include "OneGunBullet.h"

#include <iostream>
#include <vector>
#include <map>
class EnemyOneGun : public GameEnemy
{
	EnemyOneGunData* enemyOneGunData;
	OneGunStates currentState;
	void UpdatePosition(double time);
public:
	vector<OneGunBullet*> vtRocket;

	Animation* listAnimation;
	void Init(VT3 position, int width, int height);
	void Draw(double time);
	void Update(double time);
	void SetState(EnemyOneGunState* state);
	void SetListAnimation();
	EnemyOneGun();
	~EnemyOneGun();
};

#endif //__ENEMYONEGUN__H__
