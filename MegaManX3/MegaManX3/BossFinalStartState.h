#pragma once
#ifndef __BOSSFINALSTARTSTATE__H__
#define __BOSSFINALSTARTSTATE__H__

#include "BossFinalState.h"
class BossFinalStartState : public BossFinalState
{
public:
	BossFinalStartState(BossFinalData *bossFinalData);
	~BossFinalStartState();

	void Update(double time);

	virtual BigBossStates GetState();
};

#endif // !__BOSSFINALSTARTSTATE__H__


