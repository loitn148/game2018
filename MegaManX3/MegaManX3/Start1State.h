#pragma once
#ifndef __START1STATE__H__
#define __START1STATE__H__

#include "MegaManState.h"
#include "Global.h"
class Start1State :
	public MegaManState
{
public:
	Start1State(MegaManData *megaManData);
	~Start1State();

	void Update(double time);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual CharactersStates GetState();
};

#endif // !__START1STATE__H__