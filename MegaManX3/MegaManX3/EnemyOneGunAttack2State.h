#pragma once
#include "EnemyOneGunState.h"

#define JUMPRANGE 600

class EnemyOneGunAttack2State : public EnemyOneGunState
{
	int NumberBullet;
public:
	void Update(double time);

	void HandleKeyboard(std::map<int, bool> keys);

	OneGunStates GetState();

	void OnCollision();

	EnemyOneGunAttack2State(EnemyOneGunData * enemyOneGunData);
	EnemyOneGunAttack2State();
	~EnemyOneGunAttack2State();
};

