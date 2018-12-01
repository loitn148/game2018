#pragma once
#ifndef __RUNNINGATTACKSTATE__H__
#define __RUNNINGATTACKSTATE__H__

#include "MegaManState.h"

class RunningAttackState : public MegaManState
{
public:
	RunningAttackState(MegaManData *megaManData, bool isStart = true);
	~RunningAttackState();

	void Update(double time);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual CharactersStates GetState();
};

#endif // !__RUNNINGATTACKSTATE__H__