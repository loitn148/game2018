#pragma once

#ifndef __GAME__H__
#define __GAME__H__

#include "Ball.h"
#include "PlaySence.h"
#include "SenceManager.h"

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