#include "MegaManHealth.h"

MegaManHealth* MegaManHealth::instance = NULL;
MegaManHealth* MegaManHealth::GetInstance() {
	if (!MegaManHealth::instance) {
		MegaManHealth::instance = new MegaManHealth();
	}
	return MegaManHealth::instance;
}

MegaManHealth::MegaManHealth()
{
	this->animation = new Animation();
	this->currentHealth = 16;
	this->SetAnimation();
	this->position = VT3(CAMERA_START_X + 10, CAMERA_START_Y - 10, 0);
}


MegaManHealth::~MegaManHealth()
{
}

void MegaManHealth::Update(double time) {
	if (currentHealth > 0) {
		int curentIdx = currentHealth / 2 - 1;
		this->animation->SetIndex(curentIdx);
	}
	else {
		isDead = true;
	}
}

void MegaManHealth::SetHealth(int health) {
	this->currentHealth = health;
}

void MegaManHealth::Draw(double time) {
	if (!isDead) {
		this->transform.positionInViewport = this->GetPositionInViewport();
		VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
		this->transform.translation = VT2(-cameraPosition.x, -cameraPosition.y);

		this->animation->Draw(transform.positionInViewport, this->direct, time, VT2(2.2, 2.5), transform.translation, C_XRGB(255, 255, 255));
	}
}

void MegaManHealth::SetAnimation() {
	std::vector<Rect> temp;
	temp.push_back(Rect(0, 0, 52, 14));
	temp.push_back(Rect(0, 14, 52, 28));
	temp.push_back(Rect(0, 28, 52, 42));
	temp.push_back(Rect(0, 42, 52, 56));
	temp.push_back(Rect(0, 56, 52, 70));
	temp.push_back(Rect(0, 70, 52, 84));
	temp.push_back(Rect(0, 84, 52, 98));
	temp.push_back(Rect(0, 98, 52, 112));

	this->animation->Create(HEALTH_PATH, temp.size(), temp, 0.05f, RIGHT);
	temp.clear();
}