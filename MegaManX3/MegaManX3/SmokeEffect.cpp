#include "SmokeEffect.h"

SmokeEffect::SmokeEffect()
{
	this->id = SMOKE;
}


SmokeEffect::~SmokeEffect()
{
}

SmokeEffect::SmokeEffect(VT3 position)
{
	animation = new Animation();

	std::vector<Rect> temp;

	temp.push_back(Rect(0, 30, 12, 39));
	temp.push_back(Rect(15, 14, 27, 25));
	temp.push_back(Rect(15, 0, 28, 13));
	temp.push_back(Rect(0, 0, 14, 14));
	temp.push_back(Rect(0, 15, 14, 29));

	animation->Create(SMOKE_EFFECT_PATH, temp.size(), temp, 0.005f, RIGHT);
	temp.clear();

	this->id = SMOKE;
	this->position = position;
	this->isDead = false;
	this->width = 15;
	this->height = 15;
	this->direct = RIGHT;
}

void SmokeEffect::Update(double time)
{
	if (this->animation->GetIndex() == this->animation->GetTotalFrame() - 1) {
		this->isDead = true;
	}
}

void SmokeEffect::Draw(double time)
{
	if (!isDead)
	{
		this->transform.positionInViewport = this->GetPositionInViewport();
		VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
		this->transform.translation = VT2(-cameraPosition.x, -cameraPosition.y);

		this->animation->Draw(transform.positionInViewport, this->direct, time, VT2(2, 2), transform.translation);
	}
}
