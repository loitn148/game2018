#include "EnemyRocket.h"
#include "EnemyRocketAttack1State.h"

EnemyRocket::EnemyRocket()
{
}

void EnemyRocket::Init(VT3 position, int width, int height, Direct direct)
{
	this->id = ENEMYROCKET;
	this->direct = direct;
	this->position = position;
	this->vx = this->vy = 0;
	this->ax = this->ay = 0;
	this->vy = 100;
	this->ay = 100;
	this->width = width;
	this->height = height;
	this->listAnimation = new Animation[4];
	this->SetBasePos(position);
	this->enemyRocketData = new EnemyRocketData();
	this->enemyRocketData->m_EnemyRocket = this;
	this->SetState(new EnemyRocketAttack1State(this->enemyRocketData));
	SetDead(false);
	this->UpdateRect();
	this->SetListAnimation();
	nLife = 3;
}
void EnemyRocket::Draw(double time)
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
void EnemyRocket::Update(double time)
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
				if (listCollision[i]->GetId() != Object::BULLET)
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
				if (listCollision[i]->GetId() != Object::STATICOBJECT)
				{
					this->vy = 0;
					this->ay = 0;
				}
			}
			else
			{
				this->position.y -= vx * time;
			}
		}
		this->enemyRocketData->m_EnemyRocketState->Update(time);
		UpdatePosition(time);
	}
	if (rocket != NULL && !rocket->GetIsDead())
	{
		rocket->Update(time);
	}
}
void EnemyRocket::SetState(EnemyRocketState* state)
{
	if (!this->enemyRocketData->m_EnemyRocketState)
		delete this->enemyRocketData->m_EnemyRocketState;

	this->enemyRocketData->m_EnemyRocketState = state;

	this->currentState = state->GetState();
}
void EnemyRocket::SetListAnimation()
{
	std::vector<Rect> temp;
	temp.push_back(Rect(0, 0, 45, 38));
	this->listAnimation[ENEMYROCKETSTANDING].Create(ENEMIES_ROCKET_STAND, temp.size(), temp, 0.01f, LEFT);

	temp.clear();
	temp.push_back(Rect(0, 42, 45, 80));
	temp.push_back(Rect(0, 81, 45, 119));
	temp.push_back(Rect(46, 0, 91, 38));
	temp.push_back(Rect(0, 0, 45, 41));
	this->listAnimation[ENEMYROCKETATTACK1].Create(ENEMIES_ROCKET_SHOOTING, temp.size(), temp, 0.1f, LEFT);



}

void EnemyRocket::UpdatePosition(double time)
{
	this->dx = this->vx * time;
	this->dy = this->vy * time;

	this->position.x += this->dx;
	this->position.y += this->dy;

	this->UpdateRect();

	this->vy += this->ay;
	this->vx += this->ax;
}
EnemyRocket::~EnemyRocket()
{
}