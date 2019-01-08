#include "BulletLv2.h"

BulletLv2::BulletLv2()
{
	this->id = BULLET;
}


BulletLv2::~BulletLv2()
{
}

BulletLv2::BulletLv2(D3DXVECTOR3 position, double vx, Direct direct)
{
	animation = new Animation();

	std::vector<Rect> temp;

	temp.push_back(Rect(0, 0, 16, 38, VT3(-7, 0, 0)));
	temp.push_back(Rect(42, 89, 56, 103));
	temp.push_back(Rect(36, 39, 60, 63));
	temp.push_back(Rect(61, 48, 77, 64));
	temp.push_back(Rect(0, 76, 24, 100));
	temp.push_back(Rect(25, 89, 41, 105));
	temp.push_back(Rect(61, 25, 83, 47));
	temp.push_back(Rect(36, 64, 60, 88));

	animation->Create(BULLET_LV2_PATH, temp.size(), temp, 0.005f, RIGHT);
	temp.clear();

	this->id = BULLET;
	this->position = position;
	this->vx = vx;
	this->isDead = false;
	this->isCollision = false;
	this->direct = direct;
	this->width = 25;
	this->height = 25;
	UpdateRect();
}

void BulletLv2::Update(double time)
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
		if (listCollision[i]->GetId() == ONEGUN || listCollision[i]->GetId() == ENEMYROCKET) {
			if (staticCollision.isCollision || Collision::IsColliding(this->rectBound, listCollision[i]->GetRect())) {
				entryTime = staticCollision.entryTime;
				this->isCollision = true;
				listCollision[i]->SubLife(2);
			}
		}
		else {
			if (staticCollision.isCollision) {
				entryTime = staticCollision.entryTime;
				this->isCollision = true;
			}
		}
	}

	position.x += vx*entryTime;

	UpdateRect();
}

void BulletLv2::Draw(double time)
{
	if (!isDead)
	{
		this->transform.positionInViewport = this->GetPositionInViewport();
		VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
		this->transform.translation = VT2(-cameraPosition.x, -cameraPosition.y);

		this->animation->Draw(transform.positionInViewport, this->direct, time, VT2(2, 2), transform.translation);
	}
}
