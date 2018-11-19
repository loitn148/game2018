#pragma once
#ifndef __START2STATE__H__
#define __START2STATE__H__

#include "MegaManState.h"
class Start2State :
	public MegaManState
{
public:
	Start2State(MegaManData *megaManData);
	~Start2State();

	void Update(double time);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual CharactersStates GetState();
};

#endif // !__START1STATE__H__