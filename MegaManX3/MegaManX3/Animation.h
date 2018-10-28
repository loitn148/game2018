#pragma once
#ifndef __ANIMATION__H__
#define __ANIMATION__H__

#include "GameSprite.h"
#include "GameGraphic.h"
#include "Global.h"
#include "Rect.h"
#include "vector"

class Animation
{
private:
	TEXTURE image;
	GameSprite* sprite;
	int width, height;
	int nFrame;
	double deltaTime;
	double totalTime;
	int index;
	Direct direct;
	std::vector<Rect> rectSprite;
public:
	int NextFrame(double time);
	void Draw(VT3 position, Direct direct, double, VT2 scale, VT2 translation);
	void Create(char* filePath, int nFrame, std::vector<Rect> rect, double timeFrame, Direct direct);
	int GetIndex();
	void SetIndex(int inx);
	int GetTotalFrame();

	Animation();
	~Animation();
};

#endif // !__ANIMATION__H__