#pragma once
#ifndef __PLAYSENCE__H__
#define __PLAYSENCE__H__

#include "GameSence.h"
#include "Ball.h"
#include "GameTime.h"
#include "Camera.h"
#include "Map.h"

class PlaySence : public GameSence
{
private:
	HWND hWnd;
	HINSTANCE hInstance;

	Camera* camera;
	Map* map;
	Ball* ball;
public:
	void LoadContent();
	void Update(float time);
	void Draw(float time);
	PlaySence(HWND hWnd, HINSTANCE hInstance);
	PlaySence();
	~PlaySence();
};
#endif // !__PLAYSENCE__H__