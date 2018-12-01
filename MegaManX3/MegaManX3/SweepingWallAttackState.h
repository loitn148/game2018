#pragma once
#ifndef __SWEEPINGWALLATTACKSTATE__H__
#define __SWEEPINGWALLATTACKSTATE__H__

#include "MegaManState.h"

class SweepingWallAttackState : public MegaManState
{
public:
	SweepingWallAttackState(MegaManData *megaManData, bool isStart = true);
	~SweepingWallAttackState();

	void Update(double time);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual CharactersStates GetState();
};

#endif // !__SWEEPINGWALLATTACKSTATE__H__