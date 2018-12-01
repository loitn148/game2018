#pragma once
#ifndef __STANDINGATTACKSTATE__H__
#define __STANDINGATTACKSTATE__H__

#include "MegaManState.h"

class StandingAttackState : public MegaManState
{
public:
	StandingAttackState(MegaManData *megaManData, bool isStart = true);
	~StandingAttackState();

	void Update(double time);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual CharactersStates GetState();
};

#endif // !__STANDINGATTACKSTATE__H__