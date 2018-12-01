#pragma once
#ifndef __SWEEPINGSTATE__H__
#define __SWEEPINGSTATE__H__

#include "MegaManState.h"

class SweepingState : public MegaManState
{
public:
	SweepingState(MegaManData *megaManData, bool isStart = true);
	~SweepingState();

	void Update(double time);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual CharactersStates GetState();
};

#endif // !__SWEEPINGSTATE__H__