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

	std::vector<Rect> _temp;

	_temp.push_back(Rect(28, 51, 38, 58));
	_temp.push_back(Rect(28, 30, 46, 50));
	_temp.push_back(Rect(26, 0, 48, 29));
	_temp.push_back(Rect(0, 0, 25, 31));
	_temp.push_back(Rect(0, 32, 27, 62));

	bulletLv1->Create(BULLET_LV1_PATH, _temp.size(), _temp, 0.05f, RIGHT);
	_temp.clear();

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
