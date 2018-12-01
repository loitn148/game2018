#include "GameSprite.h"



GameSprite::GameSprite() {
	this->sprite = GameGraphic::GetInstance()->GetSprite();
	this->texture = NULL;
}


GameSprite::~GameSprite() {
	if (this->sprite) {
		this->sprite->Release();
		this->sprite = NULL;
	}
}

GameSprite::GameSprite(const char* filePath, COLOR transcolor) {
	this->InitWithSprite(filePath, transcolor);
}

GameSprite* GameSprite::instance = NULL;

GameSprite* GameSprite::GetInstance() {
	if (!GameSprite::instance)
	{
		GameSprite::instance = new GameSprite();
	}
	return GameSprite::instance;
}

bool GameSprite::Init(DEVICE device) {
	if (!SUCCEEDED(D3DXCreateSprite(device, &this->sprite)))
	{
		MessageBox(NULL, "Create Sprite Error!", NULL, MB_OK);
		return false;
	}
	return true;
}


void GameSprite::InitWithSprite(const char* filePath, COLOR transcolor) {
	this->sprite = GameGraphic::GetInstance()->GetSprite();
	D3DXIMAGE_INFO info;
	HRESULT hResult;

	hResult = D3DXGetImageInfoFromFile(filePath, &info);

	GameGraphic *gameGraphic = GameGraphic::GetInstance();

	this->rect = rect;
	if (!this->isRect(rect)) {
		this->rect.left = 0;
		this->rect.top = info.Height;
		this->rect.right = info.Width;
		this->rect.bottom = 0;
	}

	hResult = D3DXCreateTextureFromFileEx(
		gameGraphic->device,
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
		&this->texture);

	if (hResult != D3D_OK) {
		//MessageBox(NULL, "Create Texture Error!", "Error", MB_OK);
		return;
	}
}

bool GameSprite::isRect(RECT rect)
{
	if (rect.left == rect.right)
		return false;

	if (rect.top == rect.bottom)
		return false;

	return true;
}

void GameSprite::Begin() {
	this->sprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void GameSprite::End() {
	this->sprite->End();
}


void GameSprite::Draw(VT3 position, VT2 translation, VT3 center, RECT rect, VT2 scale, float angle, VT2 rotationCenter, COLOR transcolor) {
	MATRIX oldMatrix;
	MATRIX matrix;

	VT2 scalingCenter = VT2(position.x, position.y);

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
		this->texture,
		&rect,
		&center,
		&position,
		transcolor);

	this->sprite->End();

	this->sprite->SetTransform(&oldMatrix);
}


void GameSprite::ResetTranform() {
	this->sprite->SetTransform(&matrix);
}

void GameSprite::FlipX(int width, int height, VT3 position) {
	this->sprite->GetTransform(&matrix);
	MATRIX matrixFlip;
	//tao ma tran don vi
	D3DXMatrixIdentity(&matrixFlip);
	//lat quanh truc y
	matrixFlip._11 = -1;
	//di chuyen ve mot luong bang gap 2 khoang canh tu tam
	matrixFlip._41 = (position.x + width / 2) * 2;
	this->sprite->SetTransform(&(matrix * matrixFlip));
}

void GameSprite::FlipY(int width, int height, VT3 position) {
	this->sprite->GetTransform(&matrix);
	MATRIX matrixFlip;
	//tao ma tran don vi
	D3DXMatrixIdentity(&matrixFlip);
	//lat quanh truc y
	matrixFlip._22 = -1;
	//di chuyen ve mot luong bang gap 2 khoang canh tu tam
	matrixFlip._42 = (position.y + height / 2) * 2;
	this->sprite->SetTransform(&(matrix * matrixFlip));
}

SPRITE GameSprite::GetSrpite() {
	return this->sprite;
}
TEXTURE GameSprite::GetTexture() {
	return this->texture;
}
VT3 GameSprite::GetPosition() {
	return this->position;
}
