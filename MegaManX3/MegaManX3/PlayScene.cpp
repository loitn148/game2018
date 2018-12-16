#include "PlayScene.h"



void PlayScene::LoadContent() {
	this->camera = Camera::GetInstance();
	this->camera->Create(VT3(CAMERA_START_X, CAMERA_START_Y, 0), WIDTH, HEIGHT);
	this->megaMan = MegaManCharacters::GetInstance();
	this->megaMan->Init(this->hInstance, this->hWnd);
	mMap = GameMap::GetInstance();
	mMap->Init("Assets/map/map.tmx");
	bossNormal = new BossNormal(VT3(0, 2400, 0), 0, 0);
}

void PlayScene::Update(double time) {
	this->megaMan->Update(time);
	this->camera->Update(this->megaMan);
	this->megaMan->HandleKeyboard(this->keys);
	this->bossNormal->Update(time);
}

void PlayScene::Draw(double time) {
	mMap->Draw();
	this->megaMan->Draw(time);
	this->bossNormal->Draw(time);
}

PlayScene::PlayScene(HWND hWnd, HINSTANCE hInstance) {
	this->hWnd = hWnd;
	this->hInstance = hInstance;
}

void PlayScene::OnKeyDown(int keyCode) {
	this->keys[keyCode] = true;
	this->megaMan->OnKeyDown(keyCode);
}

void PlayScene::OnKeyUp(int keyCode) {
	this->keys[keyCode] = false;
	this->megaMan->OnKeyUp(keyCode);
}

PlayScene::PlayScene() {
	this->hWnd = NULL;
	this->hInstance = NULL;
}

PlayScene::~PlayScene() {
}


