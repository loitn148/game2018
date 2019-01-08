#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "PlayerBullets.h"
#include "Camera.h"
#include "Global.h"
class OneGunBullet :
	public PlayerBullets
{
private:
	VT3 OldPosion;
	void UpdatePosition(double time);
public:
	OneGunBullet(D3DXVECTOR3 position, double vy, double ay, double vx, Direct direct);
	void Draw(double time);
	void Update(double time);
	bool isCollision;
	Animation* animation;
	OneGunBullet();
	~OneGunBullet();
};

