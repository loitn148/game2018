#pragma once
#ifndef __BOSSFINALHEALTH__H__
#define __BOSSFINALHEALTH__H__
#include "GameObject.h"
#include "Animation.h"
#include "Camera.h"

class BossFinalHealth :
	public GameObject
{
public:
	static BossFinalHealth* instance;
	static BossFinalHealth* GetInstance();

	void SetHealth(int health);
	void SetAnimation();
	void Update(double time);
	void Draw(double time);
	Animation *animation;
	int currentHealth;
	BossFinalHealth();
	~BossFinalHealth();
};

#endif // !__BOSSFINALHEALTH__H__