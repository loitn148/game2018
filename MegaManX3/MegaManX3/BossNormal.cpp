#include "BossNormal.h"

BossNormal::BossNormal()
{
	this->id = NORMALBOSS;
}


BossNormal::~BossNormal()
{
}

BossNormal::BossNormal(D3DXVECTOR3 position, double vx, double vy)
{
	animation = new Animation();

	std::vector<Rect> temp;

	temp.push_back(Rect(227, 700, 447, 920));
	temp.push_back(Rect(235, 0, 468, 233));
	temp.push_back(Rect(231, 468, 457, 695));
	temp.push_back(Rect(235, 234, 465, 465));
	temp.push_back(Rect(0, 468, 230, 699));
	temp.push_back(Rect(0, 700, 226, 926));
	temp.push_back(Rect(0, 0, 234, 233));
	temp.push_back(Rect(469, 0, 689, 219));
	temp.push_back(Rect(0, 234, 234, 467));

	animation->Create(BOSSNORMAL, temp.size(), temp, 0.001f, RIGHT);
	temp.clear();

	this->id = NORMALBOSS;
	this->position = position;
	this->angle = 0.1f;
	this->vx = vx;
	this->vy = vy;
	this->isDead = false;
	this->width = 98;
	this->height = 98;
	this->rotateCenter = VT2(2300, 100);
	UpdateRect();
}

void BossNormal::Update(double time)
{
	CollisionResult result;
	position.x += vx*time;
	position.y += vy*time;

	UpdateRect();
}

void BossNormal::Draw(double time)
{
	if (!isDead)
	{
		this->transform.positionInViewport = this->GetPositionInViewport();
		VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
		this->transform.translation = VT2(-cameraPosition.x, -cameraPosition.y);

		this->animation->Draw(transform.positionInViewport, this->direct, time, VT2(0.6, 0.6), transform.translation, C_XRGB(255, 255, 255), this->angle, this->rotateCenter);
	}
}