#include "PlayScene.h"



void PlayScene::LoadContent() {
	this->camera = Camera::GetInstance();
	this->camera->Create(VT3(6500, 2200, 0), WIDTH, HEIGHT);
	this->megaMan = MegaManCharacters::GetInstance();
	this->megaMan->Init(this->hInstance, this->hWnd);
	mMap = GameMap::GetInstance();
	mMap->Init("Assets/map/map.tmx");
	elevator1 = new Elevator1(VT3(1987, 2315, 0), 0, 0);
	this->InitGameOverImage();
}

void PlayScene::Update(double time) {
	if (!this->megaMan->GetIsDead()) {
		double entryTime = time;
		CollisionResult collisiontResult = CheckCollision(this->megaMan, this->elevator1, time);
		if (collisiontResult.isCollision && collisiontResult.directCollision == BOTTOM) {
			if (this->elevator1->GetIsActive() == false) {
				this->elevator1->SetIsActive(true);
				this->elevator1->SetVy(300);
				this->camera->SetPosition(VT3(1705, 2785, 0));
			}
			this->megaMan->AddPosition(VT3(0, this->megaMan->GetVy() * collisiontResult.entryTime, 0));
			this->megaMan->SetVy(this->elevator1->GetVy());
			this->megaMan->SetAy(0);

			this->megaMan->SetState(new StandingState(this->megaMan->GetMegaManData()));
		}
		for (int i = 0; i < mMap->vecEnemy.size(); i++)
		{
			mMap->vecEnemy[i]->Update(time);
		}
		this->megaMan->Update(time);
		this->elevator1->Update(time);
		this->camera->Update(this->megaMan);
		this->megaMan->HandleKeyboard(this->keys);
	}
}

void PlayScene::Draw(double time) {
	mMap->Draw();

	if (this->megaMan->GetIsDead()) {
		this->DrawOnGameOver();
	}
	else {
		for (int i = 0; i < mMap->vecEnemy.size(); i++)
		{
			mMap->vecEnemy[i]->Draw(time);
		}
		this->megaMan->Draw(time);
		this->elevator1->Draw(time);
	}
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

void PlayScene::InitGameOverImage() {
	this->gameOverImages = GameGraphic::GetInstance()->LoadTexture("Assets/gameover.png", C_XRGB(0, 0, 0));
}

void PlayScene::DrawOnGameOver() {
	VT3 _position = VT3(camera->GetPosition().x + 150, camera->GetPosition().y - 185, 0);

	VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
	VT2 translation = VT2(-cameraPosition.x, -cameraPosition.y);
	VT3 inPosition = Viewport::GetInstance()->GetPositionInViewport(_position);
	GameGraphic::GetInstance()->DrawTexture(this->gameOverImages, Rect(0, 0, 130, 250), VT3(0, 0, 0), inPosition, VT2(1, 1), VT2(inPosition.x, inPosition.y), translation, C_XRGB(255, 255, 255));
}