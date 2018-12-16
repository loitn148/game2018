#pragma once
#ifndef __PLAYERBULLETS__H__
#define __PLAYERBULLETS__H__

#include "GameObject.h"
#include "Animation.h"

class PlayerBullets :
	public GameObject
{
public:
	bool isCollision;

	virtual void Update(double time) = 0;
	virtual void Draw(double time) = 0;

	PlayerBullets();
	~PlayerBullets();
};

#endif // !__PLAYERBULLETS__H__