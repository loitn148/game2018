#pragma once
#ifndef __DESTROYEDEFFECT__H__
#define __DESTROYEDEFFECT__H__

#include "GameObject.h"
#include "Camera.h"
#include "Animation.h"

class DestroyedEffect :
	public GameObject
{
public:
	DestroyedEffect(VT3 position);
	void Draw(double time);
	void Update(double time);
	DestroyedEffect();
	~DestroyedEffect();
	Animation* animation;
};
#endif // !__DESTROYEDEFFECT__H__