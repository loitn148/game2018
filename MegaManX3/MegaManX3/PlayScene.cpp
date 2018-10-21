#include "PlayScene.h"



void PlayScene::LoadContent() {
	//this->camera = Camera::GetInstance();
	//this->camera->Create(VT3(CAMERA_START_X, CAMERA_START_Y, 0), WIDTH, HEIGHT);
	this->megaMan = MegaManCharacters::GetInstance();
	this->megaMan->Init(this->hInstance, this->hWnd);
	mMap = new GameMap("Assets//untitled.tmx");
	//this->map = new Map();
}

void PlayScene::Update(double time) {
	this->megaMan->Update(time);
	//this->camera->Update(this->megaMan);
	//this->megaMan->HandleKeyboard(this->keys);
}

void PlayScene::Draw(double time) {
	//this->map->Draw();
	mMap->Draw();
	this->megaMan->Draw(time);
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


