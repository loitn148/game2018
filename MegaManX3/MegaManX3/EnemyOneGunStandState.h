#pragma once
#include "EnemyOneGunState.h"

#define JUMPRANGE 600

class EnemyOneGunStandState : public EnemyOneGunState
{
public:
	void Update(double time);

	void HandleKeyboard(std::map<int, bool> keys);

	OneGunStates GetState();

	void OnCollision();

	EnemyOneGunStandState(EnemyOneGunData * enemyOneGunData);
	EnemyOneGunStandState();
	~EnemyOneGunStandState();
};

