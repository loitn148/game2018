#pragma once
#ifndef __BOSSNORMAL__H__
#define __BOSSNORMAL__H__

#include "GameObject.h"
#include "Animation.h"
#include "Camera.h"
#include "Global.h"

class BossNormal :
	public GameObject
{
public:
	void Draw(double time);
	void Update(double time);
	BossNormal(D3DXVECTOR3 position, double vx, double vy);
	bool isDead;
	double angle;
	VT2 rotateCenter;
	BossNormal();
	~BossNormal();
	Animation* animation;
};
#endif // !__BOSSNORMAL__H__#pragma once
