#include "PlaySence.h"



void PlaySence::LoadContent() {
	this->ball = new Ball(VT3(200.0f, 400.0f, 0), 400.0f, 400.0f);
	this->bar = new Bar(VT3(WIDTH - 10.0f, 100.0f, 0.0f), 0.0f, 0.0f, this->hWnd, this->hInstance, BAR1);
	this->bar2 = new Bar(VT3(10.0f, 100.0f, 0.0f), 0.0f, 0.0f, this->hWnd, this->hInstance, BAR2);
	this->ball->SetBar(bar, bar2);
	this->camera = Camera::GetInstance();
	this->camera->Create(VT3(0, HEIGHT, 0), WIDTH, HEIGHT);

	this->map = new Map();
}

void PlaySence::Update(double time) {
	this->camera->Update();
	this->ball->Update(time);
	this->bar->Update(time);
	this->bar2->Update(time);
}

void PlaySence::Draw(double time) {
	this->map->Draw();
	this->ball->Draw(time);
	this->bar->Draw(time);
	this->bar2->Draw(time);
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
