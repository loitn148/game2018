#pragma once
#ifndef __BOSSFINAL__H__
#define __BOSSFINAL__H__

#include "GameObject.h"
#include "Animation.h"
#include "Camera.h"
#include "Global.h"
#include "Wings.h"
#include "BossFinalData.h"
#include "BossFinalState.h"
#include "MegaManCharacters.h"
#include "Enemy.h"

class BossFinalHealth;

class BossFinal : public GameObject
{
public:
	BossFinal(D3DXVECTOR3 position, float vx, float vy);
	BossFinalData * bossFinalData;
	BossFinalState *bossFinalState;
	MegaManCharacters *megaMan;
	BossFinalHealth* healthDraw;
	bool isDead;
	bool isIntro;
	bool isCallEnemies;
	bool isPrick;
	bool isJustPrick;
	BossFinal();
	~BossFinal();
	Wings *wings;
	vector<Enemy*> enemies;
	Enemy* enemy1;
	Enemy* enemy2;
	Enemy* enemy3;
	BigBossStates currentState;
	Animation* listAnimation;
	void UpdatePosition(double time);
	void Draw(double time);
	void Update(double time);
	void SetState(BossFinalState* state);
	void SetListAnimation();
	void CallEnemy();
	void SubLife(int sub);
	//void AddPosition

	Animation* GetListAnimation();
};

#endif // !__BOSSFINAL__H__