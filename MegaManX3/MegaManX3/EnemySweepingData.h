#pragma once
#ifndef __ENEMYSWEEPINGDATA__H__
#define __ENEMYSWEEPINGDATA__H__
class EnemySweeping;
class EnemySweepingState;
class EnemySweepingData
{
public:
	EnemySweeping* enemySweeping;
	EnemySweepingState* enemySweepingState;
	EnemySweepingData();
	~EnemySweepingData();
};
#endif

