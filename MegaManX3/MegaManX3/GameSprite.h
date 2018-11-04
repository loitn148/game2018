#pragma once
#ifndef __GAMESPRITE__H__
#define __GAMESPRITE__H__

#include <d3d9.h>
#include <d3dx9.h>
#include "GameGraphic.h"
#include "Global.h"
#include "Rect.h"

class GameSprite
{
protected:
	static GameSprite* instance;
	MATRIX matrix;
	SPRITE sprite;
	TEXTURE texture;

	VT3 position;
	float width, height;
	RECT rect;

	void InitWithSprite(const char* filePath, COLOR transcolor = NULL);
	bool isRect(RECT rect);
public:
	bool Init(DEVICE);
	void Begin();
	void End();
	void Draw(VT3 position = VT3(0, 0, 0), VT2 translation = VT2(), VT3 center = VT3(), RECT rect = RECT(), VT2 scale = VT2(1, 1),
		float angle = 0, VT2 rotationCenter = VT2(), COLOR transcolor = C_XRGB(255, 255, 255));

	void ResetTranform();
	void FlipX(int width, int height, VT3 position);
	void FlipY(int width, int height, VT3 position);
	SPRITE GetSrpite();
	TEXTURE GetTexture();
	VT3 GetPosition();

	static GameSprite* GetInstance();

	GameSprite(const char* filePath, COLOR transcolor = NULL);
	GameSprite();
	~GameSprite();
};
#endif // !__GAMESPRITE__H__