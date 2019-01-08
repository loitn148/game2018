#pragma once
#ifndef __ENEMY__H__
#define __ENEMY__H__

#include "GameObject.h"
#include "Animation.h"
#include "Camera.h"
#include "Global.h"

class Enemy : public GameObject
{
public:
	void Draw(float time);
	void Update(float time, MegaManCharacters *megaman);
	Enemy(D3DXVECTOR3 position, float vx, float vy, Direct direct);
	bool isDead;
	void SetStatus(bool isDead) { this->isDead = isDead; }
	void Attack(MegaManCharacters *megaMan);
	Enemy();
	~Enemy();
	Animation* enemy;
};

#endif // !__ENEMY__H__
