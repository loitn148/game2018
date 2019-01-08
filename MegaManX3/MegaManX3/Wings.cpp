#include "Wings.h"



Wings::Wings()
{
	this->id = WINGS;
}


Wings::~Wings()
{
}

Wings::Wings(D3DXVECTOR3 position, float vx, float vy)
{
	wings = new Animation();

	std::vector<Rect> temp;

	temp.push_back(Rect(0, 0, 24, 96));
	temp.push_back(Rect(25, 0, 66, 79));
	temp.push_back(Rect(67, 0, 108, 47));

	wings->Create(WINGS_PATH, temp.size(), temp, 0.005f, RIGHT);
	temp.clear();

	this->id = WINGS;
	this->position = position;
	this->vx = vx;
	this->vy = vy;
	this->width = 10;
	this->height = 10;
	UpdateRect();
}

void Wings::Update(VT3 bossPosition, BigBossStates currentState)
{
	CollisionResult result;
	if (currentState == PRICK)
	{
		position.x = bossPosition.x + 10;
		position.y = bossPosition.y + 100;
	}
	else
	{
		position.x = bossPosition.x;
		position.y = bossPosition.y + 120;
	}
	

	UpdateRect();
}

void Wings::Draw(float time)
{
	this->transform.positionInViewport = this->GetPositionInViewport();
	VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
	this->transform.translation = VT2(-cameraPosition.x, -cameraPosition.y);

	this->wings->Draw(transform.positionInViewport, this->direct, time, VT2(2.5, 2.5), transform.translation);
}
