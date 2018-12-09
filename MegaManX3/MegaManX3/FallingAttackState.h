#pragma once
#ifndef __FALLINGATTACKSTATE__H__
#define __FALLINGATTACKSTATE__H__

#include "MegaManState.h"

class FallingAttackState : public MegaManState
{
public:
	FallingAttackState(MegaManData *megaManData, bool isStart = true);
	~FallingAttackState();

	void Update(double time);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual CharactersStates GetState();
};

#endif // !__FALLINGATTACKSTATE__H__