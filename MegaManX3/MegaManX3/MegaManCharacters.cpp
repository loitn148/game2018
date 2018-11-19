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
	this->position = VT3(MEGAMAN_START_X, MEGAMAN_START_Y, 0);
	this->vx = this->vy = 0;
	this->ax = this->ay = 0;
	this->width = MEGAMAN_WIDTH;
	this->height = MEGAMAN_HEIGHT;
	this->listAnimation = new Animation[6];

	this->megaManData = new MegaManData();
	this->megaManData->megaMan = this;
	this->SetState(new Start1State(this->megaManData));

	this->UpdateRect();
	this->SetListAnimation();
}

void MegaManCharacters::UpdatePosition(double time)
{
	this->dx = (this->vx + this->ax) * time * this->direct;
	this->dy = (this->vy + this->ay) * time;

	this->position.x += this->dx;
	this->position.y += this->dy;

	this->UpdateRect();
}

void MegaManCharacters::Update(double time)
{

	GameMap::GetInstance()->GetQuadtree()->GetEntitiesCollideAble(listCollision, this);
	CollisionResult staticCollision;
	double entryTime = time;
	for (int i = 0; i < listCollision.size(); i++) {
		staticCollision = Collision::SweptAABB(this->rectBound, VT2(this->vx, this->vy), listCollision[i]->GetRect(), VT2(listCollision[i]->GetVx(), listCollision[i]->GetVy()), time);
		if (staticCollision.isCollision) {
			entryTime = staticCollision.entryTime;
			break;
		}
	}

	this->UpdatePosition(entryTime);

	if (this->megaManData->megaManState) {
		this->megaManData->megaManState->Update(entryTime);
	}

	if (staticCollision.isCollision) {
		if (this->currentState == START1) {
			this->SetState(new Start2State(this->megaManData));
		}
		else {
			this->SetState(new StandingState(this->megaManData));
		}
	}
}

void MegaManCharacters::HandleKeyboard(std::map<int, bool> keys) {
	if (this->megaManData->megaManState) {
		this->megaManData->megaManState->HandleKeyboard(keys);
	}
}

void MegaManCharacters::SetState(MegaManState *newState)
{
	delete this->megaManData->megaManState;

	this->megaManData->megaManState = newState;

	this->currentState = newState->GetState();
}

void MegaManCharacters::OnKeyDown(int keyCode) {
	if (keyCode == VK_RIGHT || keyCode == VK_LEFT) {

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
}

void MegaManCharacters::OnKeyUp(int keyCode) {
	if (keyCode == VK_RIGHT || keyCode == VK_LEFT) {

		if (currentState == RUNNING)
		{
			this->SetState(new StandingState(this->megaManData));
		}
	}
	if (keyCode == VK_UP) {
		if (currentState == STANDING) {
			this->SetState(new JumpingState(this->megaManData));
		}
	}
}

void MegaManCharacters::Draw(double time) {
	this->transform.positionInViewport = this->GetPositionInViewport();
	VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
	this->transform.translation = VT2(-cameraPosition.x, -cameraPosition.y);

	this->listAnimation[this->currentState].Draw(transform.positionInViewport, this->direct, time, VT2(2.5, 3), transform.translation);
}

void MegaManCharacters::SetListAnimation() {
	std::vector<Rect> temp;

	//START1
	temp.push_back(Rect(0, 0, 48, 8));

	this->listAnimation[START1].Create(START1_PATH, temp.size(), temp, 0.05f, RIGHT);
	temp.clear();

	//START2
	temp.push_back(Rect(40, 31, 69, 53));
	temp.push_back(Rect(0, 0, 42, 30));
	temp.push_back(Rect(0, 31, 39, 61));
	temp.push_back(Rect(0, 62, 36, 92));
	temp.push_back(Rect(0, 93, 34, 123));
	temp.push_back(Rect(43, 0, 75, 30));

	this->listAnimation[START2].Create(START2_PATH, temp.size(), temp, 0.05f, RIGHT);
	temp.clear();

	//STANDING
	temp.push_back(Rect(0, 0, 34, 30));
	temp.push_back(Rect(0, 31, 34, 61));
	temp.push_back(Rect(0, 62, 34, 92));
	temp.push_back(Rect(0, 93, 34, 123));

	this->listAnimation[STANDING].Create(STAND_PATH, temp.size(), temp, 0.05f, RIGHT);
	temp.clear();

	//RUNNING
	temp.push_back(Rect(70, 53, 104, 73));
	temp.push_back(Rect(0, 103, 35, 126));
	temp.push_back(Rect(0, 70, 34, 102));
	temp.push_back(Rect(0, 0, 33, 34));
	temp.push_back(Rect(69, 0, 102, 26));
	temp.push_back(Rect(35, 61, 69, 83));
	temp.push_back(Rect(69, 27, 104, 52));
	temp.push_back(Rect(34, 0, 68, 30));
	temp.push_back(Rect(0, 35, 33, 69));
	temp.push_back(Rect(34, 31, 67, 60));

	this->listAnimation[RUNNING].Create(RUN_PATH, temp.size(), temp, 0.015f, RIGHT);
	temp.clear();

	//JUMPING
	temp.push_back(Rect(0, 84, 37, 108));
	temp.push_back(Rect(75, 0, 116, 15));
	temp.push_back(Rect(43, 24, 89, 43));
	temp.push_back(Rect(33, 0, 74, 23));
	temp.push_back(Rect(0, 31, 42, 58));
	temp.push_back(Rect(0, 59, 38, 83));
	temp.push_back(Rect(0, 0, 32, 30));

	this->listAnimation[JUMPING].Create(JUMP_PATH, temp.size(), temp, 0.02f, RIGHT);
	temp.clear();

	//SWEEPING
	temp.push_back(Rect(27, 0, 58, 28));
	temp.push_back(Rect(0, 0, 26, 38));

	this->listAnimation[SWEEPING].Create(SWEEP_PATH, temp.size(), temp, 0.05f, RIGHT);
	temp.clear();
}

Animation* MegaManCharacters::GetListAnimation() {
	return this->listAnimation;
}

MegaManCharacters::~MegaManCharacters() {
}

