#include "Game.h"

Game::Game() {
	this->timeLoop = 0;
}

Game::~Game()
{
}

bool Game::Init(HWND hWnd, HINSTANCE hInstance) {
	this->hWnd = hWnd;
	this->hInstance = hInstance;

	GameGraphic::GetInstance()->Init(hWnd, true);
	if (!GameGraphic::GetInstance()->Init(hWnd, true)) {
		return false;
	}
	GameSprite::GetInstance()->Init(GameGraphic::GetInstance()->device);
	GameTime::GetInstance()->Init();

	this->LoadContent();
	return true;
}

void Game::Run() {
	GameTime::GetInstance()->Run();

	this->timeLoop += GameTime::GetInstance()->currentTime;
	if (this->timeLoop >= 1.0f / 60)
	{
		if (GameGraphic::GetInstance()->device->BeginScene()) {

			GameGraphic::GetInstance()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
			GameGraphic::GetInstance()->device->ColorFill(
				GameGraphic::GetInstance()->GetBackBuffer(),
				NULL,
				D3DCOLOR_XRGB(255, 255, 0)
			);

			SenceManager::GetInstance()->GetCurrentSence()->Update(this->timeLoop);

			GameGraphic::GetInstance()->Begin();
			GameSprite::GetInstance()->Begin();

			SenceManager::GetInstance()->GetCurrentSence()->Draw(this->timeLoop);

			GameSprite::GetInstance()->End();
			GameGraphic::GetInstance()->End();
			GameGraphic::GetInstance()->Present();

		}

		this->timeLoop = 0;
	}
}

void Game::LoadContent() {
	PlaySence* sence = new PlaySence(this->hWnd, this->hInstance);
	sence->LoadContent();
	SenceManager::GetInstance()->ReplaceSence(sence);
}