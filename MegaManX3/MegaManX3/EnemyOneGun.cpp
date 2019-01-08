#include "EnemyOneGun.h"
#include "EnemyOneGunAttack1State.h"
#include <stdlib.h> 
#include <time.h> 

EnemyOneGun::EnemyOneGun()
{
}

void EnemyOneGun::Init(VT3 position, int width, int height)
{
	this->id = ONEGUN;
	this->direct = RIGHT;
	this->position = position;
	this->vx = this->vy = 0;
	this->ax = this->ay = 0;
	this->width = width;
	this->height = height;
	this->listAnimation = new Animation[4];
	//this->SetBasePos(position);
	this->enemyOneGunData = new EnemyOneGunData();
	this->enemyOneGunData->m_EnemyOneGun = this;
	SetIsDead(false);
	SetLife(3);
	this->UpdateRect();
	this->SetListAnimation();

	if (this->enemyOneGunData->m_EnemyOneGun->GetPosition().x > MegaManCharacters::GetInstance()->GetPosition().x)
	{
		SetDirect(Direct::LEFT);
		//SetVx(-600);
	}
	else
	{
		SetDirect(Direct::RIGHT);
		//SetVx(600);

	}
	this->SetState(new EnemyOneGunAttack1State(this->enemyOneGunData));
}
void EnemyOneGun::Draw(double time)
{
	if (!GetIsDead() && checkCamera())
	{
		this->transform.positionInViewport = this->GetPositionInViewport();
		VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
		this->transform.translation = VT2(-cameraPosition.x, -cameraPosition.y);

		this->listAnimation[currentState].Draw(transform.positionInViewport, this->direct, time, VT2(2.5, 2.5), transform.translation);
	}
	for (int i = 0; i < vtRocket.size(); i++)
	{
		if (!vtRocket[i]->GetIsDead())
			vtRocket[i]->Draw(time);
	}
	if (blood != NULL&& !blood->GetIsDead())
	{
		blood->Draw(time);
	}
}
void EnemyOneGun::Update(double time)
{
	if (!GetIsDead() && checkCamera())
	{
		if (GetLife() <= 0)
		{
			int iSecret = rand() % 10 + 1;
			if (iSecret < 5)
			{
				blood = new Blood(VT3(position.x, position.y + 50, 0));
			}
			SetIsDead(true);
		}
		vector<GameObject*> listCollision;
		GameMap::GetInstance()->GetQuadtree()->GetEntitiesCollideAble(listCollision, this);
		CollisionResult staticCollision;
		staticCollision = Collision::SweptAABB(rectBound, 
											VT2(this->vx, this->vy), 
											MegaManCharacters::GetInstance()->GetRect(), 
											VT2(MegaManCharacters::GetInstance()->GetVx(), MegaManCharacters::GetInstance()->GetVy()), 
											time);
		if (staticCollision.isCollision)
		{
			
			MegaManCharacters::GetInstance()->SubLife(2);
			SetLife(0);

		}
		double entryTime = time;
		int deltaBottom = MEGAMAN_WIDTH;
		for (int i = 0; i < listCollision.size(); i++)
		{
			staticCollision = Collision::SweptAABB(rectBound, VT2(this->vx, this->vy), listCollision[i]->GetRect(), VT2(listCollision[i]->GetVx(), listCollision[i]->GetVy()), time);
			if (staticCollision.isCollision)
			{

				switch (staticCollision.directCollision)
				{
				case BOTTOM:
					//if (listCollision[i]->GetId() == Object::STATICOBJECT)
					//{
					if (listCollision[i]->GetId() == Object::STATICOBJECT)
					{
						position.y += vy*staticCollision.entryTime;
						//position.x += vx*staticCollision.entryTime;
						if (this->currentState == ENEMYJUMPING) {
							this->vy = 0;
							this->ay = 0;
							SetState(new EnemyOneGunStandState(this->enemyOneGunData));
							if (this->enemyOneGunData->m_EnemyOneGun->GetPosition().x > MegaManCharacters::GetInstance()->GetPosition().x)
							{
								SetDirect(Direct::LEFT);
							}
							else
							{
								SetDirect(Direct::RIGHT);

							}
						}
						UpdateRect();
					}
						
					//}
					
					break;
				case LEFT:
					if (listCollision[i]->GetId() == Object::STATICOBJECT)
					{
						position.x -= vx*staticCollision.entryTime;
						vx = 0;
						ax = 0;
						UpdateRect();
					}
					break;
				case RIGHT:
					//position.y += vy*staticCollision.entryTime;
					if (listCollision[i]->GetId() == Object::STATICOBJECT)
					{
						position.x -= 2*vx*staticCollision.entryTime;
						vx = 0;
						ax = 0;
						UpdateRect();
					}
					break;
				default:
					break;
				}
			}
		}

		this->enemyOneGunData->m_EnemyOneGunState->Update(time);
		UpdatePosition(time);
	}
	int a = 0;
	for (int i = 0; i < vtRocket.size(); i++)
	{
		if (!vtRocket[i]->GetIsDead())
			vtRocket[i]->Update(time);
		else
		{
			a++;
		}
	}
	if (a == vtRocket.size())
	{
		for (int i = 0; i < vtRocket.size(); i++)
		{
			if (vtRocket[i] != NULL)
			{
				delete vtRocket[i];
				vtRocket[i] = NULL;
			}
		}
		vtRocket.clear();
	}
	if (blood != NULL&& !blood->GetIsDead())
	{
		blood->Update(time);
	}
}
void EnemyOneGun::SetState(EnemyOneGunState* state)
{
	if (!this->enemyOneGunData->m_EnemyOneGunState)
		delete this->enemyOneGunData->m_EnemyOneGunState;

	this->enemyOneGunData->m_EnemyOneGunState = state;
	
	this->currentState = state->GetState();
}
void EnemyOneGun::SetListAnimation()
{
	std::vector<Rect> temp;
	temp.push_back(Rect(60, 41, 92, 80));
	temp.push_back(Rect(42, 0, 73, 40));
	temp.push_back(Rect(0, 49, 29, 90));
	temp.push_back(Rect(0, 0, 41, 48));
	temp.push_back(Rect(30, 49, 59, 90));
	temp.push_back(Rect(74, 0, 105, 40));
	temp.push_back(Rect(93, 41, 125, 80));

	this->listAnimation[ENEMYJUMPING].Create(ENEMIES_1_JUMP, temp.size(), temp, 0.005f, LEFT);
	temp.clear();
	temp.push_back(Rect(0, 0, 39, 37));
	temp.push_back(Rect(0, 76, 44, 110));
	temp.push_back(Rect(40, 35, 87, 64));
	temp.push_back(Rect(45, 95, 93, 122));
	temp.push_back(Rect(0, 123, 48, 150));
	temp.push_back(Rect(45, 65, 92, 94));
	temp.push_back(Rect(40, 0, 84, 34));
	temp.push_back(Rect(0, 38, 39, 75));



	this->listAnimation[ENEMYSTANDING].Create(ENEMIES_1_STAND, temp.size(), temp, 0.1f, LEFT);

	temp.clear();
	temp.push_back(Rect(0, 36, 44, 70));
	temp.push_back(Rect(0, 0, 43, 35));
	this->listAnimation[ENEMYATTACK1].Create(ENEMIES_1_ATTACK1, temp.size(), temp, 0.2f, LEFT);

	temp.clear();
	temp.push_back(Rect(0, 29, 48, 56));
	temp.push_back(Rect(0, 0, 48, 28));

	this->listAnimation[ENEMYATTACK2].Create(ENEMIES_1_ATTACK2, temp.size(), temp, 0.2f, LEFT);

}

void EnemyOneGun::UpdatePosition(double time)
{
	this->dx = this->vx * time;
	this->dy = this->vy * time;

	this->position.x += this->dx;
	this->position.y += this->dy;

	this->UpdateRect();

	this->vy += this->ay;
	this->vx += this->ax;
}
EnemyOneGun::~EnemyOneGun()
{
}
