#pragma once
#ifndef __PLAYSCENE__H__
#define __PLAYSCENE__H__

#include "GameScene.h"
#include "GameTime.h"
#include "Camera.h"
#include "Map.h"
#include "MegaManCharacters.h"
#include "GameMap.h"
#include "BossNormal.h"
#include <map>

class PlayScene : public GameScene
{
private:
	HWND hWnd;
	HINSTANCE hInstance;

	Camera* camera;
	Map* map;
	MegaManCharacters *megaMan;
	std::map<int, bool> keys;
	GameMap *mMap;
	BossNormal *bossNormal;

public:
	void LoadContent();
	void Update(double time);
	void Draw(double time);
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	PlayScene(HWND hWnd, HINSTANCE hInstance);
	PlayScene();
	~PlayScene();
};
#endif // !__PLAYSCENE__H__