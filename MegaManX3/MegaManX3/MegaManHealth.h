#pragma once
#ifndef __MEGAMANHEALTH__H__
#define __MEGAMANHEALTH__H__

#include "GameObject.h"
#include "Animation.h"
#include "Camera.h"

class MegaManHealth :
	public GameObject
{
public:
	static MegaManHealth* instance;
	static MegaManHealth* GetInstance();

	void SetHealth(int health);
	void SetAnimation();
	void Update(double time);
	void Draw(double time);
	Animation *animation;
	int currentHealth;
	MegaManHealth();
	~MegaManHealth();
};

#endif // !__MEGAMANHEALTH__H__



