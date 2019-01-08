#pragma once
#ifndef __ENEMYSWEEPINGSTATE__H__
#define __ENEMYSWEEPINGSTATE__H__

#include "Global.h"
#include "GameObject.h"
#include "EnemySweepingData.h"
#include <map>
#include "Animation.h"
class EnemySweepingState
{
protected:
	EnemySweepingState();
	EnemySweepingState(EnemySweepingData* megaManData);
	EnemySweepingData* enemySweepingData;
public:
	virtual void Update(double time);
	virtual void HandleKeyboard(std::map<int, bool> keys);
	virtual void OnCollision();
	virtual EnemySweepingStates GetState() = 0;
	~EnemySweepingState();
};
#endif

