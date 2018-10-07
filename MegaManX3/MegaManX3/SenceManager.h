#pragma once
#ifndef __SENCEMANAGER__H__
#define __SENCEMANAGER__H__

#include "GameSence.h"

class SenceManager
{
private:
	static SenceManager* instance;
	GameSence* currentSence;
public:
	static SenceManager* GetInstance();
	void Update(float time);
	GameSence* GetCurrentSence();
	void ReplaceSence(GameSence* sence);

	SenceManager();
	~SenceManager();
};
#endif // !__SENCEMANAGER__H__