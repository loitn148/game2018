#include "BulletLv1.h"

BulletLv1::BulletLv1()
{
	this->id = BULLET;
}


BulletLv1::~BulletLv1()
{
}

BulletLv1::BulletLv1(D3DXVECTOR3 position, double vx)
{
	animation = new Animation();

	std::vector<Rect> temp;

	temp.push_back(Rect(16, 13, 22, 21));
	temp.push_back(Rect(16, 0, 28, 12));
	temp.push_back(Rect(0, 16, 13, 29));
	temp.push_back(Rect(0, 0, 15, 15));

	animation->Create("Assets/megaman/bullet_lv1.png", temp.size(), temp, 0.005f, RIGHT);
	temp.clear();

	this->id = BULLET;
	this->position = position;
	this->vx = vx;
	this->isDead = false;
	this->isCollision = false;
	this->direct = RIGHT;
	this->width = 15;
	this->height = 15;
	UpdateRect();
}

void BulletLv1::Update(double time)
{
	position.x += vx*time;
	position.y += vy*time;

	if (this->animation->GetIndex() == 1 && this->isDead == false) {
		this->animation->SetIndex(0);
	}
	else if (this->isCollision == true && this->animation->GetIndex() == 0) {
		this->isDead = true;
	}

	vector<GameObject*> listCollision;
	GameMap::GetInstance()->GetQuadtree()->GetEntitiesCollideAble(listCollision, this);
	CollisionResult staticCollision;
	double entryTime = time;
	int deltaBottom = MEGAMAN_WIDTH;
	for (int i = 0; i < listCollision.size(); i++) {
		staticCollision = Collision::SweptAABB(this->rectBound, VT2(this->vx, this->vy), listCollision[i]->GetRect(), VT2(listCollision[i]->GetVx(), listCollision[i]->GetVy()), time);
		if (staticCollision.isCollision) {
			this->isCollision = true;
		}
	}

	UpdateRect();
}

void BulletLv1::Draw(double time)
{
	if (!isDead)
	{
		this->transform.positionInViewport = this->GetPositionInViewport();
		VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
		this->transform.translation = VT2(-cameraPosition.x, -cameraPosition.y);

		this->animation->Draw(transform.positionInViewport, this->direct, time, VT2(2, 2), transform.translation);
	}
}
