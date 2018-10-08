#pragma once
#ifndef __GAMESENCE__H__
#define __GAMESENCE__H__

class GameSence
{
public:
	virtual void LoadContent() = 0;
	virtual void Update(double time) = 0;
	virtual void Draw(double time) = 0;
};

#endif //__GAMESENCE__H__