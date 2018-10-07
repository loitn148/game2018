#pragma once
#ifndef __GAMETIME__H__
#define __GAMETIME__H__

#include <Windows.h>

class GameTime
{
private:
	static GameTime* instance;
	float start;
	float frequency;
	void Update();
public:
	float currentTime;
	float totalTime;
	bool Init();
	void Run();

	static GameTime* GetInstance();
	GameTime();
	~GameTime();
};
#endif // !__GAMETIME__H__