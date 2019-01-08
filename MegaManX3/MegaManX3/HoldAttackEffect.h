#pragma once
#ifndef __HOLDATTACKEFFECT__H__
#define __HOLDATTACKEFFECT__H__

#include "GameObject.h"
#include "Animation.h"
#include "Global.h"
#include "Camera.h"
#include "Viewport.h"

class HoldAttackEffect :
	public GameObject
{
public:
	HoldAttackEffect(VT3 position, int bulletType);
	void Draw(double time);
	void Update(double time);
	int bulletType;
	void ChangeAnimation(int bulletType);
	HoldAttackEffect();
	~HoldAttackEffect();
	Animation* listAnimation;
};
#endif // !__HOLDATTACKEFFECT__H__