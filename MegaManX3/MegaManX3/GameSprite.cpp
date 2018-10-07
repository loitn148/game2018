#include "GameSprite.h"



GameSprite::GameSprite() {
	this->sprite = NULL;
}


GameSprite::~GameSprite() {
	if (this->sprite) {
		this->sprite->Release();
		this->sprite = NULL;
	}
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

void GameSprite::Begin() {
	this->sprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void GameSprite::End() {
	this->sprite->End();
}


void GameSprite::Draw(TEXTURE texture, RECT* rect, VT3 center, VT3 position, VT2 scale, VT2 scalingCenter, VT2 translation) {
	GameGraphic::GetInstance()->DrawTexture(texture, *rect, center, position, scale, scalingCenter, translation);
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
