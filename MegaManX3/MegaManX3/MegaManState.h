#pragma once
#ifndef __MEGAMANSTATE__H__
#define __MEGAMANSTATE__H__

#include "Global.h"
#include "GameObject.h"
#include "MegaManData.h"
#include <map>
#include "Animation.h"

class MegaManState
{
protected:
	MegaManState();
	MegaManState(MegaManData* megaManData);
	MegaManData* megaManData;
public:
	virtual void Update(double time);
	virtual void HandleKeyboard(std::map<int, bool> keys);
	virtual CharactersStates GetState() = 0;
	Animation* listAnimation;
	~MegaManState();
};
#endif // !__MEGAMANSTATE__H__