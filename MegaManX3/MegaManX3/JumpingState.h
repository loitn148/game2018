#pragma once
#ifndef __JUMPINGSTATE__H__
#define __JUMPINGSTATE__H__

#include "MegaManState.h"

class JumpingState : public MegaManState
{
public:
	JumpingState(MegaManData *megaManData);
	~JumpingState();

	void Update(double time);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual CharactersStates GetState();
};

#endif // !__JUMPINGSTATE__H__