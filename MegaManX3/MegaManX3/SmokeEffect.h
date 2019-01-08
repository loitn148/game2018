#pragma once
#ifndef __SMOKEEFFECT__H__
#define __SMOKEEFFECT__H__

#include "GameObject.h"
#include "Animation.h"
#include "Global.h"
#include "Camera.h"
#include "Viewport.h"

class SmokeEffect :
	public GameObject
{
public:
	SmokeEffect(VT3 position);
	void Draw(double time);
	void Update(double time);
	SmokeEffect();
	~SmokeEffect();
	Animation* animation;
};
#endif // !__SMOKEEFFECT__H__