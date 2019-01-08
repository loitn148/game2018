#include "Elevator1.h"



Elevator1::Elevator1()
{
}


Elevator1::~Elevator1()
{
}

Elevator1::Elevator1(VT3 position, double vx, double vy) {
	animation = new Animation();

	std::vector<Rect> temp;

	temp.push_back(Rect(0, 97, 43, 193));
	temp.push_back(Rect(47, 0, 92, 96));
	temp.push_back(Rect(0, 0, 46, 96));

	animation->Create(ELEVATOR1, temp.size(), temp, 0.001f, RIGHT);
	temp.clear();

	this->id = ELEVATOR;
	this->position = position;
	this->vx = vx;
	this->isDead = false;
	this->isActive = false;
	this->isStop = false;
	this->direct = RIGHT;
	this->width = 210;
	this->height = 70;
	UpdateRect();
}

void Elevator1::Update(double time) {
	if (isActive) {
		position.y += vy*time;
		if (position.y >= 3463 && this->isStop == false) {
			this->vy = 0;
			this->isStop = true;
			Camera::GetInstance()->SetPosition(VT3(1705, 3910, 0));
			Camera::GetInstance()->allowMove(true, false);
			if (MegaManCharacters::GetInstance()->GetAy() == 0) {
				MegaManCharacters::GetInstance()->SetVy(0);
				MegaManCharacters::GetInstance()->SetAy(ACCELERATION_Y);
			}
		}
		UpdateRect();
	}
}

void Elevator1::Draw(double time)
{
	this->transform.positionInViewport = this->GetPositionInViewport();
	VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
	this->transform.translation = VT2(-cameraPosition.x, -cameraPosition.y);

	this->animation->Draw(transform.positionInViewport, this->direct, time, VT2(2.2, 2.2), transform.translation);
}

void Elevator1::SetIsActive(bool isActive) {
	this->isActive = isActive;
}

bool Elevator1::GetIsActive() {
	return this->isActive;
}
