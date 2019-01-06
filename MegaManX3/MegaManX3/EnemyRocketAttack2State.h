#pragma once
#include "EnemyRocketState.h"
class EnemyRocketAttack2State :
	public EnemyRocketState
{
public:
	void Update(double time);

	void HandleKeyboard(std::map<int, bool> keys);

	EnemyRocketStates GetState();

	void OnCollision();

	EnemyRocketAttack2State(EnemyRocketData * enemyRocketData);
	EnemyRocketAttack2State();
	~EnemyRocketAttack2State();
};

