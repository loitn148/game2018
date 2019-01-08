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
#include "Sound.h"
#include <map>
#include "EnemyOneGun.h"
#include "EnemyRocket.h"
#include "EnemySweeping.h"

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
<<<<<<< HEAD
	Sound* sound;
=======
	EnemySweeping *Sweep;
>>>>>>> 2acb566015ca7ce560cd7424b67d18acb81471f6

public:
	void LoadContent();
	void Update(double time);
	void Draw(double time);
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	CollisionResult CheckCollision(GameObject* obj1, GameObject* obj2, double time);
	PlayScene(HWND hWnd, HINSTANCE hInstance);
	PlayScene();
	~PlayScene();
};
#endif // !__PLAYSCENE__H__