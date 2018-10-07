#pragma once
#ifndef __GAMESPRITE__H__
#define __GAMESPRITE__H__

#include <d3d9.h>
#include "GameGraphic.h"
class GameSprite
{
private:
	static GameSprite* instance;
	SPRITE sprite;
	MATRIX matrix;
public:
	bool Init(DEVICE);
	void Begin();
	void End();
	void Draw(TEXTURE texture, RECT* rect, VT3 center, VT3 position,
		VT2 scale, VT2 scalingCenter, VT2 translation = VT2(0, 0));
	void ResetTranform();
	void FlipX(int width, int height, VT3 position);
	void FlipY(int width, int height, VT3 position);
	SPRITE GetSrpite();

	static GameSprite* GetInstance();
	GameSprite();
	~GameSprite();
};
#endif // !__GAMESPRITE__H__