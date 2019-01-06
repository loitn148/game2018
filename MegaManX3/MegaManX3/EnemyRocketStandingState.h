#pragma once
#include "EnemyRocketState.h"
class EnemyRocketStandingState :
	public EnemyRocketState
{
public:
	void Update(double time);

	void HandleKeyboard(std::map<int, bool> keys);

	EnemyRocketStates GetState();

	void OnCollision();

	EnemyRocketStandingState(EnemyRocketData * enemyRocketData);
	EnemyRocketStandingState();
	~EnemyRocketStandingState();
};

