#include "Bar.h"



Bar::Bar() {
	this->id = BAR;
}


Bar::~Bar() {
}

Bar::Bar(VT3 position, double vx, double vy, HWND hWnd, HINSTANCE hInstance, int barIdx) {
	this->listBar = new Animation[1];
	std::vector<Rect> temp;

	temp.push_back(Rect(0, 0, 200, 20));

	this->listBar[0].Create(BAR_PATH, temp.size(), temp, 0.015f, RIGHT);
	temp.clear();

	this->currentState = 0;
	this->id = BAR;
	this->position = position;
	this->vx = vx;
	this->vy = vy;
	this->isDead = false;
	this->width = 20;
	this->height = 200;
	this->hWnd = hWnd;
	this->hInstance = hInstance;
	this->InitKeyBoard(hInstance, hWnd);
	this->barIdx = barIdx;
	UpdateRect();
}

void Bar::Update(double time)
{
	this->ProcessKeyBoard(this->hWnd);
	UpdateRect();

	this->position.y += this->vy*time;

	if (this->position.y + this->height >= HEIGHT) {
		this->position.y = HEIGHT - this->height;
	}
	else if (this->position.y <= 0) {
		this->position.y = 0;
	}
}

void Bar::OnKeyUp(int keyCode) {
	if (barIdx == 1) {
		switch (keyCode) {
		case DIK_UP:
			this->vy = 0.0f;
			break;
		case DIK_DOWN:
			this->vy = 0.0f;
			break;
		}
	}
	else {
		switch (keyCode) {
		case DIK_W:
			this->vy = 0.0f;
			break;
		case DIK_S:
			this->vy = 0.0f;
			break;
		}
	}
	
}

void Bar::OnKeyDown(int keyCode) {
	if (barIdx == 1) {
		switch (keyCode) {
		case DIK_UP:
			this->vy = 500.0f;
			break;
		case DIK_DOWN:
			this->vy = -500.0f;
			break;
		}
	}
	else {
		switch (keyCode) {
		case DIK_W:
			this->vy = 500.0f;
			break;
		case DIK_S:
			this->vy = -500.0f;
			break;
		}
	}
}

void Bar::Draw(double time) {
	if (!this->isDead)
	{
		this->transform.positionInViewport = this->GetPositionInViewport();
		VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
		this->transform.translation = VT2(-cameraPosition.x, -cameraPosition.y);

		this->listBar[this->currentState].Draw(this->transform.positionInViewport, this->direct, time, VT2(1, 1), this->transform.translation);
	}
}
