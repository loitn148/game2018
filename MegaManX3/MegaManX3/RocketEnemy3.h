#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "PlayerBullets.h"
#include "Camera.h"
#include "Global.h"
class RocketEnemy3: public PlayerBullets
{
public:
	RocketEnemy3(D3DXVECTOR3 position, double vx, Direct direct);
	void Draw(double time);
	void Update(double time);
	bool isCollision;
	Animation* animation;
	RocketEnemy3();
	~RocketEnemy3();
};

