#include "EnemySweeping.h"
#include "EnemySweepingNormalState.h"

EnemySweeping::EnemySweeping()
{
}

void EnemySweeping::Init(VT3 position, int width, int height, Direct direct)
{
	this->id = ENEMYROCKET;
	this->direct = direct;
	this->position = position;
	oldPosition = position;
	this->vx = this->vy = 0;
	this->ax = this->ay = 0;
	this->width = width;
	this->height = height;
	this->listAnimation = new Animation[4];
	this->SetBasePos(position);
	this->enemySweepingData = new EnemySweepingData();
	this->enemySweepingData->enemySweeping = this;
	this->SetState(new EnemySweepingNormalState(this->enemySweepingData));
	SetDead(false);
	this->UpdateRect();
	this->SetListAnimation();
	nLife = 3;
}
void EnemySweeping::Draw(double time)
{
	if (!GetDead() && checkCamera(time))
	{
		this->transform.positionInViewport = this->GetPositionInViewport();
		VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
		this->transform.translation = VT2(-cameraPosition.x, -cameraPosition.y);

		this->listAnimation[currentState].Draw(transform.positionInViewport, this->direct, time, VT2(3, 3), transform.translation);
	}
	if (rocket != NULL && !rocket->GetIsDead())
	{
		rocket->Draw(time);
	}
}
void EnemySweeping::Update(double time)
{
	if (!GetDead() && checkCamera(time))
	{


		vector<GameObject*> listCollision;
		GameMap::GetInstance()->GetQuadtree()->GetEntitiesCollideAble(listCollision, this);
		CollisionResult staticCollision;
		double entryTime = time;
		for (int i = 0; i < listCollision.size(); i++)
		{
			staticCollision = Collision::SweptAABB(rectBound, VT2(this->vx, this->vy), listCollision[i]->GetRect(), VT2(listCollision[i]->GetVx(), listCollision[i]->GetVy()), time);
			if (staticCollision.isCollision)
			{
				if (listCollision[i]->GetId() == Object::BULLET)
				{
					if (nLife > 0)
					{
						nLife--;
					}
					if (nLife == 0)
					{
						SetDead(true);

					}
				}
			}
			else
			{
				
			}
		}
		if (this->enemySweepingData->enemySweeping->GetPosition().x > MegaManCharacters::GetInstance()->GetPosition().x)
		{
			this->enemySweepingData->enemySweeping->SetDirect(Direct::LEFT);
		}
		else
		{
			this->enemySweepingData->enemySweeping->SetDirect(Direct::RIGHT);
		}
		this->enemySweepingData->enemySweepingState->Update(time);

		UpdatePosition(time);
	}
	if (rocket != NULL && !rocket->GetIsDead())
	{
		rocket->Update(time);
	}
	else
	{
		delete rocket;
		rocket = NULL;
	}
}
void EnemySweeping::SetState(EnemySweepingState* state)
{
	if (!this->enemySweepingData->enemySweepingState)
		delete this->enemySweepingData->enemySweepingState;

	this->enemySweepingData->enemySweepingState = state;

	this->currentState = state->GetState();
}
void EnemySweeping::SetListAnimation()
{
	std::vector<Rect> temp;
	temp.push_back(Rect(0, 96, 36, 120));
	temp.push_back(Rect(0, 40, 36, 67));
	temp.push_back(Rect(0, 0, 36, 39));
	temp.push_back(Rect(0, 68, 36, 95));
	temp.push_back(Rect(37, 0, 73, 24));
	this->listAnimation[ENEMYSWEEPINGNORMAL].Create(ENEMIES_SWEEPING_NORMAL, temp.size(), temp, 0.005f, LEFT);

	temp.clear();
	temp.push_back(Rect(0, 96, 36, 120));
	temp.push_back(Rect(0, 40, 36, 67));
	temp.push_back(Rect(0, 0, 36, 39));
	temp.push_back(Rect(0, 68, 36, 95));
	temp.push_back(Rect(37, 0, 73, 24));
	this->listAnimation[ENEMYSWEEPINGSHOOTING].Create(ENEMIES_SWEEPING_SHOOTING, temp.size(), temp, 0.005f, LEFT);



}

void EnemySweeping::UpdatePosition(double time)
{
	this->dx = this->vx * time;
	this->dy = this->vy * time;

	this->position.x += this->dx;
	this->position.y += this->dy;

	this->UpdateRect();

	this->vy += this->ay;
	this->vx += this->ax;
}

EnemySweeping::~EnemySweeping()
{
}
