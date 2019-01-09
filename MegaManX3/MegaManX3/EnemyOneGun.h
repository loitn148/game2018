#pragma once
#ifndef __ENEMYONEGUN__H__
#define __ENEMYONEGUN__H__

#include "GameObject.h"
#include "GameTime.h"
#include "Animation.h"
#include "Camera.h"

#include "Blood.h"
#include "EnemyOneGunData.h"
#include "EnemyOneGunState.h"
#include "EnemyOneGunJumpState.h"
#include "EnemyOneGunStandState.h"
#include "Rocket.h"
#include "OneGunBullet.h"
#include "DestroyedEffect.h"
#include <iostream>
#include <vector>
#include <map>
class EnemyOneGun : public GameObject
{
	EnemyOneGunData* enemyOneGunData;
	OneGunStates currentState;

	Blood* blood;
	void UpdatePosition(double time);
public:
	vector<OneGunBullet*> vtRocket;
	DestroyedEffect*destroyedEffect;
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
