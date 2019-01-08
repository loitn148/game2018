#pragma once
#pragma once
#ifndef __ENEMYROCKETTATE__H__
#define __ENEMYROCKETTATE__H__

#include "Global.h"
#include "GameObject.h"
#include "EnemyRocketData.h"
#include <map>
#include "Animation.h"
class EnemyRocketState
{
protected:
	EnemyRocketState();
	EnemyRocketState(EnemyRocketData* megaManData);
	EnemyRocketData* enemyRocketData;
public:
	virtual void Update(double time);
	virtual void HandleKeyboard(std::map<int, bool> keys);
	virtual void OnCollision();
	virtual EnemyRocketStates GetState() = 0;
	~EnemyRocketState();
};
#endif

