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
	int width, height;
	int nFrame;
	float deltaTime;
	float totalTime;
	int index;
	Direct direct;
	std::vector<Rect> rectSprite;
public:
	int NextFrame(float time);
	void Draw(VT3 position, Direct direct, float, VT2 scale, VT2 translation);
	void Create(char* fileName, int nFrame, std::vector<Rect> rect, float timeFrame, Direct direct);
	int GetIndex();
	void SetIndex(int inx);
	int GetTotalFrame();

	Animation();
	~Animation();
};

#endif // !__ANIMATION__H__