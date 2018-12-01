#pragma once
#ifndef __JUMPINGFROMWALLATTACKSTATE__H__
#define __JUMPINGFROMWALLATTACKSTATE__H__

#include "MegaManState.h"

class JumpingFromWallAttackState : public MegaManState
{
public:
	JumpingFromWallAttackState(MegaManData *megaManData, bool isStart = true);
	~JumpingFromWallAttackState();

	void Update(double time);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual CharactersStates GetState();
};

#endif // !__JUMPINGFROMWALLATTACKSTATE__H__