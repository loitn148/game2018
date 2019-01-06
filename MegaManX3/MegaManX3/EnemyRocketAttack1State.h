#pragma once
#include "EnemyRocketState.h"
class EnemyRocketAttack1State :
	public EnemyRocketState
{
public:
	void Update(double time);

	void HandleKeyboard(std::map<int, bool> keys);

	EnemyRocketStates GetState();

	void OnCollision();

	EnemyRocketAttack1State(EnemyRocketData * enemyRocketData);
	EnemyRocketAttack1State();
	~EnemyRocketAttack1State();
};

