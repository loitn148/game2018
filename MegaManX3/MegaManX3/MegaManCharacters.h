#pragma once
#ifndef __MEGAMANCHARACTERS__H__
#define __MEGAMANCHARACTERS__H__

#include "GameObject.h"
#include "GameTime.h"
#include "Animation.h"
#include "Camera.h"

#include "MegaManData.h"
#include "MegaManState.h"
#include "StandingState.h"
#include "RunningState.h"

#include <iostream>
#include <vector>
#include <map>

class MegaManCharacters : public GameObject
{
protected:
	static MegaManCharacters* instance;
	HWND hWnd;
	HINSTANCE hInstance;
	Animation* listAnimation;
	MegaManData* megaManData;
	CharactersStates currentState;
public:
	static MegaManCharacters* GetInstance();

	void Init(HINSTANCE hInstance, HWND hWnd);
	void UpdatePosition(double time);
	void Draw(double time);
	void Update(double time);
	void SetState(MegaManState* state);
	void SetListAnimation();

	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	void HandleKeyboard(std::map<int, bool> keys);
	MegaManCharacters();
	~MegaManCharacters();
};
#endif // !__MEGAMANCHARACTERS__H__



