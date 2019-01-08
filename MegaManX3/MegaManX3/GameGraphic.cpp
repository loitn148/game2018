#include "GameGraphic.h"



GameGraphic::GameGraphic() {
}


GameGraphic::~GameGraphic() {
}

GameGraphic* GameGraphic::instance = NULL;
GameGraphic* GameGraphic::GetInstance() {
	if (!GameGraphic::instance) {
		GameGraphic::instance = new GameGraphic();
	}
	return GameGraphic::instance;
}

SURFACE GameGraphic::GetBackBuffer() {
	return this->backBuffer;
}

SPRITE GameGraphic::GetSprite() {
	return this->sprite;
}

TEXTURE GameGraphic::LoadTexture(char* filePath, COLOR transcolor) {
	TEXTURE texture;
	D3DXIMAGE_INFO info;
	HRESULT hResult;

	hResult = D3DXGetImageInfoFromFile(filePath, &info);

	hResult = D3DXCreateTextureFromFileEx(
		this->device,
		filePath,
		info.Width,
		info.Height,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		&info,
		NULL,
		&texture);
	if (hResult != D3D_OK) {
		MessageBox(NULL, "Create Texture Error!", "Error", MB_OK);
		return false;
	}
	return texture;
}

SURFACE GameGraphic::LoadSurface(char * filePath, COLOR transcolor) {
	SURFACE surface;
	D3DXIMAGE_INFO info;
	if (D3DXGetImageInfoFromFile(filePath, &info))
		return NULL;

	this->device->CreateOffscreenPlainSurface(
		info.Width,
		info.Height,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&surface,
		NULL);

	if (D3DXLoadSurfaceFromFile(
		surface,
		NULL,
		NULL,
		filePath,
		NULL,
		D3DX_FILTER_TRIANGLE,
		transcolor,
		&info) != D3D_OK)
	{
		return NULL;
	}

	return surface;
}

bool GameGraphic::Init(HWND hWnd, bool isWindowed) {
	this->d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = isWindowed;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = WIDTH;
	d3dpp.BackBufferHeight = HEIGHT;

	if (!SUCCEEDED(this->d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&this->device)))
	{
		return false;
	}

	this->device->Clear(
		0,
		NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0, 0, 0),
		1.0f,
		0);

	this->device->GetBackBuffer(
		0,
		0,
		D3DBACKBUFFER_TYPE_MONO,
		&this->backBuffer);

	if (D3DXCreateSprite(this->device, &this->sprite) != D3D_OK)
	{
		return false;
	}
	return true;
}

void GameGraphic::Clear(DWORD color) {
	this->device->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0);
}

void GameGraphic::Begin() {
	this->device->BeginScene();
	this->sprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void GameGraphic::End() {
	this->sprite->End();
	this->device->EndScene();
}

void GameGraphic::Present() {
	this->device->Present(NULL, NULL, NULL, NULL);
}

void GameGraphic::DrawTexture(TEXTURE texture, RECT rect, VT3 center,
	VT3 position, VT2 scale, VT2 scalingCenter, VT2 translation, COLOR transcolor) {

	MATRIX oldMatrix;
	MATRIX matrix;

	D3DXMatrixTransformation2D(
		&matrix,
		&scalingCenter,
		0,
		&scale,
		NULL,
		0,
		&translation);

	this->sprite->GetTransform(&oldMatrix);
	this->sprite->SetTransform(&matrix);

	this->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	this->sprite->Draw(
		texture,
		&rect,
		&center,
		&position,
		transcolor);
	this->sprite->End();

	this->sprite->SetTransform(&oldMatrix);
}

void GameGraphic::DrawSurface(SURFACE surface, RECT * sRect, RECT * dRect) {
	this->device->StretchRect(
		surface,
		sRect,
		this->backBuffer,
		dRect,
		D3DTEXF_NONE);
}