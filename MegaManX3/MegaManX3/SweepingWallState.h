#pragma once
#ifndef __SWEEPINGWALLSTATE__H__
#define __SWEEPINGWALLSTATE__H__

#include "MegaManState.h"

class SweepingWallState : public MegaManState
{
public:
	SweepingWallState(MegaManData *megaManData, bool isStart = true);
	~SweepingWallState();

	void Update(double time);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual CharactersStates GetState();
};

#endif // !__SWEEPINGWALLSTATE__H__