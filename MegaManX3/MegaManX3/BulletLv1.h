#pragma once
#ifndef __BULLETLV1__H__
#define __BULLETLV1__H__

#include "GameObject.h"
#include "Animation.h"
#include "Camera.h"
#include "Global.h"

class BulletLv1 :
	public GameObject
{
public:
	void Draw(float time);
	void Update(float time);
	BulletLv1(D3DXVECTOR3 position, float vx, float vy);
	bool isDead;
	BulletLv1();
	~BulletLv1();
	Animation* bulletLv1;
};
#endif // !__BULLETLV1__H__