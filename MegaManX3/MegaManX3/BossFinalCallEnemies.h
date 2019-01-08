#pragma once
#ifndef __BOSSFINALCALLENEMIESSTATE__H__
#define __BOSSFINALCALLENEMIESSTATE__H__

#include "BossFinalState.h"

class BossFinalCallEnemies : public BossFinalState
{
public:
	BossFinalCallEnemies(BossFinalData *bossFinalData);
	~BossFinalCallEnemies();

	VT3 positionMegan;
	void Update(double time);

	virtual BigBossStates GetState();
};

#endif // !__BOSSFINALCALLENEMIESSTATE__H__
