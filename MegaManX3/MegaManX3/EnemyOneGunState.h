#pragma once
#ifndef __ENEMYONEGUNSTATE__H__
#define __ENEMYONEGUNSTATE__H__

#include "Global.h"
#include "GameObject.h"
#include "EnemyOneGunData.h"
//#include "EnemyOneGun.h"
#include <map>
#include "Animation.h"


class EnemyOneGunState
{
protected:
	EnemyOneGunState();
	EnemyOneGunState(EnemyOneGunData* megaManData);
	EnemyOneGunData* enemyOneGunData;
public:
	virtual void Update(double time);
	virtual void HandleKeyboard(std::map<int, bool> keys);
	virtual void OnCollision();
	virtual OneGunStates GetState() = 0;
	~EnemyOneGunState();
};
#endif
