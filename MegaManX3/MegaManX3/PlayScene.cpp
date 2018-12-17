#include "PlayScene.h"



void PlayScene::LoadContent() {
	this->camera = Camera::GetInstance();
	this->camera->Create(VT3(CAMERA_START_X, CAMERA_START_Y, 0), WIDTH, HEIGHT);
	this->megaMan = MegaManCharacters::GetInstance();
	this->megaMan->Init(this->hInstance, this->hWnd);
	mMap = GameMap::GetInstance();
	mMap->Init("Assets/map/map.tmx");
	elevator1 = new Elevator1(VT3(1987, 2320, 0), 0, 0);
}

void PlayScene::Update(double time) {
	CollisionResult collisiontResult = CheckCollision(this->megaMan, this->elevator1, time);
	if (collisiontResult.isCollision && collisiontResult.directCollision == BOTTOM) {
		if (this->elevator1->GetIsActive() == false) {
			this->elevator1->SetIsActive(true);
			this->elevator1->SetVy(100);
		}
		this->megaMan->SetVy(100);
		this->megaMan->SetAy(0);

		int deltaBottom = MEGAMAN_WIDTH;
		if (this->megaMan->GetDirect() == RIGHT) {
			deltaBottom = this->elevator1->GetRect().right - this->megaMan->GetRect().left;
		}
		else if (this->megaMan->GetDirect() == LEFT) {
			deltaBottom = this->megaMan->GetRect().right - this->elevator1->GetRect().left;
		}

		if (deltaBottom <= MEGAMAN_WIDTH / 5) {
			this->megaMan->SetState(new FallingState(this->megaMan->GetMegaManData()));
		}
	}
	this->megaMan->Update(time);
	this->camera->Update(this->megaMan);
	this->megaMan->HandleKeyboard(this->keys);
	this->elevator1->Update(time);
}

void PlayScene::Draw(double time) {
	mMap->Draw();
	this->megaMan->Draw(time);
	this->elevator1->Draw(time);
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

CollisionResult PlayScene::CheckCollision(GameObject* obj1, GameObject* obj2, double time) {
	CollisionResult collisiontResult;
	collisiontResult = Collision::SweptAABB(obj1->GetRect(), VT2(obj1->GetVx(), obj1->GetVy()), obj2->GetRect(), VT2(obj2->GetVx(), obj2->GetVy()), time);
	return collisiontResult;
}

PlayScene::~PlayScene() {
}


