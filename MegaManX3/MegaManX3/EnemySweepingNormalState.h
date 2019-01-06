#pragma once
#include "EnemySweepingState.h"
class EnemySweepingNormalState :
	public EnemySweepingState
{
public:
	int MoveTimes;
	bool Term;
	void Update(double time);

	void HandleKeyboard(std::map<int, bool> keys);

	EnemySweepingStates GetState();

	void OnCollision();

	EnemySweepingNormalState(EnemySweepingData * enemyRocketData);
	EnemySweepingNormalState();
	~EnemySweepingNormalState();
};

