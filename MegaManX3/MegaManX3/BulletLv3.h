#pragma once
#ifndef __BULLETLV1__H__
#define __BULLETLV1__H__

#include "GameObject.h"
#include "Animation.h"
#include "Camera.h"
#include "Global.h"

class BulletLv3 :
	public GameObject
{
public:
	void Draw(float time);
	void Update(float time);
	BulletLv3(D3DXVECTOR3 position, float vx, float vy);
	bool isDead;
	BulletLv3();
	~BulletLv3();
	Animation* bulletLv3;
};
#endif // !__BULLETLV1__H__