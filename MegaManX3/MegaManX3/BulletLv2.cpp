#include "BulletLv2.h"

BulletLv2::BulletLv2()
{
	this->id = BULLET;
}


BulletLv2::~BulletLv2()
{
}

BulletLv2::BulletLv2(D3DXVECTOR3 position, double vx)
{
	animation = new Animation();

	std::vector<Rect> temp;

	/*temp.push_back(Rect(43, 33, 45, 35));
	temp.push_back(Rect(61, 65, 75, 79));
	temp.push_back(Rect(52, 0, 76, 24));
	temp.push_back(Rect(23, 39, 35, 67));
	temp.push_back(Rect(43, 0, 51, 32));
	temp.push_back(Rect(17, 0, 29, 38));
	temp.push_back(Rect(0, 39, 22, 75));
	temp.push_back(Rect(30, 0, 42, 38));*/
	temp.push_back(Rect(0, 0, 16, 38));
	temp.push_back(Rect(42, 89, 56, 103));
	temp.push_back(Rect(36, 39, 60, 63));
	temp.push_back(Rect(61, 48, 77, 64));
	temp.push_back(Rect(0, 76, 24, 100));
	temp.push_back(Rect(25, 89, 41, 105));
	temp.push_back(Rect(61, 25, 83, 47));
	temp.push_back(Rect(36, 64, 60, 88));

	animation->Create("Assets/megaman/bullet_lv2.png", temp.size(), temp, 0.005f, RIGHT);
	temp.clear();

	this->id = BULLET;
	this->position = position;
	this->vx = vx;
	this->isDead = false;
	this->direct = RIGHT;
	this->width = 70;
	this->height = 25;
	UpdateRect();
}

void BulletLv2::Update(double time)
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
