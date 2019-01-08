#include "Rocket.h"

Rocket::Rocket()
{
}

Rocket::Rocket(D3DXVECTOR3 position, double vx, Direct direct)
{
	animation = new Animation();
	duration = 0;
	std::vector<Rect> temp;

	temp.push_back(Rect(8, 0, 13, 21));
	temp.push_back(Rect(0, 0, 7, 23));

	animation->Create("Assets/enemies/bullet.png", temp.size(), temp, 0.005f, RIGHT);
	temp.clear();
	vy = 0;
	this->id = BULLETENEMY;
	this->position = position;
	this->vx = vx;
	this->isDead = false;
	this->isCollision = false;
	this->direct = direct;
	this->width = 15;
	this->height = 15;
	if (this->GetPosition().y >= MegaManCharacters::GetInstance()->GetPosition().y)
	{
		this->SetVy(-200);
	}
	else
	{
		this->SetVy(200);

	}
	UpdateRect();
}

void Rocket::Update(double time)
{
	if (!isDead)
	{
		if (duration >= 0.04f) {
			VT3 megaManPosition = this->GetPosition();
			VT3 smokePosition(megaManPosition.x - 40 * this->GetDirect(), megaManPosition.y - 8, 0);
			this->AddSmokeEffect(smokePosition);
			duration = 0.0f;
		}
		if (this->listSmokeEff.size() > 0)
		{
			for (size_t i = 0; i < this->listSmokeEff.size(); i++)
			{
				if (!this->listSmokeEff[i]->GetIsDead())
				{
					this->listSmokeEff[i]->Update(time);
				}
			}
		}
		duration += time;
		CollisionResult staticCollision;
		staticCollision = Collision::SweptAABB(rectBound,
			VT2(this->vx, this->vy),
			MegaManCharacters::GetInstance()->GetRect(),
			VT2(MegaManCharacters::GetInstance()->GetVx(), MegaManCharacters::GetInstance()->GetVy()),
			time);
		if (staticCollision.isCollision)
		{

			MegaManCharacters::GetInstance()->SubLife(2);
			this->isCollision = true;

		}
		position.x += vx*time;
		position.y += vy*time;

		if (this->animation->GetIndex() == 1 && this->isCollision == false) {
			this->animation->SetIndex(0);
		}
		if (this->isCollision == true) {
			this->vx = 0;
			if (this->animation->GetIndex() == 0) {
				this->isDead = true;
			}
		}

		vector<GameObject*> listCollision;
		GameMap::GetInstance()->GetQuadtree()->GetEntitiesCollideAble(listCollision, this);
		double entryTime = time;
		for (int i = 0; i < listCollision.size(); i++) {
			staticCollision = Collision::SweptAABB(this->rectBound, VT2(this->vx, this->vy), listCollision[i]->GetRect(), VT2(listCollision[i]->GetVx(), listCollision[i]->GetVy()), time);
			if (staticCollision.isCollision) {
				entryTime = staticCollision.entryTime;
				this->isCollision = true;
			}
		}

		position.x += vx*entryTime;

		UpdateRect();
	}
	else
	{
		for (int i = 0; i < listSmokeEff.size(); i++)
		{
			delete listSmokeEff[i];
			listSmokeEff[i] = NULL;
		}
		listSmokeEff.clear();
	}
}

void Rocket::Draw(double time)
{
	if (!isDead)
	{
		if (this->listSmokeEff.size() > 0)
		{
			for (size_t i = 0; i < this->listSmokeEff.size(); i++)
			{
				this->listSmokeEff[i]->Draw(time);
			}
		}
		this->transform.positionInViewport = this->GetPositionInViewport();
		VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
		this->transform.translation = VT2(-cameraPosition.x, -cameraPosition.y);

		this->animation->Draw(transform.positionInViewport, this->direct, time, VT2(2, 2), transform.translation);
	}
}

void Rocket::AddSmokeEffect(VT3 smokePosition) {
	SmokeEffect *smoke = new SmokeEffect(smokePosition);
	this->listSmokeEff.push_back(smoke);
}

Rocket::~Rocket()
{
}
