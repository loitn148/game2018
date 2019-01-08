#pragma once
#include "EnemyOneGunState.h"


#define JUMPRANGE 600

class EnemyOneGunAttack1State : public EnemyOneGunState
{
	int NumberBullet;
public:
	void Update(double time);

	void HandleKeyboard(std::map<int, bool> keys);

	OneGunStates GetState();

	void OnCollision();

	EnemyOneGunAttack1State(EnemyOneGunData * enemyOneGunData);
	EnemyOneGunAttack1State();
	~EnemyOneGunAttack1State();
};

