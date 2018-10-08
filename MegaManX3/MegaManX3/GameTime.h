#pragma once
#ifndef __GAMETIME__H__
#define __GAMETIME__H__

#include <Windows.h>

class GameTime
{
private:
	static GameTime* instance;
	double start;
	double frequency;
	void Update();
public:
	double currentTime;
	double totalTime;
	bool Init();
	void Run();

	static GameTime* GetInstance();
	GameTime();
	~GameTime();
};
#endif // !__GAMETIME__H__