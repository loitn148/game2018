#pragma once
#ifndef __CAMERA__H__
#define __CAMERA__H__

#include <DirectXMath.h>
#include "GameGraphic.h"
#include "MegaManCharacters.h"
#include "MegaManHealth.h"

class MegaManCharacters;


using namespace std;

class Camera
{
private:
	static Camera* instance;
	VT3 position;
	int width, height;
	double vx, vy;
	bool allowMoveX;
	bool allowMoveY;
	int state;
public:
	void CameraOnWorld();
	void Update(MegaManCharacters* megaMan);
	void SetPosition(VT3 position);
	RECT GetRect();
	VT3 GetPosition();
	void Create(VT3 position, int width, int height);
	static Camera* GetInstance();
	void allowMove(bool moveX, bool moveY);
	Camera();
	~Camera();
};
#endif // !__CAMERA__H__