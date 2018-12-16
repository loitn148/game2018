#pragma once
#ifndef __BULLETLV2__H__
#define __BULLETLV2__H__

#include "GameObject.h"
#include "Animation.h"
#include "PlayerBullets.h"
#include "Camera.h"
#include "Global.h"

class BulletLv2 :
	public PlayerBullets
{
public:
	BulletLv2(D3DXVECTOR3 position, double vx);
	void Draw(double time);
	void Update(double time);
	bool isCollision;
	BulletLv2();
	~BulletLv2();
	Animation* animation;
};
#endif // !__BULLETLV2__H__