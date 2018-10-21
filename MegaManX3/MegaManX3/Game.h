#pragma once

#ifndef __GAME__H__
#define __GAME__H__

#include "GameSprite.h"
#include "PlayScene.h"
#include "SceneManager.h"

class Game
{
private:
	HINSTANCE hInstance;
	HWND hWnd;
	double timeLoop;
public:
	bool Init(HWND hWnd, HINSTANCE hInstance);
	void Run();
	void LoadContent();

	Game();
	~Game();
};
#endif // !__GAME__H__