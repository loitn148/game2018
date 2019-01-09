#include "RocketEnemy3.h"

RocketEnemy3::RocketEnemy3()
{
}

void RocketEnemy3::SetDestroyEffect() {
	delete destroyedEffect;
	this->destroyedEffect = new DestroyedEffect(VT3(position.x, position.y, 0));
}

RocketEnemy3::RocketEnemy3(D3DXVECTOR3 position, double vx, Direct direct)
{
	animation = new Animation();

	std::vector<Rect> temp;


	temp.push_back(Rect(0, 0, 10, 15));


	animation->Create("Assets/enemies/RocketEnemy3.png", temp.size(), temp, 0.005f, RIGHT);
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
	if (this->GetPosition().y > MegaManCharacters::GetInstance()->GetPosition().y)
	{
		this->SetVy(-100);
	}
	else
	{
		this->SetVy(100);

	}
	UpdateRect();
}

void RocketEnemy3::Update(double time)
{
	if (!isDead)
	{
		CollisionResult staticCollision;
		staticCollision = Collision::SweptAABB(rectBound,
			VT2(this->vx, this->vy),
			MegaManCharacters::GetInstance()->GetRect(),
			VT2(MegaManCharacters::GetInstance()->GetVx(), MegaManCharacters::GetInstance()->GetVy()),
			time);
		if (staticCollision.isCollision)
		{

			MegaManCharacters::GetInstance()->SubLife(2);
			SetDestroyEffect();
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
				SetDestroyEffect();
			}
		}

		position.x += vx*entryTime;

		UpdateRect();
	}
}

void RocketEnemy3::Draw(double time)
{
	if (!isDead)
	{
		this->transform.positionInViewport = this->GetPositionInViewport();
		VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
		this->transform.translation = VT2(-cameraPosition.x, -cameraPosition.y);

		this->animation->Draw(transform.positionInViewport, this->direct, time, VT2(2, 2), transform.translation);
	}
}
RocketEnemy3::~RocketEnemy3()
{
}
