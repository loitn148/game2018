#pragma once
#ifndef __GAMEINPUT__H__
#define __GAMEINPUT__H__

//KEYBOARD
#define KEY_DOWN(code) ( IsKeyDown(code) )
#define KEYBOARD_BUFFER_SIZE 1024

#define DIRECTINPUT_HEADER_VERSION  0x0800
#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION DIRECTINPUT_HEADER_VERSION
#pragma message(__FILE__ ": DIRECTINPUT_VERSION undefined. Defaulting to version 0x0800")
#endif

#include <dinput.h>
#include "Global.h"
class GameInput
{
protected:
	BYTE keyStates[256];
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];
	INPUT input;
	INPUTDEV inputDev;
	int isKeyDown(int keyCode);
public:
	virtual void OnKeyDown(int keyCode);
	virtual void OnKeyUp(int keyCode);
	void ProcessKeyBoard(HWND hWnd);
	void InitKeyBoard(HINSTANCE hInstance, HWND hWnd);
	void CleanUp();

	GameInput();
	~GameInput();
};
#endif // !__GAMEINPUT__H__



