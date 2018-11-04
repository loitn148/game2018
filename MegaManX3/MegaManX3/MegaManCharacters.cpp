#include "MegaManCharacters.h"



MegaManCharacters* MegaManCharacters::instance = NULL;
MegaManCharacters* MegaManCharacters::GetInstance() {
	if (!MegaManCharacters::instance) {
		MegaManCharacters::instance = new MegaManCharacters();
	}
	return MegaManCharacters::instance;
}

MegaManCharacters::MegaManCharacters() {
	this->id = MEGAMAN;
	this->megaManData = new MegaManData();
	this->megaManData->megaMan = this;
}

void MegaManCharacters::Init(HINSTANCE hInstance, HWND hWnd) {
	this->hInstance = hInstance;
	this->hWnd = hWnd;
	this->id = MEGAMAN;
	this->direct = RIGHT;
	this->position = VT3(WIDTH, HEIGHT, 0);
	this->vx = this->vy = 0;
	this->ax = this->ay = 0;
	this->width = MEGAMAN_WIDTH;
	this->height = MEGAMAN_HEIGHT;
	this->listAnimation = new Animation[2];

	this->megaManData = new MegaManData();
	this->megaManData->megaMan = this;
	this->SetState(new StandingState(this->megaManData));

	this->UpdateRect();
	this->SetListAnimation();
}

void MegaManCharacters::UpdatePosition(double time)
{
	this->dx = (this->vx + this->ax) * time * this->direct;
	this->dy = (this->vy + this->ay) * time * this->direct;

	this->position.x += this->dx;
	this->position.y += this->dy;
}

void MegaManCharacters::Update(double time)
{
	this->UpdatePosition(time);
	if (this->megaManData->megaManState) {
		this->megaManData->megaManState->Update(time);
	}
}

void MegaManCharacters::HandleKeyboard(std::map<int, bool> keys) {
	/*if (this->megaManData->megaManState) {
		this->megaManData->megaManState->HandleKeyboard(keys);
	}*/
}

void MegaManCharacters::SetState(MegaManState *newState)
{
	delete this->megaManData->megaManState;

	this->megaManData->megaManState = newState;

	this->currentState = newState->GetState();
}

void MegaManCharacters::OnKeyDown(int keyCode) {
	if (keyCode == VK_RIGHT || VK_LEFT) {

		if (currentState == STANDING)
		{
			this->SetState(new RunningState(this->megaManData));
		}

		if (keyCode == VK_RIGHT) {
			this->direct = RIGHT;
		}
		else {
			this->direct = LEFT;
		}
	}
	if (keyCode == VK_UP || VK_DOWN) {

	}
}

void MegaManCharacters::OnKeyUp(int keyCode) {
	if (keyCode == VK_RIGHT || VK_LEFT) {

		if (currentState == RUNNING)
		{
			this->SetState(new StandingState(this->megaManData));
		}
	}
	if (keyCode == VK_UP || VK_DOWN) {

	}
}

void MegaManCharacters::Draw(double time) {
	this->transform.positionInViewport = this->GetPositionInViewport();
	VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
	this->transform.translation = VT2(-cameraPosition.x, -cameraPosition.y);

	this->listAnimation[this->currentState].Draw(transform.positionInViewport, this->direct, time, VT2(2, 2.5), transform.translation);
}

void MegaManCharacters::SetListAnimation() {
	std::vector<Rect> temp;

	//STANDING
	temp.push_back(Rect(0, 0, 34, 30));
	temp.push_back(Rect(0, 31, 34, 61));
	temp.push_back(Rect(0, 62, 34, 92));
	temp.push_back(Rect(0, 93, 34, 123));

	this->listAnimation[STANDING].Create(STAND_PATH, temp.size(), temp, 0.05f, RIGHT);
	temp.clear();

	//RUNNING
	temp.push_back(Rect(34, 0, 68, 30));
	temp.push_back(Rect(36, 88, 70, 108));
	temp.push_back(Rect(0, 103, 35, 126));
	temp.push_back(Rect(0, 70, 34, 102));
	temp.push_back(Rect(0, 0, 33, 34));
	temp.push_back(Rect(69, 30, 102, 56));
	temp.push_back(Rect(71, 57, 105, 79));
	temp.push_back(Rect(35, 62, 70, 87));
	temp.push_back(Rect(34, 31, 68, 61));
	temp.push_back(Rect(0, 35, 33, 69));
	temp.push_back(Rect(69, 0, 102, 29));

	this->listAnimation[RUNNING].Create(RUN_PATH, temp.size(), temp, 0.05f, RIGHT);
	temp.clear();
}

MegaManCharacters::~MegaManCharacters() {
}
