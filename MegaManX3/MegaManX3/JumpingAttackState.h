#pragma once
#ifndef __JUMPINGATTACKSTATE__H__
#define __JUMPINGATTACKSTATE__H__

#include "MegaManState.h"

class JumpingAttackState : public MegaManState
{
public:
	JumpingAttackState(MegaManData *megaManData, bool isStart = true);
	~JumpingAttackState();

	void Update(double time);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual CharactersStates GetState();
};

#endif // !__JUMPINGATTACKSTATE__H__