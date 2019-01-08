#include "BossFinal.h"
#include "BossFinalStartState.h"
#include "BossFinalPrickState.h"
#include "BossFinalCallEnemies.h"
#include "Enemy.h"


BossFinal::BossFinal()
{
	this->id = BOSSFINAL;
	this->bossFinalData = new BossFinalData();
	this->bossFinalData->bossFinal = this;
}


BossFinal::~BossFinal()
{
}

void BossFinal::UpdatePosition(double time)
{
	this->dx = this->vx * time;
	this->dy = this->vy * time;

	this->position.x += this->dx;
	this->position.y += this->dy;

	this->UpdateRect();

	this->vx += this->ax;
	this->vy += this->ay;
}

BossFinal::BossFinal(D3DXVECTOR3 position, float vx, float vy)
{
	this->id = BOSSFINAL;
	this->direct = LEFT;
	this->position = position;
	this->vx = vx;
	this->vy = vy;
	this->ax = 0;
	this->ay = 0;
	this->isDead = false;
	this->isIntro = true;
	this->isPrick = false;
	this->isJustPrick = false;
	this->isCallEnemies = false;
	this->width = 70;
	this->height = 100;
	listAnimation = new Animation[5];

	wings = new Wings(VT3(this->position.x, this->position.y + 120, 0), this->vx, this->vy);

	this->bossFinalData = new BossFinalData();
	this->bossFinalData->bossFinal = this;
	this->SetState(new BossFinalStartState(this->bossFinalData));

	this->UpdateRect();
	this->SetListAnimation();
}

void BossFinal::Update(double time)
{
	CollisionResult result;

	if (this->isIntro)
	{
		if (this->currentState == START)
		{
			if (this->position.y < 2300)
			{
				this->vx = 0;
				this->vy = 500;
			}

			else if (this->position.y > 2500)
			{
				this->currentState = CALL_ENEMIES;
				this->vx = 0;
				this->vy = 0;
			}
		}

		if (this->currentState == CALL_ENEMIES)
		{
			if (this->listAnimation[this->currentState].GetIndex() == 4)
			{
				this->currentState = PRICK;
				this->vx = 0;
				this->vy = 0;
			}
		}

		if (this->currentState == PRICK)
		{
			if (this->listAnimation[this->currentState].GetIndex() == 11)
			{
				this->isIntro = false;
				this->SetState(new BossFinalStartState(this->bossFinalData));
				this->vx = 0;
				this->vy = 200;
			}
		}
	}
	else
	{
		if (this->currentState == START)
		{
			if (this->position.y >= 2600)
			{
				if (this->isJustPrick)
				{
					this->listAnimation[this->currentState].SetIndex(0);
					this->SetState(new BossFinalCallEnemies(this->bossFinalData));
				}
				else
				{
					this->listAnimation[this->currentState].SetIndex(0);
					this->SetState(new BossFinalPrickState(this->bossFinalData));
				}
			}
		}

		if (this->currentState == CALL_ENEMIES)
		{
			if (this->listAnimation[this->currentState].GetIndex() == 4)
			{
				this->listAnimation[this->currentState].SetIndex(0);
				this->SetState(new BossFinalStartState(this->bossFinalData));
				this->vx = 0;
				this->vy = 0;
				CallEnemy();
			}
		}

		if (this->currentState == PRICK)
		{
			if (this->isJustPrick)
			{
				this->listAnimation[this->currentState].SetIndex(0);
				this->SetState(new BossFinalStartState(this->bossFinalData));
			}
		}

		if (this->currentState == DEAD)
		{
			if (this->position.y <= 2300)
			{
				this->vx = 0;
				this->vy = 0;
			}
			else
			{
				this->vx = 0;
				this->vy = -300;
			}
		}
	}
	

	this->UpdatePosition(time);

	if (this->bossFinalData->bossFinalState) {
		this->bossFinalData->bossFinalState->Update(time);
	}

	this->wings->Update(this->position, this->currentState);
	if (isCallEnemies)
	{
		for (int i = 0; i < 3; i++)
		{
			enemies[i].Update(time, megaMan->GetInstance());
		}
	}
}

void BossFinal::SetState(BossFinalState *newState)
{
	delete this->bossFinalData->bossFinalState;

	this->bossFinalData->bossFinalState = newState;

	this->currentState = newState->GetState();
}

void BossFinal::Draw(double time)
{
	if (!isDead)
	{
		this->transform.positionInViewport = this->GetPositionInViewport();
		VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
		this->transform.translation = VT2(-cameraPosition.x, -cameraPosition.y);
		this->wings->Draw(time, this->currentState);
		if (isCallEnemies)
		{
			for (int i = 0; i < 3; i++)
			{
				enemies[i].Draw(time);
			}
		}

		this->listAnimation[this->currentState].Draw(transform.positionInViewport, this->direct, time, VT2(2.2, 2.5), transform.translation);
	}
}

void BossFinal::SetListAnimation() {
	std::vector<Rect> temp;

	//BOSS FINAL START
	temp.push_back(Rect(0, 0, 62, 50));

	listAnimation[START].Create(BOSSFINAL_PATH, temp.size(), temp, 0.05f, LEFT);
	temp.clear();

	//BOSS FINAL FLY
	temp.push_back(Rect(0, 0, 62, 50));

	listAnimation[FLY].Create(BOSSFINAL_PATH, temp.size(), temp, 0.05f, LEFT);
	temp.clear();

	//BOSS FINAL PRICK
	temp.push_back(Rect(0, 45, 60, 88));
	temp.push_back(Rect(55, 210, 112, 248));
	temp.push_back(Rect(58, 129, 112, 168));
	temp.push_back(Rect(0, 210, 54, 249));
	temp.push_back(Rect(58, 169, 112, 208));
	temp.push_back(Rect(0, 130, 57, 169));
	temp.push_back(Rect(58, 89, 115, 128));
	temp.push_back(Rect(0, 170, 57, 209));
	temp.push_back(Rect(61, 44, 118, 87));
	temp.push_back(Rect(0, 89, 57, 129));
	temp.push_back(Rect(59, 0, 116, 43));
	temp.push_back(Rect(0, 0, 58, 44));

	listAnimation[PRICK].Create(BOSSFINAL_PRICK_PATH, temp.size(), temp, 0.05f, LEFT);
	temp.clear();

	//BOSS FINAL CALL ENEMIES
	temp.push_back(Rect(0, 0, 62, 51));
	temp.push_back(Rect(0, 52, 67, 100));
	temp.push_back(Rect(0, 101, 72, 148));
	temp.push_back(Rect(0, 196, 72, 241));
	temp.push_back(Rect(0, 149, 72, 195));

	listAnimation[CALL_ENEMIES].Create(BOSSFINAL_CALL_ENEMIES_PATH, temp.size(), temp, 0.05f, LEFT);
	temp.clear();

	//BOSS FINAL DEAD
	temp.push_back(Rect(0, 0, 48, 96));

	listAnimation[DEAD].Create(BOSSFINAL_DEAD_PATH, temp.size(), temp, 0.05f, LEFT);
	temp.clear();
}

Animation* BossFinal::GetListAnimation() {
	return this->listAnimation;
}

void BossFinal::CallEnemy()
{
	if (sizeof(enemies) > 0)
	{
		delete[] enemies;
	}
	enemies = new Enemy[3];
	this->isCallEnemies = true;
	enemies[0] = Enemy(VT3(this->position.x + this->direct * 90, this->position.y + 100, 0), 10, 10, this->direct);
	enemies[1] = Enemy(VT3(this->position.x + this->direct * 120, this->position.y + 70, 0), 10, 10, this->direct);
	enemies[2] = Enemy(VT3(this->position.x + this->direct * 60, this->position.y + 60, 0), 10, 10, this->direct);
}