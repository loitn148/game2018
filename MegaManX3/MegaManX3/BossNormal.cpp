#include "BossNormal.h"

BossNormal::BossNormal()
{
	this->id = NORMALBOSS;
}


BossNormal::~BossNormal()
{
}

BossNormal::BossNormal(D3DXVECTOR3 position, float vx, float vy)
{
	animation = new Animation();

	std::vector<Rect> temp;

	temp.push_back(Rect(0, 0, 49, 49));
	

	animation->Create(BOSSNORMAL, temp.size(), temp, 0.05f, RIGHT);
	temp.clear();

	this->id = NORMALBOSS;
	this->position = position;
	this->angle = 0.0f;
	this->vx = vx;
	this->vy = vy;
	this->isDead = false;
	this->width = 98;
	this->height = 98;
	this->rotateCenter = VT2(0,0);
	UpdateRect();
}

void BossNormal::Update(float time)
{
	CollisionResult result;
	position.x += vx*time;
	position.y += vy*time;
	this->angle += 0.5f;

	UpdateRect();
}

void BossNormal::Draw(float time)
{
	if (!isDead)
	{
		this->transform.positionInViewport = this->GetPositionInViewport();
		VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
		this->transform.translation = VT2(-cameraPosition.x, -cameraPosition.y);

		this->animation->Draw(transform.positionInViewport, this->direct, time, VT2(2, 2), transform.translation, C_XRGB(255, 255, 255), this->angle, this->rotateCenter);
	}
}