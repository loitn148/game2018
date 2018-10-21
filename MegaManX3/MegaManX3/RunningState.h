#pragma once
#ifndef __RUNNINGSTATE__H__
#define __RUNNINGSTATE__H__

#include "MegaManState.h"

class RunningState : public MegaManState
{
public:
	RunningState(MegaManData *megaManData);
	~RunningState();

	void Update(double time);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual CharactersStates GetState();
};

#endif // !__RUNNINGSTATE__H__