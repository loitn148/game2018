#pragma once
#ifndef __JUMPINGFROMWALLSTATE__H__
#define __JUMPINGFROMWALLSTATE__H__

#include "MegaManState.h"

class JumpingFromWallState : public MegaManState
{
public:
	JumpingFromWallState(MegaManData *megaManData, bool isStart = true);
	~JumpingFromWallState();

	void Update(double time);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual CharactersStates GetState();
};

#endif // !__JUMPINGFROMWALLSTATE__H__