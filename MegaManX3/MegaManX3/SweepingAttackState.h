#pragma once
#ifndef __SWEEPINGATTACKSTATE__H__
#define __SWEEPINGATTACKSTATE__H__

#include "MegaManState.h"

class SweepingAttackState : public MegaManState
{
public:
	SweepingAttackState(MegaManData *megaManData, bool isStart = true);
	~SweepingAttackState();

	double duration;
	void Update(double time);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual CharactersStates GetState();
};

#endif // !__SWEEPINGATTACKSTATE__H__