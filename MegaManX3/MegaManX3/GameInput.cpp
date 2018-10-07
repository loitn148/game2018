#include "GameInput.h"


GameInput::GameInput()
{
	this->input = NULL;
	this->inputDev = NULL;
}


GameInput::~GameInput()
{
}

void GameInput::InitKeyBoard(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;
	hr = DirectInput8Create(
		hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(VOID**)&this->input,
		NULL);

	if (hr != DI_OK) return;

	hr = this->input->CreateDevice(GUID_SysKeyboard, &this->inputDev, NULL);
	if (hr != DI_OK) return;

	hr = this->inputDev->SetDataFormat(&c_dfDIKeyboard);
	if (hr != DI_OK) return;

	hr = this->inputDev->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (hr != DI_OK) return;

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	hr = this->inputDev->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (hr != DI_OK) return;

	hr = this->inputDev->Acquire();
	if (hr != DI_OK) return;
}

void GameInput::ProcessKeyBoard(HWND _hWnd)
{

	// Collect all key states first
	this->inputDev->GetDeviceState(sizeof(keyStates), keyStates);


	if (isKeyDown(DIK_ESCAPE))
	{
		PostMessage(_hWnd, WM_QUIT, 0, 0);
	}

	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	HRESULT hr = this->inputDev->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);

	// Scan through all data, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = keyEvents[i].dwOfs;
		int KeyState = keyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
			OnKeyDown(KeyCode);
		else
			OnKeyUp(KeyCode);
	}
}

int GameInput::isKeyDown(int KeyCode)
{
	return (keyStates[KeyCode] & 0x80) > 0;
}

void GameInput::OnKeyUp(int KeyCode) {  }

void GameInput::OnKeyDown(int KeyCode) { }

void GameInput::CleanUp()
{

	if (this->inputDev != NULL)
	{
		this->inputDev->Release();
	}

	if (this->input != NULL)
	{
		this->input->Release();
	}

	if (this->inputDev)
	{
		this->inputDev->Unacquire();
		this->inputDev->Release();
	}
}
