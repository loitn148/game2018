#pragma once
#ifndef __FALLINGSTATE__H__
#define __FALLINGSTATE__H__

#include "MegaManState.h"

class FallingState : public MegaManState
{
public:
	FallingState(MegaManData *megaManData, bool isStart = true);
	~FallingState();

	void Update(double time);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual CharactersStates GetState();
};

#endif // !__FALLINGSTATE__H__