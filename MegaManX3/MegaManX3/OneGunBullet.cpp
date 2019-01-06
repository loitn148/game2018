#include "OneGunBullet.h"


OneGunBullet::OneGunBullet()
{
}
OneGunBullet::OneGunBullet(D3DXVECTOR3 position, double vy, double ay, double vx, Direct direct)
{
	animation = new Animation();

	std::vector<Rect> temp;

	temp.push_back(Rect(0, 0, 8, 8));


	animation->Create("Assets/enemies/OneGunBullet.png", temp.size(), temp, 0.05f, RIGHT);
	temp.clear();
	this->SetVy(vy);
	this->SetAy(ay);

	if (direct == Direct::LEFT)
	{
		this->SetVx(-vx);
	}
	else
	{
		this->SetVx(vx);
	}
	this->id = BULLET;
	this->position = position;
	this->OldPosion = position;
	this->isDead = false;
	this->isCollision = false;
	this->direct = direct;
	this->width = 15;
	this->height = 15;
	UpdateRect();
}

void OneGunBullet::Update(double time)
{



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
	CollisionResult staticCollision;
	double entryTime = time;
	for (int i = 0; i < listCollision.size(); i++) {
		staticCollision = Collision::SweptAABB(this->rectBound, VT2(this->vx, this->vy), listCollision[i]->GetRect(), VT2(listCollision[i]->GetVx(), listCollision[i]->GetVy()), time);
		if (staticCollision.isCollision) {
			entryTime = staticCollision.entryTime;
			this->isCollision = true;
		}
	}
	UpdatePosition(time);

	UpdateRect();
}

void OneGunBullet::Draw(double time)
{
	if (!isDead)
	{
		this->transform.positionInViewport = this->GetPositionInViewport();
		VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
		this->transform.translation = VT2(-cameraPosition.x, -cameraPosition.y);

		this->animation->Draw(transform.positionInViewport, this->direct, time, VT2(2, 2), transform.translation);
	}
}

void OneGunBullet::UpdatePosition(double time)
{
	this->dx = this->vx * time;
	this->dy = this->vy * time;

	this->position.x += this->dx;
	this->position.y += this->dy;

	this->UpdateRect();

	this->vy += this->ay;
	this->vx += this->ax;
}

OneGunBullet::~OneGunBullet()
{
}
