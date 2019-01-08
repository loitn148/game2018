#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "PlayerBullets.h"
#include "SmokeEffect.h"
#include "Camera.h"
#include "Global.h"
class Blood: public PlayerBullets
{
protected:
	int Level;
public:
	Blood(D3DXVECTOR3 position);
	void Draw(double time);
	void Update(double time);
	bool isCollision;
	Animation* listAnimation;
	Animation* animation;
	Blood();
	~Blood();
};

