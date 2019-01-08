#pragma once
#include "EnemyOneGunState.h"

#define JUMPRANGE 600

class EnemyOneGunJumpState : public EnemyOneGunState
{
public:
	void Update(double time);

	void HandleKeyboard(std::map<int, bool> keys);

	OneGunStates GetState();

	void OnCollision();

	EnemyOneGunJumpState(EnemyOneGunData * enemyOneGunData);
	EnemyOneGunJumpState();
	~EnemyOneGunJumpState();
};

