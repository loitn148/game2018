#pragma once
#ifndef __CAMERA__H__
#define __CAMERA__H__

#include <DirectXMath.h>
#include "GameGraphic.h"


using namespace std;

class Camera
{
private:
	static Camera* instance;
	VT3 position;
	int width, height;
	double vx, vy;
public:

	void CameraOnWorld();
	void Update();
	void SetPosition(VT3 position);
	RECT GetRect();
	VT3 GetPosition();
	void Create(VT3 position, int width, int height);
	static Camera* GetInstance();
	Camera();
	~Camera();
};
#endif // !__CAMERA__H__