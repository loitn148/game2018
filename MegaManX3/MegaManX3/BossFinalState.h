#pragma once
#ifndef __BOSSFINALSTATE__H__
#define __BOSSFINALSTATE__H__

#include "Global.h"
#include "GameObject.h"
#include "BossFinalData.h"
#include <map>
#include "Animation.h"

class BossFinalState
{
protected:
	BossFinalState();
	BossFinalState(BossFinalData* bossFinalData);
	BossFinalData* bossFinalData;
public:
	virtual void Update(double time);
	virtual BigBossStates GetState() = 0;
	Animation* listAnimation;
	~BossFinalState();
};

#endif // !__BOSSFINALSTATE__H__

