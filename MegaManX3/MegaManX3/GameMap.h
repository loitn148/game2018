#pragma once
#ifndef __GAME_MAP__
#define __GAME_MAP__

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#include "Sprite.h"
#include "GameSprite.h"
#include "MapReader/Tmx.h.in"
#include "Global.h"
#include "Quadtree.h"
#include "MegaManCharacters.h"
class EnemyOneGun;
class EnemyRocket;
class GameMap
{
protected:
	static GameMap* instance;
	void LoadMap(char *filePath);
	VT3 position;
	RECT mapRect;
	Tmx::Map *map;
	std::map<int, GameSprite*> listTileset;
	Quadtree* quadtree;
public:
	static GameMap* GetInstance();
    void Init(char* filePath);
	GameMap();

    Tmx::Map* GetMap();
	vector<EnemyOneGun*> vecOneGun;
	vector<EnemyRocket*> vecEnemyRocket;
    int GetWidth();
    int GetHeight();
    int GetTileWidth();
    int GetTileHeight();
	vector<GameObject*> vtStaticObject;
	vector<GameObject*> vtOneHitObject;
	vector<GameObject*> vtCauthangObject;
    void Draw();
	Quadtree* GetQuadtree();

    ~GameMap();
};

#endif

