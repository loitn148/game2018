#pragma once
#ifndef __STANDINGSTATE__H__
#define __STANDINGSTATE__H__

#include "MegaManState.h"

class StandingState : public MegaManState
{
public:
	StandingState(MegaManData *megaManData, bool isStart = true);
	~StandingState();

	void Update(double time);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual CharactersStates GetState();
};
#endif // !__STANDINGSTATE__H__