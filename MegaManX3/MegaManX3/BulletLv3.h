#pragma once
#ifndef __BULLETLV3__H__
#define __BULLETLV3__H__

#include "GameObject.h"
#include "Animation.h"
#include "PlayerBullets.h"
#include "Camera.h"
#include "Global.h"

class BulletLv3 :
	public PlayerBullets
{
public:
	BulletLv3(D3DXVECTOR3 position, double vx, Direct direct);
	void Draw(double time);
	void Update(double time);
	bool isCollision;
	BulletLv3();
	~BulletLv3();
	Animation* animation;
};
#endif // !__BULLETLV3__H__