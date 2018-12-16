#pragma once
#ifndef __BULLETLV1__H__
#define __BULLETLV1__H__

#include "GameObject.h"
#include "Animation.h"
#include "PlayerBullets.h"
#include "Camera.h"
#include "Global.h"

class BulletLv1 :
	public PlayerBullets
{
public:
	BulletLv1(D3DXVECTOR3 position, double vx);
	void Draw(double time);
	void Update(double time);
	bool isCollision;
	BulletLv1();
	~BulletLv1();
	Animation* animation;
};
#endif // !__BULLETLV1__H__