#pragma once
#ifndef __HURTSTATE__H__
#define __HURTSTATE__H__

#include "MegaManState.h"

class HurtState : public MegaManState
{
public:
	HurtState(MegaManData *megaManData, CharactersStates previousState);
	~HurtState();

	double duration;
	CharactersStates previousState;

	void Update(double time);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual CharactersStates GetState();
};

#endif // !__HURTSTATE__H__