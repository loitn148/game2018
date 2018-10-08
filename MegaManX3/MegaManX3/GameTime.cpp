#include "GameTime.h"



GameTime::GameTime() {
}


GameTime::~GameTime() {
}

GameTime* GameTime::instance = NULL;

GameTime* GameTime::GetInstance()
{
	if (!GameTime::instance)
	{
		GameTime::instance = new GameTime();
	}
	return GameTime::instance;
}

bool GameTime::Init()
{
	LARGE_INTEGER i;

	if (!QueryPerformanceFrequency(&i))
	{
		return false;
	}
	this->frequency = (double)(i.QuadPart);
	this->currentTime = 0;
	this->totalTime = 0;

	QueryPerformanceCounter(&i);
	this->start = (double)(i.QuadPart);
}

void GameTime::Update()
{
	LARGE_INTEGER i;
	QueryPerformanceCounter(&i);
	this->currentTime = ((double)(i.QuadPart) - this->start) / this->frequency;
	this->totalTime += this->currentTime;
	this->start = (double)(i.QuadPart);
}

void GameTime::Run()
{
	this->Update();
}
