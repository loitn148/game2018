#include "DestroyedEffect.h"

DestroyedEffect::DestroyedEffect()
{
	this->id = SMOKE;
}


DestroyedEffect::~DestroyedEffect()
{
}

DestroyedEffect::DestroyedEffect(VT3 position)
{
	animation = new Animation();

	std::vector<Rect> temp;

	temp.push_back(Rect(45, 66, 61, 82));
	temp.push_back(Rect(0, 0, 32, 32));
	temp.push_back(Rect(0, 99, 24, 127));
	temp.push_back(Rect(17, 66, 44, 96));
	temp.push_back(Rect(0, 33, 27, 65));
	temp.push_back(Rect(33, 0, 63, 32));
	temp.push_back(Rect(28, 33, 51, 65));
	temp.push_back(Rect(0, 66, 16, 98));

	animation->Create(DESTROYED_EFFECT_PATH, temp.size(), temp, 0.02f, RIGHT);
	temp.clear();

	this->id = SMOKE;
	this->position = position;
	this->isDead = false;
	this->width = 15;
	this->height = 15;
	this->direct = RIGHT;
}

void DestroyedEffect::Update(double time)
{
	if (this->animation->GetIndex() == this->animation->GetTotalFrame() - 1) {
		this->isDead = true;
	}
}

void DestroyedEffect::Draw(double time)
{
	if (!isDead)
	{
		this->transform.positionInViewport = this->GetPositionInViewport();
		VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
		this->transform.translation = VT2(-cameraPosition.x, -cameraPosition.y);

		this->animation->Draw(transform.positionInViewport, this->direct, time, VT2(2, 2), transform.translation);
	}
}