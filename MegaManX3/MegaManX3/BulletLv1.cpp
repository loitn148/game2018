#include "BulletLv1.h"

BulletLv1::BulletLv1()
{
	this->id = BULLET;
}


BulletLv1::~BulletLv1()
{
}

BulletLv1::BulletLv1(D3DXVECTOR3 position, float vx, float vy)
{
	bulletLv1 = new Animation();

	std::vector<Rect> temp;

	temp.push_back(Rect(16, 13, 22, 21));
	temp.push_back(Rect(16, 0, 28, 12));
	temp.push_back(Rect(0, 16, 13, 29));
	temp.push_back(Rect(0, 0, 15, 15));

	bulletLv1->Create(BULLET_LV1_PATH, temp.size(), temp, 0.05f, RIGHT);
	temp.clear();

	this->id = BULLET;
	this->position = position;
	this->vx = vx;
	this->vy = vy;
	this->isDead = false;
	this->width = 10;
	this->height = 10;
	UpdateRect();
}

void BulletLv1::Update(float time)
{
	CollisionResult result;
	position.x += vx*time;
	position.y += vy*time;

	UpdateRect();
}

void BulletLv1::Draw(float time)
{
	if (!isDead)
	{
		this->transform.positionInViewport = this->GetPositionInViewport();
		VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
		this->transform.translation = VT2(-cameraPosition.x, -cameraPosition.y);

		this->bulletLv1->Draw(transform.positionInViewport, this->direct, time, VT2(2, 2), transform.translation);
	}
}
