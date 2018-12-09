#include "BulletLv2.h"

BulletLv2::BulletLv2()
{
	this->id = BULLET;
}


BulletLv2::~BulletLv2()
{
}

BulletLv2::BulletLv2(D3DXVECTOR3 position, float vx, float vy)
{
	bulletLv2 = new Animation();

	std::vector<Rect> _temp;

	_temp.push_back(Rect(28, 51, 38, 58));
	_temp.push_back(Rect(28, 30, 46, 50));
	_temp.push_back(Rect(26, 0, 48, 29));
	_temp.push_back(Rect(0, 0, 25, 31));
	_temp.push_back(Rect(0, 32, 27, 62));

	bulletLv2->Create(BULLET_LV1_PATH, _temp.size(), _temp, 0.05f, RIGHT);
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

void BulletLv2::Update(float time)
{
	CollisionResult result;
	position.x += vx*time;
	position.y += vy*time;

	UpdateRect();
}

void BulletLv2::Draw(float time)
{
	if (!isDead)
	{
		this->transform.positionInViewport = this->GetPositionInViewport();
		VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
		this->transform.translation = VT2(-cameraPosition.x, -cameraPosition.y);

		this->bulletLv2->Draw(transform.positionInViewport, this->direct, time, VT2(2, 2), transform.translation);
	}
}
