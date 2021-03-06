#pragma once
#ifndef __MEGAMANCHARACTERS__H__
#define __MEGAMANCHARACTERS__H__

#include "GameObject.h"
#include "GameTime.h"
#include "Animation.h"
#include "Camera.h"

#include "MegaManData.h"
#include "MegaManState.h"
#include "Start1State.h"
#include "Start2State.h"
#include "StandingState.h"
#include "RunningState.h"
#include "JumpingState.h"
#include "SweepingState.h"
#include "StandingAttackState.h"
#include "RunningAttackState.h"
#include "JumpingAttackState.h"
#include "SweepingAttackState.h"
#include "SweepingWallState.h"
#include "SweepingWallAttackState.h"
#include "JumpingFromWallState.h"
#include "JumpingFromWallAttackState.h"
#include "FallingState.h"
#include "FallingAttackState.h"
#include "HurtState.h"
#include "PlayerBullets.h"
#include "BulletLv1.h"
#include "BulletLv2.h"
#include "BulletLv3.h"
#include "StaticObject.h"
#include "Collision.h"
#include "GameMap.h"

#include <iostream>
#include <vector>
#include <map>

class SmokeEffect;
class HoldAttackEffect;
class MegaManHealth;
class DestroyedEffect;

class MegaManCharacters : public GameObject
{
protected:
	static MegaManCharacters* instance;
	HWND hWnd;
	HINSTANCE hInstance;
	Animation* listAnimation;
	MegaManData* megaManData;
	MegaManHealth* healthDraw;
	CharactersStates currentState;
	int positionBeforeJump;
	HoldAttackEffect* holdAttackEffect;
	DestroyedEffect* destroyedEffect;
	vector<PlayerBullets*> listBullet;
	vector<SmokeEffect*> listSmokeEff;
public:
	bool isUndying;
	double undyingDuration;
	static MegaManCharacters* GetInstance();
	void Init(HINSTANCE hInstance, HWND hWnd);
	void UpdatePosition(double time);
	void Draw(double time);
	void Update(double time);
	void SetState(MegaManState* state);
	void SetListAnimation();
	void AddSmokeEffect(VT3 smokePosition);
	void AddPosition(VT3 distance);
	void SubLife(int sub);
	void AddLife(int sub);
	//void AddPosition

	Animation* GetListAnimation();
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	void HandleKeyboard(std::map<int, bool> keys);
	bool isRightLeftKeyDown;
	bool isAttacking;
	bool isJumping;
	bool isFalling;
	bool isDestroying;
	double holdAttack;

	MegaManData* GetMegaManData();

	void CreateBullet(int level);

	MegaManCharacters();
	~MegaManCharacters();
};
#endif // !__MEGAMANCHARACTERS__H__



