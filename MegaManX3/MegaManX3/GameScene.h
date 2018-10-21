#pragma once
#ifndef __GAMESCENE__H__
#define __GAMESCENE__H__

class GameScene
{
public:
	virtual void LoadContent() = 0;
	virtual void Update(double time) = 0;
	virtual void Draw(double time) = 0;
	virtual void OnKeyDown(int keyCode) = 0;
	virtual void OnKeyUp(int keyCode) = 0;
};

#endif //__GAMESCENE__H__