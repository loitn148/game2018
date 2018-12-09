#pragma once
#ifndef __BULLETLV2__H__
#define __BULLETLV2__H__

#include "GameObject.h"
#include "Animation.h"
#include "Camera.h"
#include "Global.h"

class BulletLv2 :
	public GameObject
{
public:
	void Draw(float time);
	void Update(float time);
	BulletLv2(D3DXVECTOR3 position, float vx, float vy);
	bool isDead;
	BulletLv2();
	~BulletLv2();
	Animation* bulletLv2;
};
#endif // !__BULLETLV2__H__