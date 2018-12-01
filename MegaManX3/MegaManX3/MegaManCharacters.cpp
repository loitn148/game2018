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
	this->isAttacking = false;
	this->isJumping = false;
	this->isFalling = false;
	this->isRightLeftKeyDown = false;
	this->listAnimation = new Animation[14];

	this->megaManData = new MegaManData();
	this->megaManData->megaMan = this;
	this->SetState(new Start1State(this->megaManData));

	this->UpdateRect();
	this->SetListAnimation();
}

void MegaManCharacters::UpdatePosition(double time)
{
	this->dx = this->vx * time;
	this->dy = this->vy * time;

	this->position.x += this->dx;
	this->position.y += this->dy;

	this->UpdateRect();

	this->vy += this->ay;
	this->vx += this->ax;
}

void MegaManCharacters::Update(double time)
{
	vector<GameObject*> listCollision;
	GameMap::GetInstance()->GetQuadtree()->GetEntitiesCollideAble(listCollision, this);
	CollisionResult staticCollision;
	double entryTime = time;
	int deltaBottom = MEGAMAN_WIDTH;
	for (int i = 0; i < listCollision.size(); i++) {
		staticCollision = Collision::SweptAABB(this->rectBound, VT2(this->vx, this->vy), listCollision[i]->GetRect(), VT2(listCollision[i]->GetVx(), listCollision[i]->GetVy()), time);
		if (staticCollision.isCollision) {
			if (staticCollision.directCollision == BOTTOM) {
				deltaBottom = listCollision[i]->GetRect().right - this->rectBound.left;
			}
			entryTime = staticCollision.entryTime;
			break;
		}
	}

	this->UpdatePosition(entryTime);

	
	if (staticCollision.isCollision) {
		if (staticCollision.directCollision == BOTTOM) {
			if (this->currentState == START1) {
				this->SetState(new Start2State(this->megaManData));
			}
			else if (this->currentState == JUMPING || this->currentState == JUMPING_ATTACK) {
				this->vy = 0;
				this->ay = 0;
			}
			else if ((this->currentState == STANDING || this->currentState == RUNNING) && deltaBottom < MEGAMAN_WIDTH/5) {
				this->SetState(new JumpingState(this->megaManData));
			}
			else {
				this->SetState(new StandingState(this->megaManData));
			}
		}

		if (staticCollision.directCollision == TOP) {
			this->vy = 0;
		}

		if (staticCollision.directCollision == LEFT || staticCollision.directCollision == RIGHT) {
			if (this->currentState == JUMPING) {
				this->SetState(new SweepingWallState(this->megaManData));
			}
			else if (this->currentState == JUMPING_ATTACK) {
				this->SetState(new SweepingWallAttackState(this->megaManData));
			}
			this->vx = 0;
		}
	}

	if (this->megaManData->megaManState) {
		this->megaManData->megaManState->Update(entryTime);
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

		this->isRightLeftKeyDown = true;

		if (currentState == STANDING)
		{
			this->SetState(new RunningState(this->megaManData));
		}
		else if (currentState == STANDING_ATTACK) {
			this->SetState(new RunningAttackState(this->megaManData));
		}

		if (currentState != SWEEPING && currentState != SWEEPING_ATTACK) {
			if (keyCode == VK_RIGHT) {
				this->direct = RIGHT;
				this->vx = RUN_SPEED;
			}
			else {
				this->direct = LEFT;
				this->vx = -RUN_SPEED;
			}
		}
	}
}

void MegaManCharacters::OnKeyUp(int keyCode) {
	if (keyCode == VK_RIGHT || keyCode == VK_LEFT) {
		this->isRightLeftKeyDown = false;
		if (currentState == RUNNING)
		{
			this->SetState(new StandingState(this->megaManData));
		}
		if (currentState == JUMPING || currentState == JUMPING_ATTACK)
		{
			this->vx = 0;
		}
	}

	if (keyCode == VK_A) {
		if (currentState == STANDING_ATTACK) {
			this->SetState(new StandingState(this->megaManData));
		}
	}
}

void MegaManCharacters::Draw(double time) {
	this->transform.positionInViewport = this->GetPositionInViewport();
	VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
	this->transform.translation = VT2(-cameraPosition.x, -cameraPosition.y);

	this->listAnimation[this->currentState].Draw(transform.positionInViewport, this->direct, time, VT2(2.2, 2.5), transform.translation);
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

	this->listAnimation[START2].Create(START2_PATH, temp.size(), temp, 0.03f, RIGHT);
	temp.clear();

	//STANDING
	temp.push_back(Rect(0, 0, 34, 30));
	temp.push_back(Rect(0, 31, 34, 61));
	temp.push_back(Rect(0, 62, 34, 92));
	temp.push_back(Rect(0, 93, 34, 123));

	this->listAnimation[STANDING].Create(STAND_PATH, temp.size(), temp, 0.015f, RIGHT);
	temp.clear();

	//STANDING_ATTACK
	temp.push_back(Rect(0, 0, 34, 30));
	temp.push_back(Rect(0, 31, 34, 60));

	this->listAnimation[STANDING_ATTACK].Create(STAND_ATTACK_PATH, temp.size(), temp, 0.005f, RIGHT);
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

	//RUNNING_ATTACK
	temp.push_back(Rect(0, 113, 34, 142));
	temp.push_back(Rect(35, 71, 70, 103));
	temp.push_back(Rect(0, 77, 34, 112));
	temp.push_back(Rect(0, 0, 33, 38));
	temp.push_back(Rect(34, 36, 67, 70));
	temp.push_back(Rect(71, 70, 105, 101));
	temp.push_back(Rect(68, 36, 103, 69));
	temp.push_back(Rect(34, 0, 68, 35));
	temp.push_back(Rect(0, 39, 33, 76));
	temp.push_back(Rect(69, 0, 102, 35));

	this->listAnimation[RUNNING_ATTACK].Create(RUN_ATTACK_PATH, temp.size(), temp, 0.015f, RIGHT);
	temp.clear();

	//JUMPING
	temp.push_back(Rect(0, 84, 37, 108));
	temp.push_back(Rect(75, 0, 116, 15));
	temp.push_back(Rect(43, 24, 89, 43));
	temp.push_back(Rect(33, 0, 74, 23));
	temp.push_back(Rect(0, 31, 42, 58));
	temp.push_back(Rect(0, 59, 38, 83));
	temp.push_back(Rect(0, 0, 32, 30));

	this->listAnimation[JUMPING].Create(JUMP_PATH, temp.size(), temp, 0.01f, RIGHT);
	temp.clear();

	//JUMPING_ATTACK
	temp.push_back(Rect(72, 0, 109, 29));
	temp.push_back(Rect(0, 101, 41, 125));
	temp.push_back(Rect(43, 31, 89, 58));
	temp.push_back(Rect(0, 69, 41, 100));
	temp.push_back(Rect(0, 37, 42, 68));
	temp.push_back(Rect(33, 0, 71, 30));
	temp.push_back(Rect(0, 0, 32, 36));

	this->listAnimation[JUMPING_ATTACK].Create(JUMP_ATTACK_PATH, temp.size(), temp, 0.01f, RIGHT);
	temp.clear();


	//SWEEPING
	temp.push_back(Rect(27, 0, 58, 28));
	temp.push_back(Rect(0, 0, 26, 38));

	this->listAnimation[SWEEPING].Create(SWEEP_PATH, temp.size(), temp, 0.05f, RIGHT);
	temp.clear();

	//SWEEPING_ATTACK
	temp.push_back(Rect(27, 0, 58, 37));
	temp.push_back(Rect(0, 0, 26, 48));

	this->listAnimation[SWEEPING_ATTACK].Create(SWEEP_ATTACK_PATH, temp.size(), temp, 0.05f, RIGHT);
	temp.clear();

	//SWEEPING_WALL
	temp.push_back(Rect(0, 57, 42, 82));
	temp.push_back(Rect(0, 29, 43, 56));
	temp.push_back(Rect(0, 0, 42, 28));

	this->listAnimation[SWEEPING_WALL].Create(SWEEP_WALL_PATH, temp.size(), temp, 0.05f, RIGHT);
	temp.clear();

	//SWEEPING_WALL_ATTACK
	temp.push_back(Rect(0, 66, 39, 97));
	temp.push_back(Rect(0, 0, 43, 32));
	temp.push_back(Rect(0, 33, 42, 65));

	this->listAnimation[SWEEPING_WALL_ATTACK].Create(SWEEP_WALL_ATTACK_PATH, temp.size(), temp, 0.05f, RIGHT);
	temp.clear();

	//JUMPING_FROM_WALL
	temp.push_back(Rect(0, 0, 39, 30));
	temp.push_back(Rect(0, 62, 44, 89));
	temp.push_back(Rect(33, 31, 74, 54));
	temp.push_back(Rect(0, 90, 42, 117));
	temp.push_back(Rect(40, 0, 78, 24));
	temp.push_back(Rect(0, 31, 32, 61));

	this->listAnimation[JUMPING_FROM_WALL].Create(JUMP_FROM_WALL_PATH, temp.size(), temp, 0.05f, RIGHT);
	temp.clear();

	//JUMPING_FROM_WALL_ATTACK
	temp.push_back(Rect(75, 0, 113, 31));
	temp.push_back(Rect(0, 37, 39, 69));
	temp.push_back(Rect(33, 0, 74, 31));
	temp.push_back(Rect(0, 70, 42, 101));
	temp.push_back(Rect(40, 32, 78, 62));
	temp.push_back(Rect(0, 0, 32, 36));

	this->listAnimation[JUMPING_FROM_WALL_ATTACK].Create(JUMP_FROM_WALL_ATTACK_PATH, temp.size(), temp, 0.05f, RIGHT);
	temp.clear();
}

Animation* MegaManCharacters::GetListAnimation() {
	return this->listAnimation;
}

MegaManCharacters::~MegaManCharacters() {
}

