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
	bool isAttack1, isAttack2, isAttack3, isIntro;
	int countAttack1, countAttack2, countAttack3;
	void Draw(double time);
	void Update(double time);
	void UpdatePosition(double time);
	BossNormal(D3DXVECTOR3 position, double vx, double vy);
	bool isDead;
	double angle;
	VT2 rotateCenter;
	BossNormal();
	~BossNormal();
	Animation* animation;
	void SubLife(int sub);
};
#endif // !__BOSSNORMAL__H__#pragma once
