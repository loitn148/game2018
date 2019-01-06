#pragma once
#include "EnemySweepingState.h"
class EnemySweepingShootingState :
	public EnemySweepingState
{
public:
	void Update(double time);

	void HandleKeyboard(std::map<int, bool> keys);

	EnemySweepingStates GetState();

	void OnCollision();

	EnemySweepingShootingState(EnemySweepingData * enemyRocketData);
	EnemySweepingShootingState();
	~EnemySweepingShootingState();
};

