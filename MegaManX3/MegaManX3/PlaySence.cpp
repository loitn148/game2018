#include "PlaySence.h"



void PlaySence::LoadContent() {
	this->ball = new Ball(VT3(WIDTH/2, HEIGHT/2, 0), 400.0f, 400.0f);

	this->camera = Camera::GetInstance();
	this->camera->Create(VT3(0, HEIGHT, 0), WIDTH, HEIGHT);

	this->map = new Map();
}

void PlaySence::Update(float time) {
	this->camera->Update();
	this->ball->Update(time);
}

void PlaySence::Draw(float time) {
	this->map->Draw();
	this->ball->Draw(time);
}

PlaySence::PlaySence(HWND hWnd, HINSTANCE hInstance) {
	this->hWnd = hWnd;
	this->hInstance = hInstance;
}

PlaySence::PlaySence() {
	this->hWnd = NULL;
	this->hInstance = NULL;
}

PlaySence::~PlaySence() {
}
