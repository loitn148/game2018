#include "BulletLv3.h"

BulletLv3::BulletLv3()
{
	this->id = BULLET;
}


BulletLv3::~BulletLv3()
{
}

BulletLv3::BulletLv3(D3DXVECTOR3 position, double vx)
{
	animation = new Animation();

	std::vector<Rect> temp;

	//temp.push_back(Rect(4, 110, 6, 112));
	//temp.push_back(Rect(25, 90, 28, 93));
	//temp.push_back(Rect(4, 105, 8, 109));
	//temp.push_back(Rect(61, 87, 81, 101));
	//temp.push_back(Rect(95, 0, 111, 23));
	temp.push_back(Rect(0, 0, 31, 46));
	temp.push_back(Rect(32, 0, 61, 45));
	//temp.push_back(Rect(0, 47, 31, 89));
	//temp.push_back(Rect(21, 90, 24, 98));
	//temp.push_back(Rect(0, 105, 3, 111));
	//temp.push_back(Rect(112, 0, 115, 4));
	//temp.push_back(Rect(9, 105, 10, 109));
	temp.push_back(Rect(0, 90, 20, 104));
	temp.push_back(Rect(63, 62, 91, 86));
	temp.push_back(Rect(63, 33, 91, 61));
	temp.push_back(Rect(92, 33, 118, 59));
	temp.push_back(Rect(32, 77, 60, 105));
	temp.push_back(Rect(32, 46, 62, 76));
	temp.push_back(Rect(62, 0, 94, 32));

	animation->Create("Assets/megaman/bullet_lv3.png", temp.size(), temp, 0.005f, RIGHT);
	temp.clear();

	this->id = BULLET;
	this->position = position;
	this->vx = vx;
	this->vy = vy;
	this->isDead = false;
	this->direct = RIGHT;
	this->width = 10;
	this->height = 10;
	UpdateRect();
}

void BulletLv3::Update(double time)
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

void BulletLv3::Draw(double time)
{
	if (!isDead)
	{
		this->transform.positionInViewport = this->GetPositionInViewport();
		VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
		this->transform.translation = VT2(-cameraPosition.x, -cameraPosition.y);

		this->animation->Draw(transform.positionInViewport, this->direct, time, VT2(2, 2), transform.translation);
	}
}


