#pragma once
#ifndef __WINGS__H__
#define __WINGS__H__

#include "GameObject.h"
#include "Animation.h"
#include "Camera.h"
#include "Global.h"

class Wings : public GameObject
{
public:
	void Draw(float time, BigBossStates currentState);
	void Update(VT3 bossPosition, BigBossStates currentState);
	Wings(D3DXVECTOR3 position, float vx, float vy);
	bool isDead;
	Animation* wings;
	Wings();
	~Wings();
};

#endif // !__WINGS__H__

