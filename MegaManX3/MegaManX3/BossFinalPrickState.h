#pragma once
#ifndef __BOSSFINALPRICKSTATE__H__
#define __BOSSFINALPRICKSTATE__H__

#include "BossFinalState.h"

class BossFinalPrickState : public BossFinalState
{
public:
	BossFinalPrickState(BossFinalData *bossFinalData);
	~BossFinalPrickState();
	VT3 positionMegan;
	float angleAttack;
	void Update(double time);
	virtual BigBossStates GetState();
};

#endif // !__BOSSFINALPRICKSTATE__H__


