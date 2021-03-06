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
#include "Elevator1.h"
#include <map>
#include "EnemyOneGun.h"
#include "EnemyRocket.h"
#include "EnemySweeping.h"
#include "Sound.h"
#include "BossFinal.h"

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
	Elevator1 *elevator1;
	BossNormal *bossNormal;
	EnemySweeping *Sweep;
	TEXTURE gameOverImages;
	Sound* sound;
	BossFinal* bossfinal;
public:
	void LoadContent();
	void Update(double time);
	void Draw(double time);
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	void InitGameOverImage();
	void DrawOnGameOver();
	CollisionResult CheckCollision(GameObject* obj1, GameObject* obj2, double time);
	PlayScene(HWND hWnd, HINSTANCE hInstance);
	PlayScene();
	~PlayScene();
};
#endif // !__PLAYSCENE__H__