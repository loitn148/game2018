#pragma once
#ifndef __GAMEGRAPHIC__H__
#define __GAMEGRAPHIC__H__

#include <d3d9.h>
#include <d3dx9.h>
#include "Global.h"

class GameGraphic
{
private:
	D3D d3d;
	SPRITE sprite;
	SURFACE backBuffer;
	static GameGraphic* instance;
public:
	DEVICE device;
	bool Init(HWND hWnd, bool isWindowed);
	void Clear(DWORD color);
	void Begin();
	void End();
	void Present();
	TEXTURE LoadTexture(char* filePath, COLOR transcolor = C_XRGB(0, 0, 0));
	SURFACE LoadSurface(char* filePath, COLOR transcolor = C_XRGB(0, 0, 0));
	void DrawTexture(TEXTURE texture, RECT rect, VT3 center, VT3 position,
		VT2 scale, VT2 scalingCenter, VT2 translation = VT2(0, 0), COLOR transcolor = C_XRGB(255, 255, 255));
	void DrawSurface(SURFACE surface, RECT* sRect, RECT* dRect);
	SPRITE GetSprite();
	SURFACE GetBackBuffer();
	static GameGraphic* GetInstance();

	GameGraphic();
	~GameGraphic();
};
#endif // !__GAMEGRAPHIC__H__